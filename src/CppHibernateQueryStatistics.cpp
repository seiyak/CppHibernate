/*
 * CppHibernateQueryStatistics.cpp
 *
 *  Created on: Dec 12, 2011
 *      Author: seiyak
 */

#include "CppHibernateQueryStatistics.h"

namespace cppHibernate {

const char *CppHibernateQueryStatistics::ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETCACHEHITCOUNT_NAME =
		"getCacheHitCount";
const char *CppHibernateQueryStatistics::ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETCACHEMISS_COUNT_NAME =
		"getCacheMissCount";
const char *CppHibernateQueryStatistics::ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETCACHEPUTCOUNT_NAME =
		"getCachePutCount";
const char *CppHibernateQueryStatistics::ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETEXECUTIONAVGTIME_NAME =
		"getExecutionAvgTime";
const char *CppHibernateQueryStatistics::ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETEXECUTIONCOUNT_NAME =
		"getExecutionCount";
const char *CppHibernateQueryStatistics::ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETEXECUTIONMAXTIME_NAME =
		"getExecutionMaxTime";
const char *CppHibernateQueryStatistics::ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETEXECUTIONMINTIME_NAME =
		"getExecutionMinTime";
const char *CppHibernateQueryStatistics::ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETEXECUTIONROWCOUNT_NAME =
		"getExecutionRowCount";

CppHibernateQueryStatistics::CppHibernateQueryStatistics(JNIEnv *env,
		jobject obj, jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateStatisticsBase(env, obj, objClass, classLoader) {

}

long CppHibernateQueryStatistics::getCacheHitCount() {
	return this->getCount(
			CppHibernateQueryStatistics::ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETCACHEHITCOUNT_NAME);
}

long CppHibernateQueryStatistics::getCahceMissCount() {
	return this->getCount(
			CppHibernateQueryStatistics::ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETCACHEMISS_COUNT_NAME);
}

long CppHibernateQueryStatistics::getCachePutCount() {
	return this->getCount(
			CppHibernateQueryStatistics::ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETCACHEPUTCOUNT_NAME);
}

long CppHibernateQueryStatistics::getExecutionAvgTime() {
	return this->getCount(
			CppHibernateQueryStatistics::ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETEXECUTIONAVGTIME_NAME);
}

long CppHibernateQueryStatistics::getExecutionCount() {
	return this->getCount(
			CppHibernateQueryStatistics::ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETEXECUTIONCOUNT_NAME);
}

long CppHibernateQueryStatistics::getExecutionMaxTime() {
	return this->getCount(
			CppHibernateQueryStatistics::ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETEXECUTIONMAXTIME_NAME);
}

long CppHibernateQueryStatistics::getExecutionMinTime() {
	return this->getCount(
			CppHibernateQueryStatistics::ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETEXECUTIONMINTIME_NAME);
}

long CppHibernateQueryStatistics::getExecutionRowCount() {
	return this->getCount(
			CppHibernateQueryStatistics::ORG_HIBERNATE_STAT_QUERYSTATISTICS_GETEXECUTIONROWCOUNT_NAME);
}

CppHibernateQueryStatistics::~CppHibernateQueryStatistics() {

}

} /* namespace cppHibernate */
