/*
 * CppHibernateJBooleanObject.cpp
 *
 *  Created on: Nov 15, 2011
 *      Author: apple
 */

#include "CppHibernateJBooleanObject.h"

namespace cppHibernate {

const char *CppHibernateJBooleanObject::JAVA_LANG_BOOLEAN = "java/lang/Boolean";
const char *CppHibernateJBooleanObject::JAVA_BOOLEAN_TRUE = "true";
const char *CppHibernateJBooleanObject::JAVA_BOOLEAN_FALSE = "false";
const char *CppHibernateJBooleanObject::JAVA_LANG_BOOLEAN_BOOLEANVALUE_NAME =
		"booleanValue";
const char *CppHibernateJBooleanObject::JAVA_LANG_BOOLEAN_SIGNATURE =
		"Ljava/lang/Boolean;";
const char *CppHibernateJBooleanObject::JAVA_LANG_BOOLEAN_PRIMITIVE_SIGNATURE =
		"Z";

CppHibernateJBooleanObject::CppHibernateJBooleanObject(JNIEnv *env, jobject obj,
		jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateJObject(env, obj, objClass, classLoader) {

}

/**
 * Returns Java.lang.Boolean value as const char pointer.
 * @return const char * Returns const char pointer representation of Java boolean value, 'true' or 'false'.
 * @throw Throws exception when JNI encounters exceptions.
 */
const char *CppHibernateJBooleanObject::toString() {

	jmethodID toStringId = (jmethodID) this->findToString(this->objClass);
	if (toStringId != NULL) {

		jstring str = (jstring) this->env->CallObjectMethod(this->obj,
				toStringId);

		this->env->DeleteGlobalRef((jobject) toStringId);

		if (str != NULL) {

			const char *val = this->env->GetStringUTFChars(str, JNI_FALSE);
			if (this->env->ExceptionCheck()) {
				this->throwException();
			} else {
				if (std::strncmp(val,
						CppHibernateJBooleanObject::JAVA_BOOLEAN_TRUE,
						this->env->GetStringUTFLength(str)) == 0) {

					this->env->ReleaseStringUTFChars(str, val);
					return CppHibernateJBooleanObject::JAVA_BOOLEAN_TRUE;
				} else if (std::strncmp(val,
						CppHibernateJBooleanObject::JAVA_BOOLEAN_FALSE,
						this->env->GetStringUTFLength(str)) == 0) {

					this->env->ReleaseStringUTFChars(str, val);
					return CppHibernateJBooleanObject::JAVA_BOOLEAN_FALSE;
				}
			}
		} else {
			this->throwException();
		}
	} else {
		this->throwException();
	}

	return CppHibernateJBooleanObject::JAVA_BOOLEAN_FALSE;
}

/**
 * Gets C++ bool value.
 * @return bool Returns true or false.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
bool CppHibernateJBooleanObject::getVal() {

	bool val = false;

	jmethodID booleanValueId = this->env->GetMethodID(this->objClass,
			CppHibernateJBooleanObject::JAVA_LANG_BOOLEAN_BOOLEANVALUE_NAME,
			"()Z");
	if (booleanValueId != NULL) {

		jboolean booleanVal = this->env->CallBooleanMethod(this->obj,
				booleanValueId);

		if (this->env->ExceptionCheck()) {
			this->throwException();
		} else {
			if (booleanVal == JNI_TRUE) {
				val = true;
			} else if (booleanVal == JNI_FALSE) {
				val = false;
			}
		}
	} else {
		this->throwException();
	}

	return val;
}

/**
 * Sets bool value.
 * @param bool val true or false.
 * @throw Throws exceptions when JNI encounters excepitons.
 */
void CppHibernateJBooleanObject::setVal(bool val) {

	jmethodID booleanConstructorId = this->env->GetMethodID(objClass,
			CppHibernateJObject::JAVA_CONSTRUCTOR_NAME,
			CppHibernateJObject::PRIMITIVE_CLASS_CONSTRUCTOR_SIGNATURE);

	if (this->obj != NULL) {
		this->env->DeleteGlobalRef(this->obj);
		this->obj = NULL;
	}

	this->obj = this->createBooleanValue(val);
}

/**
 * Creates a jobject object representing Java.lang.Boolean class.
 * @param bool val true or false.
 * @return CppHibernateJBooleanObject Returns CppHibernateJBooleanObject value.The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exception.
 */
jobject CppHibernateJBooleanObject::createBooleanValue(bool val) {

	jobject booleanVal = NULL;
	jmethodID booleanConstructorId = this->env->GetMethodID(this->objClass,
			CppHibernateJObject::JAVA_CONSTRUCTOR_NAME,
			CppHibernateJObject::PRIMITIVE_CLASS_CONSTRUCTOR_SIGNATURE);

	if (booleanConstructorId != NULL) {

		jstring str = NULL;
		if (val) {
			str = this->env->NewStringUTF(
					CppHibernateJBooleanObject::JAVA_BOOLEAN_TRUE);
		} else {
			str = this->env->NewStringUTF(
					CppHibernateJBooleanObject::JAVA_BOOLEAN_FALSE);
		}

		this->throwException();

		jobject bVal = this->env->NewObject(this->objClass,
				booleanConstructorId, str);
		this->env->DeleteLocalRef(str);

		if (bVal != NULL) {
			booleanVal = this->env->NewGlobalRef(bVal);
		} else {
			this->throwException();
		}
	} else {
		this->throwException();
	}

	return booleanVal;
}

/**
 * Checks if the parameter object has the same bool value or not.
 * @param CppHibernateJBooleanObject * An object compared with this object.
 * @return bool Returns true if they have the same bool value, false otherwise.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
bool CppHibernateJBooleanObject::equals(
		CppHibernateJBooleanObject *booleanObj) {
	//// TODO need to think about the alternative for this method such as operator overloading.

	if (this == booleanObj) {
		return true;
	}
	return (this->getVal() == booleanObj->getVal());
}

CppHibernateJBooleanObject::~CppHibernateJBooleanObject() {

}

} /* namespace cppHibernate */
