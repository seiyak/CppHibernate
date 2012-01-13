/*
 * CppHibernateSessionStatistics.h
 *
 *  Created on: Dec 9, 2011
 *      Author: seiyak
 */

#ifndef CPPHIBERNATESESSIONSTATISTICS_H_
#define CPPHIBERNATESESSIONSTATISTICS_H_

#include "CppHibernateStatisticsBase.h"
#include "CppHibernateJCollectionObject.h"

namespace cppHibernate {

class CppHibernateSessionStatistics: public CppHibernateStatisticsBase {

public:
	static const char *ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETCOLLECTIONCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETCOLLECTIONCOUNT_SIGNATURE;
	static const char *ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETCOLLECTIONKEYS_NAME;
	static const char *ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETCOLLECTIONKEYS_SIGNATURE;
	static const char *ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETENTITYCOUNT_NAME;
	static const char *ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETENTITYCOUNT_SIGNATURE;
	static const char *ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETENTITYKEYS_NAME;
	static const char *ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETENTITYKEYS_SIGNATURE;

	CppHibernateSessionStatistics(JNIEnv *, jobject, jclass,
			AbstractClassLoader *);
	int getCollectionCount();
	CppHibernateJCollectionObject *getCollectionKeys();
	int getEntityCount();
	CppHibernateJCollectionObject *getEntityKeys();
	const char *toString();
	virtual ~CppHibernateSessionStatistics();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATESESSIONSTATISTICS_H_ */
