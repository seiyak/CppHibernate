/*
 * CppHibernateStatistics.h
 *
 *  Created on: Dec 9, 2011
 *      Author: seiyak
 */

#ifndef CPPHIBERNATESTATISTICS_H_
#define CPPHIBERNATESTATISTICS_H_

#include <deque>
#include "CppHibernateStatisticsBase.h"
#include "CppHibernateCollectionStatistics.h"
#include "CppHibernateEntityStatistics.h"
#include "CppHibernateQueryStatistics.h"
#include "CppHibernateSecondLevelCacheStatistics.h"

namespace cppHibernate {

class CppHibernateStatistics: public CppHibernateStatisticsBase {

private:
	std::deque<std::string> convertFrom(jobject);
	std::deque<std::string> getNames(const char *);

public:
	static const char *ORG_HIBERNATE_STAT_STATISTICS_CLEAR_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_CLEAR_SIGNATURE;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETCLOSESTATEMENTCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONFETCHCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONLOADCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONRECREATECOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONREMOVECOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONROLENAMES_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONSTATISTICS_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONSTATISTICS_SIGNATURE;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONUPDATECOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETCONNECTCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETENTITYDELETECOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETENTITYFETCHCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETENTITYINSERTCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETENTITYLOADCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETENTITYNAMES_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETENTITYSTATISTICS_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETENTITYSTATISTICS_SIGNATURE;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETENTITYUPDATECOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETFLUSHCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETOPTMISTICFAILURECOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETPREPARESTATEMENTCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETQUERIES_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETQUERYCACHEHITCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETQUERYCACHEMISSCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETQUERYCACHEPUTCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETQUERYEXECUTIONCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETQUERYEXECUTIONMAXTIME_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETQUERYEXECUTIONMAXTIMEQUERYSTRING_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETQUERYEXECUTIONMAXTIMEQUERYSTRING_SIGNATURE;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETQUERYSTATISTICS_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETQUERYSTATISTICS_SIGNATURE;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETSECONDLEVELCACHEHITCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETSECONDLEVELCACHEMISSCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETSECONDLEVELCACHEPUTCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETSECONDLEVELCACHEREGIONNAMES_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETSECONDLEVELCACHESTATISTICS_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETSECONDLEVELCACHESTATISTICS_SIGNATURE;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETSESSIONCLOSECOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETSESSIONOPENCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETSTARTTIME_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETSUCCESSFULTRANSACTIONCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_GETTRANSACTIONCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_ISSTATISCTICSENABLED_NAME;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_ISSTATISCTICSENABLED_SIGNATURE;
	static const char *ORG_HIBERNATE_STAT_STATISTICS_SETSTATISTICSENABLED_NAME;
	static const char *STRINGARRAYRETURN_VOIDPARAM_SIGNATURE;

	CppHibernateStatistics(JNIEnv *, jobject, jclass, AbstractClassLoader *);
	void clear();
	long getCloseStatementCount();
	long getCollectionFetchCount();
	long getCollectionLoadCount();
	long getCollectionRecreateCount();
	long getCollectionRemoveCount();
	std::deque<std::string> getCollectionRoleNames();
	CppHibernateCollectionStatistics *getCollectionStatistics(const char *);
	long getCollectionUpdateCount();
	long getConnectCount();
	long getEntityDeleteCount();
	long getEntityFetchCount();
	long getEntityInsertCount();
	long getEntityLoadCount();
	std::deque<std::string> getEntityNames();
	CppHibernateEntityStatistics *getEntityStatistics(const char*);
	long getEntityUpdateCount();
	long getFlushCount();
	long getOptimisticFailureCount();
	long getPrepareStatementCount();
	std::deque<std::string> getQueries();
	long getQueryCacheHitCount();
	long getQueryCacheMissCount();
	long getQueryCachePutCount();
	long getQueryExecutionCount();
	long getQueryExecutionMaxTime();
	std::string getQueryExecutionMaxTimeQueryString();
	CppHibernateQueryStatistics *getQueryStatistics(const char *);
	long getSecondLevelCacheHitCount();
	long getSecondLevelCacheMissCount();
	long getSecondLevelCachePutCount();
	std::deque<std::string> getSecondLevelCacheRegionNames();
	CppHibernateSecondLevelCacheStatistics *getSecondLevelCacheStatistics(
			const char *);
	long getSessionCloseCount();
	long getSessionOpenCount();
	long getStartTime();
	long getSuccessfulTransactionCount();
	long getTransactionCount();
	bool isStatisticsEnabled();
	virtual ~CppHibernateStatistics();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATESTATISTICS_H_ */
