/*
 * CppHibernateKeySetObject.h
 *
 *  Created on: Jan 6, 2012
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEKEYSETOBJECT_H_
#define CPPHIBERNATEKEYSETOBJECT_H_

#include "CppHibernateJObject.h"

namespace cppHibernate {

class CppHibernateJKeySetObject: public cppHibernate::CppHibernateJObject {

public:
	CppHibernateJKeySetObject(JNIEnv*, jobject, jclass, AbstractClassLoader*);
	virtual ~CppHibernateJKeySetObject();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEJKEYSETOBJECT_H_ */
