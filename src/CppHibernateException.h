/*
 * CppHibernateException.h
 *
 *  Created on: Nov 4, 2011
 *      Author: apple
 */

#ifndef CPPHIBERNATEEXCEPTION_H_
#define CPPHIBERNATEEXCEPTION_H_

#include <stdexcept>

namespace cppHibernate {

class CppHibernateException: public std::runtime_error {

public:
	CppHibernateException(const char *exceptionMsg) :
			std::runtime_error(""), exceptionMessage(exceptionMsg) {}
	virtual ~CppHibernateException() throw () {}
	virtual const char *what()const throw(){return exceptionMessage;}

private:
	const char *exceptionMessage;
};

}

#endif /* CPPHIBERNATEEXCEPTION_H_ */
