/*
 * CppHibernateJObject.cpp
 *
 *  Created on: Nov 14, 2011
 *      Author: apple
 */

#include <cstring>
#include <cstdarg>
#include "CppHibernateJObject.h"
#include "CppHibernateJStringObject.h"
#include "CppHibernateObjectHelper.h"
#include "CppHibernateJavaObject.h"

namespace cppHibernate {

const char *CppHibernateJObject::PRIMITIVE_CLASS_CONSTRUCTOR_SIGNATURE =
		"(Ljava/lang/String;)V";
const char *CppHibernateJObject::JAVA_TOSTRING_SIGNATURE =
		"()Ljava/lang/String;";
const char *CppHibernateJObject::JAVA_CONSTRUCTOR_NAME = "<init>";
const char *CppHibernateJObject::JAVA_DEFAULT_CONSTRUCTOR_SIGNATURE = "()V";
const char *CppHibernateJObject::JAVA_TOSTRING_NAME = "toString";
const char *CppHibernateJObject::JAVA_ARRAY_SIGNATURE = "[";
const char *CppHibernateJObject::JAVA_CLASS_PREFIX_SIGNATURE = "L";
const char *CppHibernateJObject::JAVA_HASHCODE_NAME = "hashCode";
const char *CppHibernateJObject::JAVA_HASHCODE_SIGNATURE = "()I";
const char *CppHibernateJObject::JAVA_EQUALS_NAME = "equals";
const char *CppHibernateJObject::JAVA_EQUALS_SIGNATURE = "(Ljava/lang/Object;)Z";

CppHibernateJObject::CppHibernateJObject(JNIEnv *env, jobject obj,
		jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateCommons(env, obj, objClass, classLoader), propertiesAccessor(
				env, classLoader), methodInvoker(env, classLoader) {
}

/**
 * Finds toString() method which is a common method call.
 * @return jobject An object representing jmethodId.The returned object must be released when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
jobject CppHibernateJObject::findToString(jclass clazz) {

	jobject methodId = NULL;
	jmethodID toStringId = this->env->GetMethodID(clazz,
			CppHibernateJObject::JAVA_TOSTRING_NAME,
			CppHibernateJObject::JAVA_TOSTRING_SIGNATURE);

	if (toStringId != NULL) {
		methodId = this->env->NewGlobalRef((jobject) toStringId);
	} else {
		this->throwException();
	}

	return methodId;
}

/**
 * Sets a value for the specific property.
 * @param const char * propertyName Property that is set by the value.
 * @param CppHibernateJObject * val The value to be set to the property.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
void CppHibernateJObject::setVal(const char *propertyName,
		CppHibernateJObject *val) {

	const char *signature = this->propertiesAccessor.searchTypeFrom(this->obj,
			this->objClass, propertyName);
	jfieldID fieldId = this->env->GetFieldID(this->objClass, propertyName,
			signature);

	if (fieldId != NULL) {

		this->env->SetObjectField(this->obj, fieldId, val->getObj());
		this->checkAndThrow();
	} else {
		this->throwException();
	}
}

/**
 * The returned object must be released when the job is done.
 */
CppHibernateJObject *CppHibernateJObject::getVal(const char *propertyName) {

	CppHibernateJObject *jObj = NULL;

	std::string signature(
			this->propertiesAccessor.searchTypeFrom(this->obj, this->objClass,
					propertyName));
	jfieldID fieldId = this->env->GetFieldID(this->objClass, propertyName,
			signature.c_str());
	if (fieldId != NULL) {

		jobject objField = this->env->GetObjectField(this->obj, fieldId);

		if (objField != NULL) {

			jobject globalObjField = this->env->NewGlobalRef(objField);
			this->checkAndThrow();

			jObj = CppHibernateObjectHelper::newInstance(this->env,
					this->classLoader, signature, globalObjField);
		} else {
			return NULL;
		}
	} else {
		this->throwException();
	}

	return jObj;
}

const char *CppHibernateJObject::toString() {

	return CppHibernateAccessor::toString(this->env, this->obj, this->objClass);
}

/**
 * Gets the canonical name of this Java object.
 * @return const char * Returns the canonical name of the object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
const char *CppHibernateJObject::getCanonicalName() {
	jobject classObj = this->propertiesAccessor.callGetClass(this->obj,
			this->objClass);
	jclass classCls = (jclass) (this->env->NewGlobalRef(
			this->env->FindClass(CppHibernateAccessor::JAVA_LANG_CLASS)));
	this->checkAndThrow();
	return this->findCanonicalName(classObj, classCls);
}

/**
 * Checks if the specified CppHibernateJObject pointer is NULL or not. If it's NULL, throws an exception.If not, does nothing.
 * @param CppHibernateJObject * Pointer to CppHibernateJObject object to be examined.
 * @throw Throws an exception when the specified pointer is NULL.
 */
void CppHibernateJObject::checkNull(CppHibernateJObject *element) {
	if (element == NULL) {
		throw CppHibernateException(
				"the specified element is NULL. can't add/remove NULL.");
	}
}

/**
 * Gets the specified object's canonical name.
 * @param jobject obj Object whose canonical name is returned.
 * @return const char * Returns the canonical name.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
const char *CppHibernateJObject::getCanonicalName(jobject obj) {
	jobject objClass = this->env->NewGlobalRef(this->env->GetObjectClass(obj));
	jobject classObj = this->propertiesAccessor.callGetClass(obj,
			(jclass) (objClass));
	this->env->DeleteGlobalRef(objClass);
	jclass classCls = (jclass) (this->env->NewGlobalRef(
			this->env->FindClass(CppHibernateAccessor::JAVA_LANG_CLASS)));
	return this->findCanonicalName(classObj, classCls);
}

/**
 * Finds this object's canonical name using java.lang.Class.getCanonicalName() method on the specified java.lang.Class object and class.
 * @param jobject classObj Object of the java.lang.Class class.
 * @param jclass classCls java.lang.Class class.
 * @return const char * Returns the canonical name.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
const char *CppHibernateJObject::findCanonicalName(jobject classObj,
		jclass classCls) {
	jmethodID getCanonicalNameId = this->env->GetMethodID(classCls,
			"getCanonicalName", "()Ljava/lang/String;");
	if (getCanonicalNameId == NULL) {
		this->env->DeleteGlobalRef(classObj);
		this->env->DeleteGlobalRef(classCls);
		this->throwException();
	}
	jobject canonicalNameObj = this->env->CallObjectMethod(classObj,
			getCanonicalNameId);
	if (canonicalNameObj == NULL) {

		this->env->DeleteGlobalRef(classObj);
		this->env->DeleteGlobalRef(classCls);
		this->throwException();
	}
	this->env->DeleteGlobalRef(classObj);
	this->env->DeleteGlobalRef(classCls);
	jobject globalCanonicalNameObj = this->env->NewGlobalRef(canonicalNameObj);
	this->checkAndThrow();
	const char *canonicalName = CppHibernateAccessor::copyStringFrom(this->env,
			(jstring) (((((((((((((((globalCanonicalNameObj))))))))))))))));
	this->env->DeleteGlobalRef(globalCanonicalNameObj);

	return canonicalName;
}

/**
 * Checks if this object is an instance of a specified class.
 * @param const char *className Class name to be checked with this object.
 * @return bool Returns true if this object is an instance of the specified class, false otherwise.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
bool CppHibernateJObject::isInstanceOf(const char *className) {
	jobject targetClass = this->env->FindClass(className);
	if (targetClass == NULL) {
		this->env->ExceptionClear();

		targetClass = this->classLoader->loadClass(className);
		this->checkAndThrow();
	} else {

		targetClass = this->env->NewGlobalRef(targetClass);
		this->checkAndThrow();
	}
	if (this->env->IsInstanceOf(this->obj, (jclass) targetClass) == JNI_TRUE) {
		this->env->DeleteGlobalRef(targetClass);
		this->checkAndThrow();

		return true;
	}

	this->env->DeleteGlobalRef(targetClass);
	this->checkAndThrow();

	return false;
}

/**
 * Creates return object according to the specified object.
 * @param jobject obj Java object to be returned as a part of newly created CppHibernateJObject object.
 * @return CppHibernateJObject * Returns newly created CppHibernateJObject object according to the type of the specified object.
 * The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateJObject *CppHibernateJObject::createReturnObj(jobject obj) {
	std::string objectSignature(this->getCanonicalName(obj));

	return CppHibernateObjectHelper::newInstance(this->env, this->classLoader,
			this->propertiesAccessor.constructObjectSignature(objectSignature),
			obj);
}

/**
 * Creates a simple error message with the specified type.
 * @param const char * Type name to be used in the message.
 * @return std::string Returns error message.
 */
std::string CppHibernateJObject::createSimpleErrorMessage(const char *type) {

	std::string errorMessage("the method is only for ");
	errorMessage += type;
	errorMessage += " but called with ";
	errorMessage += this->getCanonicalName();

	return errorMessage;
}

/**
 * Invokes a specified method.
 * @param const char * methodName Method name to be invoked.
 * @param int numberOfParameters Number of parameters that the method requires to invoke.
 * @param ... Parameters for the method.
 * @return CppHibernateJObject * Returns CppHibernateJObject pointer as the result of the invocation. If the method returns a value, then
 * the returned object must be deleted when the job is done. If not, returns NULL which means the return type is 'void'.
 * @throw Throws exceptions when JNI encounters exceptions and the specified method is not found.
 */
CppHibernateJObject *CppHibernateJObject::invoke(const char *methodName,
		int numberOfParameters, ...) {

	va_list argList;
	va_start(argList, numberOfParameters);

	CppHibernateJavaObject rtnObj = this->methodInvoker.invoke(this->obj,
			this->objClass, methodName, numberOfParameters, argList);
	va_end(argList);

	if (rtnObj.getObj() == NULL) {
		return NULL;
	}

	this->checkAndThrow();
	return CppHibernateObjectHelper::newInstance(
			this->env,
			this->classLoader,
			std::string(
					this->methodInvoker.getMethodReturnSignature(this->obj,
							this->objClass, methodName)), rtnObj.getObj());
}

/**
 * Gets the hash code of this object.
 * @return int Returns the hash code.
 * @throw Throws exceptions when JNI encountes exceptions.
 */
int CppHibernateJObject::hashCode() {

	jmethodID hashCodeId = this->env->GetMethodID(this->objClass,
			CppHibernateJObject::JAVA_HASHCODE_NAME,
			CppHibernateJObject::JAVA_HASHCODE_SIGNATURE);
	this->checkAndThrow();

	jint hash = this->env->CallIntMethod(this->obj, hashCodeId);
	this->checkAndThrow();

	return hash;
}

/**
 * Checks if this object equals to the specified object.
 * @param CppHibernateJObject * Object to be compared with this object for equality.
 * @return bool Returns true if they are equal, false otherwise.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
bool CppHibernateJObject::equals(CppHibernateJObject *obj) {

	jmethodID equalsId = this->env->GetMethodID(this->objClass,
			CppHibernateJObject::JAVA_EQUALS_NAME,
			CppHibernateJObject::JAVA_EQUALS_SIGNATURE);
	this->checkAndThrow();

	jboolean result = this->env->CallBooleanMethod(this->obj, equalsId,
			obj->getObj());
	this->checkAndThrow();

	return result;
}

CppHibernateJObject::~CppHibernateJObject() {

}

}

/* namespace cppHibernate */
