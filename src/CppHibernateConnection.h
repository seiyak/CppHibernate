/*
 * CppHibernateConnection.h
 *
 *  Created on: Nov 12, 2011
 *      Author: apple
 */

#ifndef CPPHIBERNATECONNECTION_H_
#define CPPHIBERNATECONNECTION_H_

#include "CppHibernateCommons.h"

namespace cppHibernate {

class CppHibernateConnection: public cppHibernate::CppHibernateCommons {
public:
	CppHibernateConnection(JNIEnv*, jobject, jclass, AbstractClassLoader *);
	virtual ~CppHibernateConnection();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATECONNECTION_H_ */
