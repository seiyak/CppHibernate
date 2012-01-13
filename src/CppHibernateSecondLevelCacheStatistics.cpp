/*
 * CppHibernateSecondLevelCacheStatistics.cpp
 *
 *  Created on: Dec 12, 2011
 *      Author: seiyak
 */

#include "CppHibernateSecondLevelCacheStatistics.h"

namespace cppHibernate {

const char *CppHibernateSecondLevelCacheStatistics::ORG_HIBERNATE_STAT_SECONDLEVELCACHESTATISTICS_GETELEMENTCOUNTINMEMORY_NAME =
		"getElementCountInMemory";
const char *CppHibernateSecondLevelCacheStatistics::ORG_HIBERNATE_STAT_SECONDLEVELCACHESTATISTICS_GETELEMENTCOUNTONDISK_NAME =
		"getElementCountOnDisk";
const char *CppHibernateSecondLevelCacheStatistics::ORG_HIBERNATE_STAT_SECONDLEVELCACHESTATISTICS_GETHITCOUNT_NAME =
		"getHitCount";
const char *CppHibernateSecondLevelCacheStatistics::ORG_HIBERNATE_STAT_SECONDLEVELCACHESTATISTICS_GETMISSCOUNT_NAME =
		"getMissCount";
const char *CppHibernateSecondLevelCacheStatistics::ORG_HIBERNATE_STAT_SECONDLEVELCACHESTATISTICS_GETPUTCOUNT_NAME =
		"getPutCount";
const char *CppHibernateSecondLevelCacheStatistics::ORG_HIBERNATE_STAT_SECONDLEVELCACHESTATISTICS_GETSIZEINMEMORY_NAME =
		"getSizeInMemory";

CppHibernateSecondLevelCacheStatistics::CppHibernateSecondLevelCacheStatistics(
		JNIEnv *env, jobject obj, jclass objClass,
		AbstractClassLoader *classLoader) :
		CppHibernateStatisticsBase(env, obj, objClass, classLoader) {

}

long CppHibernateSecondLevelCacheStatistics::getElementCountInMemory() {
	return this->getCount(
			CppHibernateSecondLevelCacheStatistics::ORG_HIBERNATE_STAT_SECONDLEVELCACHESTATISTICS_GETELEMENTCOUNTINMEMORY_NAME);
}

long CppHibernateSecondLevelCacheStatistics::getElementCountOnDisk() {
	return this->getCount(
			CppHibernateSecondLevelCacheStatistics::ORG_HIBERNATE_STAT_SECONDLEVELCACHESTATISTICS_GETELEMENTCOUNTONDISK_NAME);
}

long CppHibernateSecondLevelCacheStatistics::getHitCount() {
	return this->getCount(
			CppHibernateSecondLevelCacheStatistics::ORG_HIBERNATE_STAT_SECONDLEVELCACHESTATISTICS_GETHITCOUNT_NAME);
}

long CppHibernateSecondLevelCacheStatistics::getMissCount() {
	return this->getCount(
			CppHibernateSecondLevelCacheStatistics::ORG_HIBERNATE_STAT_SECONDLEVELCACHESTATISTICS_GETMISSCOUNT_NAME);
}

long CppHibernateSecondLevelCacheStatistics::getPutCount() {
	return this->getCount(
			CppHibernateSecondLevelCacheStatistics::ORG_HIBERNATE_STAT_SECONDLEVELCACHESTATISTICS_GETPUTCOUNT_NAME);
}

long CppHibernateSecondLevelCacheStatistics::getSizeInMemory() {
	return this->getCount(
			CppHibernateSecondLevelCacheStatistics::ORG_HIBERNATE_STAT_SECONDLEVELCACHESTATISTICS_GETSIZEINMEMORY_NAME);
}

CppHibernateSecondLevelCacheStatistics::~CppHibernateSecondLevelCacheStatistics() {

}

} /* namespace cppHibernate */
