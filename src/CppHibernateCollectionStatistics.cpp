/*
 * CppHibernateCollectionStatistics.cpp
 *
 *  Created on: Dec 9, 2011
 *      Author: seiyak
 */

#include "CppHibernateCollectionStatistics.h"

namespace cppHibernate {

const char *CppHibernateCollectionStatistics::ORG_HIBERNATE_STAT_COLLECTIONSTATISTICS_GETFETCHCOUNT_NAME =
		"getFetchCount";
const char *CppHibernateCollectionStatistics::ORG_HIBERNATE_STAT_COLLECTIONSTATISTICS_GETLOADCOUNT_NAME =
		"getLoadCount";
const char *CppHibernateCollectionStatistics::ORG_HIBERNATE_STAT_COLLECTIONSTATISTICS_GETRECREATECOUNT_NAME =
		"getRecreateCount";
const char *CppHibernateCollectionStatistics::ORG_HIBERNATE_STAT_COLLECTIONSTATISTICS_GETREMOVECOUNT_NAME =
		"getRemoveCount";
const char *CppHibernateCollectionStatistics::ORG_HIBERNATE_STAT_COLLECTIONSTATISTICS_GETUPDATECOUNT_NAME =
		"getUpdateCount";
const char *CppHibernateCollectionStatistics::LONGRETURN_VOIDPARAM_SIGNATURE =
		"()J";

CppHibernateCollectionStatistics::CppHibernateCollectionStatistics(JNIEnv *env,
		jobject obj, jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateStatisticsBase(env, obj, objClass, classLoader) {

}

long CppHibernateCollectionStatistics::getFetchCount() {

	return this->getCount(
			CppHibernateCollectionStatistics::ORG_HIBERNATE_STAT_COLLECTIONSTATISTICS_GETFETCHCOUNT_NAME);
}

long CppHibernateCollectionStatistics::getLoadCount() {

	return this->getCount(
			CppHibernateCollectionStatistics::ORG_HIBERNATE_STAT_COLLECTIONSTATISTICS_GETLOADCOUNT_NAME);
}

long CppHibernateCollectionStatistics::getRecreateCount() {
	return this->getCount(
			CppHibernateCollectionStatistics::ORG_HIBERNATE_STAT_COLLECTIONSTATISTICS_GETRECREATECOUNT_NAME);
}

long CppHibernateCollectionStatistics::getRemoveCount() {
	return this->getCount(
			CppHibernateCollectionStatistics::ORG_HIBERNATE_STAT_COLLECTIONSTATISTICS_GETREMOVECOUNT_NAME);
}

long CppHibernateCollectionStatistics::getUpdateCount() {
	return this->getCount(
			CppHibernateCollectionStatistics::ORG_HIBERNATE_STAT_COLLECTIONSTATISTICS_GETUPDATECOUNT_NAME);
}

CppHibernateCollectionStatistics::~CppHibernateCollectionStatistics() {

}

} /* namespace cppHibernate */
