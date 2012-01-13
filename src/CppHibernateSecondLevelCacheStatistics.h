/*
 * CppHibernateSecondLevelCacheStatistics.h
 *
 *  Created on: Dec 12, 2011
 *      Author: seiyak
 */

#ifndef CPPHIBERNATESECONDLEVELCACHESTATISTICS_H_
#define CPPHIBERNATESECONDLEVELCACHESTATISTICS_H_

#include "CppHibernateStatisticsBase.h"

namespace cppHibernate {

class CppHibernateSecondLevelCacheStatistics: public cppHibernate::CppHibernateStatisticsBase {
public:
	static const char *ORG_HIBERNATE_STAT_SECONDLEVELCACHESTATISTICS_GETELEMENTCOUNTINMEMORY_NAME;
	static const char *ORG_HIBERNATE_STAT_SECONDLEVELCACHESTATISTICS_GETELEMENTCOUNTONDISK_NAME;
	static const char *ORG_HIBERNATE_STAT_SECONDLEVELCACHESTATISTICS_GETHITCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_SECONDLEVELCACHESTATISTICS_GETMISSCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_SECONDLEVELCACHESTATISTICS_GETPUTCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_SECONDLEVELCACHESTATISTICS_GETSIZEINMEMORY_NAME;

	//// TODO add Map getEntries()
	CppHibernateSecondLevelCacheStatistics(JNIEnv *, jobject, jclass,
			AbstractClassLoader *);
	long getElementCountInMemory();
	long getElementCountOnDisk();
	long getHitCount();
	long getMissCount();
	long getPutCount();
	long getSizeInMemory();
	virtual ~CppHibernateSecondLevelCacheStatistics();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATESECONDLEVELCACHESTATISTICS_H_ */
