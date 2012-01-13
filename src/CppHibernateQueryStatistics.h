/*
 * CppHibernateQueryStatistics.h
 *
 *  Created on: Dec 12, 2011
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEQUERYSTATISTICS_H_
#define CPPHIBERNATEQUERYSTATISTICS_H_

#include "CppHibernateStatisticsBase.h"

namespace cppHibernate {

class CppHibernateQueryStatistics: public cppHibernate::CppHibernateStatisticsBase {
public:
	static const char *ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETCACHEHITCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETCACHEMISS_COUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETCACHEPUTCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETEXECUTIONAVGTIME_NAME;
	static const char *ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETEXECUTIONCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETEXECUTIONMAXTIME_NAME;
	static const char *ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETEXECUTIONMINTIME_NAME;
	static const char *ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETEXECUTIONROWCOUNT_NAME;

	CppHibernateQueryStatistics(JNIEnv *, jobject, jclass,
			AbstractClassLoader *);
	long getCacheHitCount();
	long getCahceMissCount();
	long getCachePutCount();
	long getExecutionAvgTime();
	long getExecutionCount();
	long getExecutionMaxTime();
	long getExecutionMinTime();
	long getExecutionRowCount();
	virtual ~CppHibernateQueryStatistics();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEQUERYSTATISTICS_H_ */
