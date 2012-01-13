/*
 * CppHibernateKeySetObject.cpp
 *
 *  Created on: Jan 6, 2012
 *      Author: seiyak
 */

#include "CppHibernateJKeySetObject.h"

namespace cppHibernate {

CppHibernateJKeySetObject::CppHibernateJKeySetObject(JNIEnv *env, jobject obj,
		jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateJObject(env, obj, objClass, classLoader) {

}

CppHibernateJKeySetObject::~CppHibernateJKeySetObject() {

}

} /* namespace cppHibernate */
