/*
 * CppHibernateJCollectionsObject.cpp
 *
 *  Created on: Jan 6, 2012
 *      Author: seiyak
 */

#include "CppHibernateJCollectionsObject.h"

namespace cppHibernate {

const char *CppHibernateJCollectionsObject::JAVA_UTIL_CLEAR_NAME = "clear";
const char *CppHibernateJCollectionsObject::JAVA_UTIL_CLEAR_SIGNATURE = "()V";
const char *CppHibernateJCollectionsObject::JAVA_UTIL_SIZE_NAME = "size";
const char *CppHibernateJCollectionsObject::JAVA_UTIL_SIZE_SIGNATURE = "()I";
const char *CppHibernateJCollectionsObject::JAVA_UTIL_ISEMPTY_NAME = "isEmpty";
const char *CppHibernateJCollectionsObject::JAVA_UTIL_ISEMPTY_SIGNATURE = "()Z";
const char *CppHibernateJCollectionsObject::JAVA_UTIL_COLLECTION =
		"java/util/Collection";
const char *CppHibernateJCollectionsObject::RETURN_BOOL_PARAM_OBJECT_SIGNATURE =
		"(Ljava/lang/Object;)Z";
const char *CppHibernateJCollectionsObject::JAVA_UTIL_MAP = "java/util/Map";

CppHibernateJCollectionsObject::CppHibernateJCollectionsObject(JNIEnv *env,
		jobject obj, jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateJObject(env, obj, objClass, classLoader) {
}

/**
 * Returns the number of elements that this object stores only if this object is an instance of Java.util.Collection.
 * This method is used when expressing one to many and/or many to many relationship between objects.
 * @return int Returns the number of elements that this object stores.
 * @throw Throws exceptions when JNI encounters exceptions and also when this method is called with objects that are not instance of java,.util.Collection.
 */
int CppHibernateJCollectionsObject::size() {

	this->checkInstanceOfCollectionOrMap();
	int siz = 0;
	jmethodID sizeId = this->env->GetMethodID(this->objClass,
			CppHibernateJCollectionsObject::JAVA_UTIL_SIZE_NAME,
			CppHibernateJCollectionsObject::JAVA_UTIL_SIZE_SIGNATURE);
	if (sizeId != NULL) {
		siz = this->env->CallIntMethod(this->obj, sizeId);
		this->checkAndThrow();
	} else {
		this->throwException();
	}

	return siz;
}

/**
 * Checks if this object as an instance of java.util.Collection has any elements or not.
 * @return bool Returns true if this object has no elements, false otherwise.
 * @throw Throws exceptions when JNI encounters exceptions and also when this method is called with objects that are not instance of java,.util.Collection.
 */
bool CppHibernateJCollectionsObject::isEmpty() {

	this->checkInstanceOfCollectionOrMap();

	bool empty = false;
	jmethodID isEmptyId = this->env->GetMethodID(this->objClass,
			CppHibernateJCollectionsObject::JAVA_UTIL_ISEMPTY_NAME,
			CppHibernateJCollectionsObject::JAVA_UTIL_ISEMPTY_SIGNATURE);
	if (isEmptyId != NULL) {

		if (this->env->CallBooleanMethod(this->obj, isEmptyId) == JNI_TRUE) {
			this->checkAndThrow();

			empty = true;
		} else if (this->env->CallBooleanMethod(this->obj,
				isEmptyId) == JNI_FALSE) {
			this->checkAndThrow();

			empty = false;
		}
	} else {

		this->throwException();
	}
	return empty;
}

/**
 * Checks if this is an instance of java.util.Collection or java.util.Map.If so, does nothing. Throws an exception otherwise.
 */
void CppHibernateJCollectionsObject::checkInstanceOfCollectionOrMap() {
	if (!this->isInstanceOf(
			CppHibernateJCollectionsObject::JAVA_UTIL_COLLECTION)
			&& !this->isInstanceOf(
					CppHibernateJCollectionsObject::JAVA_UTIL_MAP)) {
		throw CppHibernateException(
				this->createSimpleErrorMessage(
						"java.util.Collection or java.util.Map").c_str());
	}
}

CppHibernateJCollectionsObject::~CppHibernateJCollectionsObject() {

}

} /* namespace cppHibernate */
