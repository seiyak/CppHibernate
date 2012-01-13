/*
 * CppHibernateEntityStatistics.cpp
 *
 *  Created on: Dec 12, 2011
 *      Author: seiyak
 */

#include "CppHibernateEntityStatistics.h"

namespace cppHibernate {

const char *CppHibernateEntityStatistics::ORG_HIBERNATE_STAT_ENTITYSTATISTICS_GETDELETECOUNT_NAME =
		"getDeleteCount";
const char *CppHibernateEntityStatistics::ORG_HIBERNATE_STAT_ENTITYSTATISTICS_GETFETCHCOUNT_NAME =
		"getFetchCount";
const char *CppHibernateEntityStatistics::ORG_HIBERNATE_STAT_ENTITYSTATISTICS_GETINSERTCOUNT_NAME =
		"getInsertCount";
const char *CppHibernateEntityStatistics::ORG_HIBERNATE_STAT_ENTITYSTATISTICS_GETLOADCOUNT_NAME =
		"getLoadCount";
const char *CppHibernateEntityStatistics::ORG_HIBERNATE_STAT_ENTITYSTATISTICS_GETOPTIMISTICFAILURECOUNT =
		"getOptimisticFailureCount";
const char *CppHibernateEntityStatistics::ORG_HIBERNATE_STAT_ENTITYSTATISTICS_GETUPDATECOUNT_NAME =
		"getUpdateCount";

CppHibernateEntityStatistics::CppHibernateEntityStatistics(JNIEnv *env,
		jobject obj, jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateStatisticsBase(env, obj, objClass, classLoader) {

}

long CppHibernateEntityStatistics::getDeleteCount() {

	return this->getCount(
			CppHibernateEntityStatistics::ORG_HIBERNATE_STAT_ENTITYSTATISTICS_GETDELETECOUNT_NAME);
}

long CppHibernateEntityStatistics::getFetchCount() {

	return this->getCount(
			CppHibernateEntityStatistics::ORG_HIBERNATE_STAT_ENTITYSTATISTICS_GETFETCHCOUNT_NAME);
}

long CppHibernateEntityStatistics::getInsertCount() {
	return this->getCount(
			CppHibernateEntityStatistics::ORG_HIBERNATE_STAT_ENTITYSTATISTICS_GETINSERTCOUNT_NAME);
}

long CppHibernateEntityStatistics::getLoadCount() {
	return this->getCount(
			CppHibernateEntityStatistics::ORG_HIBERNATE_STAT_ENTITYSTATISTICS_GETLOADCOUNT_NAME);
}

long CppHibernateEntityStatistics::getOptimisticFailureCount() {
	return this->getCount(
			CppHibernateEntityStatistics::ORG_HIBERNATE_STAT_ENTITYSTATISTICS_GETOPTIMISTICFAILURECOUNT);
}

long CppHibernateEntityStatistics::getUpdateCount() {
	return this->getCount(
			CppHibernateEntityStatistics::ORG_HIBERNATE_STAT_ENTITYSTATISTICS_GETUPDATECOUNT_NAME);
}

CppHibernateEntityStatistics::~CppHibernateEntityStatistics() {

}

} /* namespace cppHibernate */
