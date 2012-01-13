/*
 * CppHibernateJavaObject.h
 *
 *  Created on: Dec 5, 2011
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEJAVAOBJECT_H_
#define CPPHIBERNATEJAVAOBJECT_H_

#include <jni.h>
#include "CppHibernateCommonProperties.h"

namespace cppHibernate {

class CppHibernateJavaObject {

private:
	jobject obj;
	jclass objClass;
public:
	CppHibernateJavaObject(jobject, jclass);
	virtual ~CppHibernateJavaObject();
	jobject getObj() const;
	jclass getObjClass() const;
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEJAVAOBJECT_H_ */
