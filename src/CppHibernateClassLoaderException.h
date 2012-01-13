/*
 * CppHibernateClassLoaderException.h
 *
 *  Created on: Nov 5, 2011
 *      Author: apple
 */

#ifndef CPPHIBERNATECLASSLOADEREXCEPTION_H_
#define CPPHIBERNATECLASSLOADEREXCEPTION_H_

#include "CppHibernateException.h"

namespace cppHibernate {

class CppHibernateClassLoaderException: public CppHibernateException {
public:
	CppHibernateClassLoaderException(const char *exceptionMsg) :CppHibernateException(exceptionMsg) {}
	virtual ~CppHibernateClassLoaderException() throw () {}
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATECLASSLOADEREXCEPTION_H_ */
