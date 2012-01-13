/*
 * CppHibernateJFloatObject.cpp
 *
 *  Created on: Nov 28, 2011
 *      Author: seiyak
 */

#include "CppHibernateJFloatObject.h"

namespace cppHibernate {

const char *CppHibernateJFloatObject::JAVA_LANG_FLOAT = "java/lang/Float";
const char *CppHibernateJFloatObject::JAVA_LANG_FLOAT_SIGNATURE =
		"Ljava/lang/Float;";
const char *CppHibernateJFloatObject::JAVA_LANG_FLOAT_PRIMITIVE_SIGNATURE = "F";
const char *CppHibernateJFloatObject::JAVA_LANG_FLOAT_FLOATVALUE_NAME =
		"floatValue";
const char *CppHibernateJFloatObject::JAVA_LANG_FLOAT_FLOATVALUE_SIGNATURE =
		"()F";

CppHibernateJFloatObject::CppHibernateJFloatObject(JNIEnv *env, jobject obj,
		jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateJObject(env, obj, objClass, classLoader) {
}

float CppHibernateJFloatObject::getVal() {

	jfloat val = 0;
	jmethodID floatValueId = this->env->GetMethodID(this->objClass,
			CppHibernateJFloatObject::JAVA_LANG_FLOAT_FLOATVALUE_NAME,
			CppHibernateJFloatObject::JAVA_LANG_FLOAT_FLOATVALUE_SIGNATURE);

	if (floatValueId != NULL) {
		val = this->env->CallFloatMethod(this->obj, floatValueId);
		this->checkAndThrow();
	} else {
		this->throwException();
	}

	return val;
}

void CppHibernateJFloatObject::setVal(float val) {

	if (this->obj != NULL) {
		this->env->DeleteGlobalRef(this->obj);
		this->obj = NULL;
	}

	jmethodID methodId = this->env->GetMethodID(this->objClass,
			CppHibernateJObject::JAVA_CONSTRUCTOR_NAME, "(F)V");

	if (methodId != NULL) {

		jobject jObj = this->env->NewObject(this->objClass, methodId, val);
		this->checkAndThrow();

		this->obj = this->env->NewGlobalRef(jObj);
	} else {

		this->throwException();
	}
}

CppHibernateJFloatObject::~CppHibernateJFloatObject() {

}

} /* namespace cppHibernate */
