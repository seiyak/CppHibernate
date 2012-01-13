/*
 * CppHibernateIndexException.h
 *
 *  Created on: Nov 5, 2011
 *      Author: apple
 */

#ifndef CPPHIBERNATEINDEXEXCEPTION_H_
#define CPPHIBERNATEINDEXEXCEPTION_H_

#include "CppHibernateException.h"

namespace cppHibernate {

class CppHibernateIndexException: public CppHibernateException {
public:
	CppHibernateIndexException(const char *exceptionMsg):CppHibernateException(exceptionMsg){}
	virtual ~CppHibernateIndexException() throw(){}
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEINDEXEXCEPTION_H_ */
