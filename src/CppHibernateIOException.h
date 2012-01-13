/*
 * CppHibernateIOException.h
 *
 *  Created on: Nov 5, 2011
 *      Author: apple
 */

#ifndef CPPHIBERNATEIOEXCEPTION_H_
#define CPPHIBERNATEIOEXCEPTION_H_

#include "CppHibernateException.h"

namespace cppHibernate {

class CppHibernateIOException: public CppHibernateException {
public:
	CppHibernateIOException(const char *exceptionMsg):CppHibernateException(exceptionMsg){}
	virtual ~CppHibernateIOException() throw(){}
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEIOEXCEPTION_H_ */
