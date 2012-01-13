/*
 * CppHibernateCommonExceptionChecks.h
 *
 *  Created on: Nov 10, 2011
 *      Author: apple
 */

#ifndef CPPHIBERNATECOMMONEXCEPTIONCHECKS_H_
#define CPPHIBERNATECOMMONEXCEPTIONCHECKS_H_

namespace cppHibernate {

class CppHibernateCommonExceptionChecks {
public:
	CppHibernateCommonExceptionChecks();
	virtual void throwException() = 0;
	virtual void checkAndThrow() = 0;
	virtual ~CppHibernateCommonExceptionChecks();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATECOMMONEXCEPTIONCHECKS_H_ */
