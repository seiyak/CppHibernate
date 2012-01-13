/*
 * CppHibernateTransaction.h
 *
 *  Created on: Nov 11, 2011
 *      Author: apple
 */

#ifndef CPPHIBERNATETRANSACTION_H_
#define CPPHIBERNATETRANSACTION_H_

#include "CppHibernateCommons.h"

namespace cppHibernate {

class CppHibernateTransaction: public cppHibernate::CppHibernateCommons {

protected:
	const char *ORG_HIBERNATE_TRANSACTION_COMMIT_NAME;
	const char *ORG_HIBERNATE_TRANSACTION_ROLLBACK_NAME;

public:
	CppHibernateTransaction(JNIEnv*, jobject, jclass, AbstractClassLoader*);
	void commit();
	void rollback();
	virtual ~CppHibernateTransaction();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATETRANSACTION_H_ */
