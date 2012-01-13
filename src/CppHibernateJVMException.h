/*
 * CppHibernateJVMException.h
 *
 *  Created on: Nov 6, 2011
 *      Author: apple
 */

#ifndef CPPHIBERNATEJVMEXCEPTION_H_
#define CPPHIBERNATEJVMEXCEPTION_H_

#include "CppHibernateException.h"

namespace cppHibernate {

class CppHibernateJVMException: public CppHibernateException {
public:
	CppHibernateJVMException(const char *exceptionMsg):CppHibernateException(exceptionMsg){}
	virtual ~CppHibernateJVMException() throw(){}
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEJVMEXCEPTION_H_ */
