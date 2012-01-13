/*
 * CppHibernateStatisticsBase.h
 *
 *  Created on: Dec 12, 2011
 *      Author: seiyak
 */

#ifndef CPPHIBERNATESTATISTICSBASE_H_
#define CPPHIBERNATESTATISTICSBASE_H_

#include "CppHibernateCommons.h"

namespace cppHibernate {

class CppHibernateStatisticsBase: public cppHibernate::CppHibernateCommons {

protected:
	long getCount(const char *);

public:
	static const char *LONGRETURN_VOIDPARAM_SIGNATURE;

	CppHibernateStatisticsBase(JNIEnv *, jobject, jclass,
			AbstractClassLoader *);
	const char *toString();
	virtual ~CppHibernateStatisticsBase();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATESTATISTICSBASE_H_ */
