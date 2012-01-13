/*
 * CppHibernatePropertiesAccessor.cpp
 *
 *  Created on: Nov 18, 2011
 *      Author: seiyak
 */

#include <cstring>
#include "CppHibernatePropertiesAccessor.h"

namespace cppHibernate {

const char *CppHibernatePropertiesAccessor::JAVA_LANG_REFLECT_FIELD =
		"java/lang/reflect/Field";
const char *CppHibernatePropertiesAccessor::JAVA_LANG_CLASS_GETDECLAREDFIELDS_NAME =
		"getDeclaredFields";
const char *CppHibernatePropertiesAccessor::JAVA_LANG_CLASS_GETDECLAREDFIELDS_SIGNATURE =
		"()[Ljava/lang/reflect/Field;";
const char *CppHibernatePropertiesAccessor::JAVA_LANG_REFLECT_FIELD_GETTYPE_NAME =
		"getType";
const char *CppHibernatePropertiesAccessor::JAVA_LANG_REFLECT_FIELD_GETTYPE_SIGNATURE =
		"()Ljava/lang/Class;";

CppHibernatePropertiesAccessor::CppHibernatePropertiesAccessor(JNIEnv *env,
		AbstractClassLoader *classLoader) :
		CppHibernateAccessor(env, classLoader), env(env), classLoader(
				classLoader) {
}

const char *CppHibernatePropertiesAccessor::searchTypeFrom(jobject obj,
		jclass objClass, const char *propertyName) {

	const char *fieldType = this->reflectField(obj, objClass, propertyName);
	return this->createCorrespondingSignature(fieldType);
}

/**
 * Searches type using Java reflection.
 * @param jobject obj An object to be reflected by Java reflection.
 * @param jclass objClass An object representing the object's class.
 * @param const char * propertyName Property name examined by the reflection.
 * @return const char * Returns const char pointer representing a string representation.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
const char *CppHibernatePropertiesAccessor::reflectField(jobject obj,
		jclass objClass, const char *propertyName) {

	jobject classObj = this->callGetClass(obj, objClass);
	jclass classCls = this->env->FindClass(
			CppHibernateAccessor::JAVA_LANG_CLASS);

	jobject field = this->findFieldWith(classObj, classCls, propertyName);
	this->env->DeleteGlobalRef(classObj);
	this->env->DeleteLocalRef(classCls);

	jclass fieldClass = this->env->FindClass(
			CppHibernatePropertiesAccessor::JAVA_LANG_REFLECT_FIELD);

	jobject typeObj = this->getType(field, fieldClass);
	const char *str = CppHibernateAccessor::toString(this->env, typeObj,
			fieldClass);
	this->env->DeleteGlobalRef(field);
	this->env->DeleteGlobalRef(typeObj);

	return str;
}

/**
 * Finds the specified property from the class definition.
 * @param jobject obj An object where the property is declared.
 * @param jclass objClass Class where the property is declared.
 * @param const char * propertyName Property name to be searched for.
 * @return jobject An object representing java.lang.reflect.Field for the property. The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
jobject CppHibernatePropertiesAccessor::findFieldWith(jobject classObj,
		jclass classObjClass, const char *propertyName) {

	jmethodID getDeclaredFieldsId =
			this->env->GetMethodID(
					classObjClass,
					CppHibernatePropertiesAccessor::JAVA_LANG_CLASS_GETDECLAREDFIELDS_NAME,
					CppHibernatePropertiesAccessor::JAVA_LANG_CLASS_GETDECLAREDFIELDS_SIGNATURE);

	if (getDeclaredFieldsId == NULL) {
		this->throwException();
	}

	jobject o = this->getTarget(propertyName, classObj, classObjClass,
			this->env->NewGlobalRef((jobject) getDeclaredFieldsId));

	this->checkAndThrow();

	return this->env->NewGlobalRef(o);
}

/**
 * Calls java.lang.reflect.Field.getType() method.
 * @param jobject obj An object representing java.lang.reflect.Field class.
 * @param jclass objClass A Class representing java.lang.reflect.Field class.
 * @return jobject An object representing java.lang.Class class. The returned object must be deleted when the job is done.
 */
jobject CppHibernatePropertiesAccessor::getType(jobject obj, jclass objClass) {

	jobject typeObj = NULL;
	jmethodID getTypeId =
			this->env->GetMethodID(
					objClass,
					CppHibernatePropertiesAccessor::JAVA_LANG_REFLECT_FIELD_GETTYPE_NAME,
					CppHibernatePropertiesAccessor::JAVA_LANG_REFLECT_FIELD_GETTYPE_SIGNATURE);

	if (getTypeId != NULL) {
		typeObj = this->env->NewGlobalRef(
				this->env->CallObjectMethod(obj, getTypeId));

		this->checkAndThrow();
	} else {
		this->throwException();
	}

	return typeObj;
}

CppHibernatePropertiesAccessor::~CppHibernatePropertiesAccessor() {

}

} /* namespace cppHibernate */
