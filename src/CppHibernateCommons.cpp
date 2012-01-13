/*
 * CppHibernateCommons.cpp
 *
 *  Created on: Nov 10, 2011
 *      Author: apple
 */

#include "CppHibernateCommons.h"

namespace cppHibernate {

CppHibernateCommons::CppHibernateCommons(JNIEnv *env, jobject obj,
		jclass objClass, AbstractClassLoader *classLoader) :
		env(NULL), obj(NULL), objClass(NULL), classLoader(NULL) {

	this->checkCommonProperties(env, obj, objClass, classLoader);

	this->env = env;
	this->obj = obj;
	this->objClass = objClass;
	this->classLoader = classLoader;

}

/**
 * Checks if required properties to call methods on JVM are set or not.
 * @param JNIEnv *env JNI pointer.
 * @param jobject obj An object representing a Java object.
 * @param jobject objClass An object representing a Java class.
 * @param AbstractClassLoader *classLoader Class loader to load classes when necessary.
 */
void CppHibernateCommons::checkCommonProperties(JNIEnv *env, jobject obj,
		jclass objClass, AbstractClassLoader *classLoader) {

	if (env == NULL) {
		throw CppHibernateException(
				"Please set 'env' property pointing to JVM.");
	}

	if (obj == NULL) {
		throw CppHibernateException(
				"Please set 'obj' property representing Java object.");
	}

	if (objClass == NULL) {
		throw CppHibernateException(
				"Please set 'objClass' property representing Java class.");
	}

	if (classLoader == NULL) {
		throw CppHibernateException(
				"Please set 'classLoader' property representing class loader object");
	}
}

/**
 * Gets obj property;
 */
jobject CppHibernateCommons::getObj() {
	return this->obj;
}

jclass CppHibernateCommons::getObjClass() {
	return this->objClass;
}

/**
 * Sets obj property. This method expects a global ref as the parameter.
 * @param jobject newObj Object to be set as the value of the property.
 */
void CppHibernateCommons::setObj(jobject newObj) {

	if (this->obj != NULL) {
		this->env->DeleteGlobalRef(this->obj);
		this->obj = NULL;
	}

	this->obj = newObj;
}

/**
 * Throws exceptions when JNI encounters exceptions.
 */
void CppHibernateCommons::throwException() {

	this->env->ExceptionDescribe();
	this->env->Throw(this->env->ExceptionOccurred());
}

/**
 * Checks if there is an appending exception or not. If so, throws the exception and do nothing otherwise.
 */
void CppHibernateCommons::checkAndThrow() {
	if (this->env->ExceptionCheck()) {
		this->throwException();
	}
}

CppHibernateCommons::~CppHibernateCommons() {

	if (this->obj != NULL) {
		this->env->DeleteGlobalRef(this->obj);
		this->obj = NULL;
	}

	if (this->objClass != NULL) {
		this->env->DeleteGlobalRef(this->objClass);
		this->objClass = NULL;
	}
}

} /* namespace cppHibernate */
