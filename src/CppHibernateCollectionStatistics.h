/*
 * CppHibernateCollectionStatistics.h
 *
 *  Created on: Dec 9, 2011
 *      Author: seiyak
 */

#ifndef CPPHIBERNATECOLLECTIONSTATISTICS_H_
#define CPPHIBERNATECOLLECTIONSTATISTICS_H_

#include "CppHibernateStatisticsBase.h"

namespace cppHibernate {

class CppHibernateCollectionStatistics: public CppHibernateStatisticsBase {

public:
	static const char *ORG_HIBERNATE_STAT_COLLECTIONSTATISTICS_GETFETCHCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_COLLECTIONSTATISTICS_GETLOADCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_COLLECTIONSTATISTICS_GETRECREATECOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_COLLECTIONSTATISTICS_GETREMOVECOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_COLLECTIONSTATISTICS_GETUPDATECOUNT_NAME;
	static const char *LONGRETURN_VOIDPARAM_SIGNATURE;

	CppHibernateCollectionStatistics(JNIEnv*, jobject, jclass,
			AbstractClassLoader *);
	long getFetchCount();
	long getLoadCount();
	long getRecreateCount();
	long getRemoveCount();
	long getUpdateCount();
	virtual ~CppHibernateCollectionStatistics();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATECOLLECTIONSTATISTICS_H_ */
