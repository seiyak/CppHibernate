/*
 * CppHibernateJIteratorObject.cpp
 *
 *  Created on: Jan 9, 2012
 *      Author: seiyak
 */

#include "CppHibernateJIteratorObject.h"

namespace cppHibernate {

const char *CppHibernateJIteratorObject::JAVA_UTIL_ITERATOR_HASNEXT_NAME =
		"hasNext";
const char *CppHibernateJIteratorObject::JAVA_UTIL_ITERATOR_HASNEXT_SIGNATURE =
		"()Z";
const char *CppHibernateJIteratorObject::JAVA_UTIL_ITERATOR_NEXT_NAME = "next";
const char *CppHibernateJIteratorObject::JAVA_UTIL_ITERATOR_NEXT_SIGNATURE =
		"()Ljava/lang/Object;";
const char *CppHibernateJIteratorObject::JAVA_UTIL_ITERATOR_REMOVE_NAME =
		"remove";
const char *CppHibernateJIteratorObject::JAVA_UTIL_ITERATOR_REMOVE_SIGNATURE =
		"()V";

CppHibernateJIteratorObject::CppHibernateJIteratorObject(JNIEnv *env,
		jobject obj, jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateJObject(env, obj, objClass, classLoader) {

}

/**
 * Returns if there are more elements to iterator on this object.
 * @return bool Returns true if there is, false otherwise.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
bool CppHibernateJIteratorObject::hasNext() {

	jmethodID hasNextId = this->env->GetMethodID(this->objClass,
			CppHibernateJIteratorObject::JAVA_UTIL_ITERATOR_HASNEXT_NAME,
			CppHibernateJIteratorObject::JAVA_UTIL_ITERATOR_HASNEXT_SIGNATURE);
	this->checkAndThrow();

	jboolean result = this->env->CallBooleanMethod(this->obj, hasNextId);
	this->checkAndThrow();

	return result;
}

CppHibernateJObject *CppHibernateJIteratorObject::next() {

	jmethodID nextId = this->env->GetMethodID(this->objClass,
			CppHibernateJIteratorObject::JAVA_UTIL_ITERATOR_NEXT_NAME,
			CppHibernateJIteratorObject::JAVA_UTIL_ITERATOR_NEXT_SIGNATURE);
	this->checkAndThrow();

	jobject result = this->env->CallObjectMethod(this->obj, nextId);
	this->checkAndThrow();

	return this->createReturnObj(this->env->NewGlobalRef(result));
}

void CppHibernateJIteratorObject::remove() {

	jmethodID removeId = this->env->GetMethodID(this->objClass,
			CppHibernateJIteratorObject::JAVA_UTIL_ITERATOR_REMOVE_NAME,
			CppHibernateJIteratorObject::JAVA_UTIL_ITERATOR_REMOVE_SIGNATURE);
	this->checkAndThrow();

	this->env->CallVoidMethod(this->obj, removeId);
	this->checkAndThrow();
}

CppHibernateJIteratorObject::~CppHibernateJIteratorObject() {

}

} /* namespace cppHibernate */
