/*
 * CppHibernateJIntegerObject.cpp
 *
 *  Created on: Nov 22, 2011
 *      Author: seiyak
 */

#include "CppHibernateJIntegerObject.h"

namespace cppHibernate {

const char *CppHibernateJIntegerObject::JAVA_LANG_INTEGER = "java/lang/Integer";
const char *CppHibernateJIntegerObject::JAVA_LANG_INTEGER_SIGNATURE =
		"Ljava/lang/Integer;";
const char *CppHibernateJIntegerObject::JAVA_LANG_INTEGER_PRIMITIVE_SIGNATURE =
		"I";
const char *CppHibernateJIntegerObject::JAVA_LANG_INTEGER_INTVALUE_NAME =
		"intValue";
const char *CppHibernateJIntegerObject::JAVA_LANG_INTEGER_INTVALUE_SIGNATURE =
		"()I";

CppHibernateJIntegerObject::CppHibernateJIntegerObject(JNIEnv *env, jobject obj,
		jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateJObject(env, obj, objClass, classLoader) {

}

int CppHibernateJIntegerObject::getVal() {

	jint val = 0;
	jmethodID intValueId = this->env->GetMethodID(this->objClass,
			CppHibernateJIntegerObject::JAVA_LANG_INTEGER_INTVALUE_NAME,
			CppHibernateJIntegerObject::JAVA_LANG_INTEGER_INTVALUE_SIGNATURE);
	if (intValueId != NULL) {
		val = this->env->CallIntMethod(this->obj, intValueId);
		this->checkAndThrow();
	} else {
		this->throwException();
	}

	return val;
}

void CppHibernateJIntegerObject::setVal(int val) {

	if (this->obj != NULL) {
		this->env->DeleteGlobalRef(this->obj);
		this->obj = NULL;
	}

	jmethodID methodId = this->env->GetMethodID(this->objClass,
			CppHibernateJObject::JAVA_CONSTRUCTOR_NAME, "(I)V");
	if (methodId != NULL) {

		jobject jObj = this->env->NewObject(this->objClass, methodId, val);
		this->checkAndThrow();

		this->obj = this->env->NewGlobalRef(jObj);
		this->checkAndThrow();
	} else {
		this->throwException();
	}
}

CppHibernateJIntegerObject::~CppHibernateJIntegerObject() {

}

} /* namespace cppHibernate */
