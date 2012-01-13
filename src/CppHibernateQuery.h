/*
 * CppHibernateQuery.h
 *
 *  Created on: Dec 7, 2011
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEQUERY_H_
#define CPPHIBERNATEQUERY_H_

#include "CppHibernateCommons.h"
#include "CppHibernateJCollectionObject.h"
#include "CppHibernateJStringObject.h"

namespace cppHibernate {

class CppHibernateQuery: public cppHibernate::CppHibernateCommons {
public:
	static const char *ORG_HIBERNATE_QUERY_LIST_NAME;
	static const char *ORG_HIBERNATE_QUERY_LIST_SIGNATURE;
	static const char *ORG_HIBERNATE_QUERY_SETMAXRESULTS_NAME;
	static const char *ORG_HIBERNATE_QUERY_SETMAXRESULTS_SIGNATURE;
	static const char *ORG_HIBERNATE_QUERY_SETPARAMETER_NAME;
	static const char *ORG_HIBERNATE_QUERY_SETPARAMETER_SIGNATURE;
	static const char *ORG_HIBERNATE_QUERY_SETCACHEABLE_NAME;
	static const char *ORG_HIBERNATE_QUERY_SETCACHEABLE_SIGNATURE;
	static const char *ORG_HIBERNATE_QUERY_SETCACHEREGION_NAME;
	static const char *ORG_HIBERNATE_QUERY_SETCACHEREGION_SIGNATURE;

	CppHibernateQuery(JNIEnv *, jobject, jclass, AbstractClassLoader *);
	CppHibernateJCollectionObject *list();
	CppHibernateQuery& setMaxResults(jint);
	CppHibernateQuery& setParameter(CppHibernateJStringObject *,
			CppHibernateJObject *);
	CppHibernateQuery& setCacheable(bool);
	CppHibernateQuery& setCacheRegion(const char *);
	virtual ~CppHibernateQuery();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEQUERY_H_ */
