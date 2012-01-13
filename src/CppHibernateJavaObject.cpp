/*
 * CppHibernateJavaObject.cpp
 *
 *  Created on: Dec 5, 2011
 *      Author: seiyak
 */

#include "CppHibernateJavaObject.h"
#include "CppHibernateException.h"

namespace cppHibernate {

CppHibernateJavaObject::CppHibernateJavaObject(jobject obj, jclass objClass) :
		obj(obj), objClass(objClass) {
}

jobject CppHibernateJavaObject::getObj() const {
	return obj;
}

jclass CppHibernateJavaObject::getObjClass() const {
	return objClass;
}

CppHibernateJavaObject::~CppHibernateJavaObject() {

}

} /* namespace cppHibernate */
