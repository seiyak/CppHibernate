/*
 * CppHibernateJLongObject.cpp
 *
 *  Created on: Nov 28, 2011
 *      Author: seiyak
 */

#include "CppHibernateJLongObject.h"

namespace cppHibernate {

const char *CppHibernateJLongObject::JAVA_LANG_LONG = "java/lang/Long";
const char *CppHibernateJLongObject::JAVA_LANG_LONG_SIGNATURE =
		"Ljava/lang/Long;";
const char *CppHibernateJLongObject::JAVA_LANG_LONG_PRIMITIVE_SIGNATURE = "J";
const char *CppHibernateJLongObject::JAVA_LANG_LONG_LONGVALUE_NAME = "longValue";
const char *CppHibernateJLongObject::JAVA_LANG_LONG_LONGVALUE_SIGNATURE = "()J";

CppHibernateJLongObject::CppHibernateJLongObject(JNIEnv *env, jobject obj,
		jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateJObject(env, obj, objClass, classLoader) {
}

long CppHibernateJLongObject::getVal() {

	jlong val = 0;
	jmethodID longValueId = this->env->GetMethodID(this->objClass,
			CppHibernateJLongObject::JAVA_LANG_LONG_LONGVALUE_NAME,
			CppHibernateJLongObject::JAVA_LANG_LONG_LONGVALUE_SIGNATURE);
	if (longValueId != NULL) {
		val = this->env->CallLongMethod(this->obj, longValueId);
		this->checkAndThrow();
	} else {
		this->throwException();
	}

	return val;
}

void CppHibernateJLongObject::setVal(long val) {

	if (this->obj != NULL) {
		this->env->DeleteGlobalRef(this->obj);
		this->obj = NULL;
	}

	jmethodID methodId = this->env->GetMethodID(this->objClass,
			CppHibernateJObject::JAVA_CONSTRUCTOR_NAME, "(J)V");
	if (methodId != NULL) {

		jobject jObj = this->env->NewObject(this->objClass, methodId, val);
		this->checkAndThrow();

		this->obj = this->env->NewGlobalRef(jObj);
		this->checkAndThrow();
	} else {
		this->throwException();
	}
}

CppHibernateJLongObject::~CppHibernateJLongObject() {

}

} /* namespace cppHibernate */
