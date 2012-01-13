/*
 * CppHibernateJStringObject.cpp
 *
 *  Created on: Nov 15, 2011
 *      Author: apple
 */

#include <cstring>
#include <string>
#include "CppHibernateJStringObject.h"

namespace cppHibernate {

const char *CppHibernateJStringObject::JAVA_LANG_STRING = "java/lang/String";
const char *CppHibernateJStringObject::JAVA_LANG_STRING_SIGNATURE =
		"Ljava/lang/String;";

CppHibernateJStringObject::CppHibernateJStringObject(JNIEnv *env, jobject obj,
		jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateJObject(env, obj, objClass, classLoader) {
}

/**
 * Gets value as const char pointer.
 * @return const char * Value representing string.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
const char *CppHibernateJStringObject::getVal() {

	if (this->obj != NULL) {

		const char *objStr = CppHibernateAccessor::copyStringFrom(this->env,
				(jstring) this->obj);
		if (this->env->ExceptionCheck()) {
			this->throwException();
		}

		return objStr;
	} else {
		throw CppHibernateException(
				"doesn't have a value yet. Please construct this object correctly.");
	}

	return NULL;
}

/**
 * Sets val.
 * @param const char * Value to be set as this value.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
void CppHibernateJStringObject::setVal(const char *val) {

	if (this->obj != NULL) {
		this->env->DeleteGlobalRef(this->obj);
		this->obj = NULL;
	}

	if (this->env->ExceptionCheck()) {
		this->throwException();
	}

	jstring str = this->env->NewStringUTF(val);
	if (str != NULL) {

		this->obj = this->env->NewGlobalRef(str);

		if (this->env->ExceptionCheck()) {
			this->throwException();
		}

	} else {
		this->throwException();
	}
}

/**
 * Concatenates the specified value to this string. If this object's obj property is NULL and/or the specified value is NULL, this method doesn't do anything
 * but returns this object without concatenation.
 * @param CppHibernateJStringObject * Value to be concatenated to this string.
 * @return CppHibernateJStringObject & Returns this concatenated object.
 * @throw Throws exceptions when JNI encounters exception.
 */
CppHibernateJStringObject & CppHibernateJStringObject::concat(
		CppHibernateJStringObject *val) {

	const char *valVal = val->getVal();
	CppHibernateJStringObject& objRef = this->concat(valVal);
	this->env->ReleaseStringUTFChars((jstring) val->getObj(), valVal);

	if (this->env->ExceptionCheck()) {
		this->throwException();
	}

	return objRef;
}

CppHibernateJStringObject & CppHibernateJStringObject::concat(const char *val) {

	if (this->obj == NULL || val == NULL) {
		return (*this);
	}

	const char *thisVal = this->getVal();

	std::string str(thisVal);
	str += val;

	this->setVal(str.c_str());

	if (this->env->ExceptionCheck()) {
		this->throwException();
	}

	return (*this);
}

CppHibernateJStringObject::~CppHibernateJStringObject() {

}

} /* namespace cppHibernate */
