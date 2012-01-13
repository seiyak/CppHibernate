/*
 * CppHibernateSession.h
 *
 *  Created on: Nov 10, 2011
 *      Author: apple
 */

#ifndef CPPHIBERNATESESSION_H_
#define CPPHIBERNATESESSION_H_

#include "CppHibernateCommons.h"
#include "CppHibernateTransaction.h"
#include "CppHibernateConnection.h"
#include "CppHibernateJObject.h"
#include "CppHibernateCriteria.h"
#include "CppHibernateQuery.h"
#include "CppHibernateSessionStatistics.h"

namespace cppHibernate {

class CppHibernateSession: public CppHibernateCommons {

private:
	void checkNull(CppHibernateJObject *);
	bool checkFlushMode(const char *);
	jobject findFlushMode(const char *);

public:
	static const char *ORG_HIBERNATE_TRANSACTION;
	static const char *ORG_HIBERNATE_SESSION_CLOSE_NAME;
	static const char *ORG_HIBERNATE_SESSION_CLOSE_SIGNATURE;
	static const char *ORG_HIBERNATE_SESSION_BEGINTRANSACTION_NAME;
	static const char *ORG_HIBERNATE_SESSION_BEGINTRANSACTION_SIGNATURE;
	static const char *ORG_HIBERNATE_SESSION_ISOPEN_NAME;
	static const char *ORG_HIBERNATE_SESSION_ISOPEN_SIGNATURE;
	static const char *ORG_HIBERNATE_SESSION_SAVE_NAME;
	static const char *ORG_HIBERNATE_SESSION_SAVE_SIGNATURE;
	static const char *ORG_HIBERNATE_SESSION_DELETE_NAME;
	static const char *ORG_HIBERNATE_SESSION_DELETE_SIGNATURE;
	static const char *ORG_HIBERNATE_SESSION_UPDATE_NAME;
	static const char *ORG_HIBERNATE_SESSION_UPDATE_SIGNATURE;
	static const char *ORG_HIBERNATE_SESSION_FLUSH_NAME;
	static const char *ORG_HIBERNATE_SESSION_FLUSH_SIGNATURE;
	static const char *ORG_HIBERNATE_FLUSHMODE;
	static const char *ORG_HIBERNATE_FLUSHMODE_SIGNATURE;
	static const char *ORG_HIBERNATE_SESSION_SETFLUSHMODE_NAME;
	static const char *ORG_HIBERNATE_SESSION_SETFLUSHMODE_SIGNATURE;
	static const char *ORG_HIBERNATE_SESSION_CREATECRITERIA_NAME;
	static const char *ORG_HIBERNATE_SESSION_CREATECRITERIA_SIGNATURE;
	static const char *ORG_HIBERNATE_SESSION_CREATEQUERY_NAME;
	static const char *ORG_HIBERNATE_SESSION_CREATEQUERY_SIGNATURE;
	static const char *ORG_HIBERNATE_SESSION_GETSTATISTICS_NAME;
	static const char *ORG_HIBERNATE_SESSION_GETSTATISTICS_SIGNATURE;
	static const char *FLUSHMODE_ALWAYS;
	static const char *FLUSHMODE_AUTO;
	static const char *FLUSHMODE_COMMIT;
	static const char *FLUSHMODE_MANUAL;
	static const char *JAVA_SQL_CONNECTION;

	CppHibernateSession(JNIEnv*, jobject, jclass, AbstractClassLoader *);
	CppHibernateTransaction *beginTransaction();
	CppHibernateConnection *close(bool closedConnection = false);
	void saveObj(CppHibernateJObject *);
	void deleteObj(CppHibernateJObject *);
	void updateObj(CppHibernateJObject *);
	void flush();
	void setFlushMode(const char *flushMode = "COMMIT");
	CppHibernateCriteria createCriteria(CppHibernateJObject *);
	CppHibernateQuery createQuery(const char *);
	bool isOpen();
	CppHibernateSessionStatistics *getStatistics();
	virtual ~CppHibernateSession();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATESESSION_H_ */
