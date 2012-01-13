/*
 * CppHibernateJDoubleObject.cpp
 *
 *  Created on: Nov 28, 2011
 *      Author: seiyak
 */

#include "CppHibernateJDoubleObject.h"

namespace cppHibernate {

const char *CppHibernateJDoubleObject::JAVA_LANG_DOUBLE = "java/lang/Double";
const char *CppHibernateJDoubleObject::JAVA_LANG_DOUBLE_SIGNATURE =
		"Ljava/lang/Double;";
const char *CppHibernateJDoubleObject::JAVA_LANG_DOUBLE_PRIMITIVE_SIGNATURE =
		"D";
const char *CppHibernateJDoubleObject::JAVA_LANG_DOUBLE_DOUBLEVALUE_NAME =
		"doubleValue";
const char *CppHibernateJDoubleObject::JAVA_LANG_DOUBLE_DOUBLEVALUE_SIGNATURE =
		"()D";

CppHibernateJDoubleObject::CppHibernateJDoubleObject(JNIEnv *env, jobject obj,
		jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateJObject(env, obj, objClass, classLoader) {
}

double CppHibernateJDoubleObject::getVal() {

	jdouble val = 0;
	jmethodID doubleValueId = this->env->GetMethodID(this->objClass,
			CppHibernateJDoubleObject::JAVA_LANG_DOUBLE_DOUBLEVALUE_NAME,
			CppHibernateJDoubleObject::JAVA_LANG_DOUBLE_DOUBLEVALUE_SIGNATURE);

	if (doubleValueId != NULL) {
		val = this->env->CallDoubleMethod(this->obj, doubleValueId);
		this->checkAndThrow();
	} else {
		this->throwException();
	}

	return val;
}

void CppHibernateJDoubleObject::setVal(double val) {

	if (this->obj != NULL) {
		this->env->DeleteGlobalRef(this->obj);
		this->obj = NULL;
	}

	jmethodID methodId = this->env->GetMethodID(this->objClass,
			CppHibernateJObject::JAVA_CONSTRUCTOR_NAME, "(D)V");
	if (methodId != NULL) {

		jobject jObj = this->env->NewObject(this->objClass, methodId, val);
		this->checkAndThrow();

		this->obj = this->env->NewGlobalRef(jObj);
		this->checkAndThrow();

	} else {
		this->throwException();
	}
}

CppHibernateJDoubleObject::~CppHibernateJDoubleObject() {

}

} /* namespace cppHibernate */
