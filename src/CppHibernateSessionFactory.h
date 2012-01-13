/*
 * CppHibernateSessionFactory.h
 *
 *  Created on: Nov 10, 2011
 *      Author: apple
 */

#ifndef CPPHIBERNATESESSIONFACTORY_H_
#define CPPHIBERNATESESSIONFACTORY_H_

#include "CppHibernateCommons.h"
#include "CppHibernateSession.h"
#include "CppHibernateStatistics.h"

namespace cppHibernate {

class CppHibernateSessionFactory: public CppHibernateCommons {

public:
	static const char *ORG_HIBERNATE_CLASSIC_SESSION;
	static const char *ORG_HIBERNATE_SESSIONFACTORY_OPENSESSION_NAME;
	static const char *ORG_HIBERNATE_SESSIONFACTORY_OPENSESSION_SIGNATURE;
	static const char *ORG_HIBERNATE_SESSIONFACTORY_GETCURRENTSESSION_NAME;
	static const char *ORG_HIBERNATE_SESSIONFACTORY_GETCURRENTSESSION_SIGNATURE;
	static const char *ORG_HIBERNATE_SESSIONFACTORY_CLOSE_NAME;
	static const char *ORG_HIBERNATE_SESSIONFACTORY_CLOSE_SIGNATURE;
	static const char *ORG_HIBERNATE_SESSIONFACTORY_ISCLOSED_NAME;
	static const char *ORG_HIBERNATE_SESSIONFACTORY_ISCLOSED_SIGNATURE;
	static const char *ORG_HIBERNATE_SESSIONFACTORY_GETSTATISTICS_NAME;
	static const char *ORG_HIBERNATE_SESSIONFACTORY_GETSTATISTICS_SIGNATURE;

	CppHibernateSessionFactory(JNIEnv*, jobject, jclass, AbstractClassLoader *);
	CppHibernateSession *openSession();
	CppHibernateSession *getCurrentSession();
	void close();
	bool isClosed();
	CppHibernateStatistics *getStatistics();
	virtual ~CppHibernateSessionFactory();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATESESSIONFACTORY_H_ */
