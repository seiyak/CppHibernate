/*
 * CppHibernateConnection.cpp
 *
 *  Created on: Nov 12, 2011
 *      Author: apple
 */

#include "CppHibernateConnection.h"

namespace cppHibernate {

////TODO need to implement the methods here. Currently this class is empty.
CppHibernateConnection::CppHibernateConnection(JNIEnv *env, jobject obj,
		jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateCommons(env, obj, objClass, classLoader) {

}

CppHibernateConnection::~CppHibernateConnection() {

}

} /* namespace cppHibernate */
