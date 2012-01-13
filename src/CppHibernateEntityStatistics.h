/*
 * CppHibernateEntityStatistics.h
 *
 *  Created on: Dec 12, 2011
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEENTITYSTATISTICS_H_
#define CPPHIBERNATEENTITYSTATISTICS_H_

#include "CppHibernateStatisticsBase.h"

namespace cppHibernate {

class CppHibernateEntityStatistics: public cppHibernate::CppHibernateStatisticsBase {
public:
	static const char *ORG_HIBERNATE_STAT_ENTITYSTATISTICS_GETDELETECOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_ENTITYSTATISTICS_GETFETCHCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_ENTITYSTATISTICS_GETINSERTCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_ENTITYSTATISTICS_GETLOADCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_ENTITYSTATISTICS_GETOPTIMISTICFAILURECOUNT;
	static const char *ORG_HIBERNATE_STAT_ENTITYSTATISTICS_GETUPDATECOUNT_NAME;

	CppHibernateEntityStatistics(JNIEnv *, jobject, jclass,
			AbstractClassLoader *);
	long getDeleteCount();
	long getFetchCount();
	long getInsertCount();
	long getLoadCount();
	long getOptimisticFailureCount();
	long getUpdateCount();
	virtual ~CppHibernateEntityStatistics();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEENTITYSTATISTICS_H_ */
