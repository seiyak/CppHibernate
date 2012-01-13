/*
 * CppHibernateCriteria.h
 *
 *  Created on: Dec 5, 2011
 *      Author: seiyak
 */

#ifndef CPPHIBERNATECRITERIA_H_
#define CPPHIBERNATECRITERIA_H_

#include "CppHibernateCommons.h"
#include "CppHibernateJObject.h"
#include "CppHibernateRestrictions.h"
#include "CppHibernateJStringObject.h"
#include "CppHibernateJCollectionObject.h"
#include "CppHibernateMatchMode.h"

namespace cppHibernate {

class CppHibernateCriteria: public cppHibernate::CppHibernateCommons {

private:
	void checkAliasParams(const char *, const char *);
	jobject findAddOrderId();
	jobject orderAsc(jobject, jmethodID, const char *, bool);
	jobject orderDesc(jobject, jmethodID, const char *, bool);
	jobject findAddId();
	jobject loadRestrictionsClass();
	CppHibernateCriteria& add(jobject, CppHibernateRestrictions&);

public:
	static const char *ORG_HIBERNATE_CRITERIA_LIST_NAME;
	static const char *ORG_HIBERNATE_CRITERIA_LIST_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERIA_CREATEALIAS_NAME;
	static const char *ORG_HIBERNATE_CRITERIA_CREATEALIAS_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERION_ORDER;
	static const char *ORG_HIBERNATE_CRITERIA_ADDORDER_NAME;
	static const char *ORG_HIBERNATE_CRITERIA_ADDORDER_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERIA_ADD_NAME;
	static const char *ORG_HIBERNATE_CRITERIA_ADD_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS;
	static const char *ORG_HIBERNATE_CRITERIA_SETCACHEABLE_NAME;
	static const char *ORG_HIBERNATE_CRITERIA_SETCACHEABLE_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERIA_SETCACHEREGION_NAME;
	static const char *ORG_HIBERNATE_CRITERIA_SETCACHEREGION_SIGNATURE;

	CppHibernateCriteria(JNIEnv *, jobject, jclass, AbstractClassLoader *);
	CppHibernateJCollectionObject *list();
	CppHibernateCriteria& createAlias(const char *, const char*);
	CppHibernateCriteria& addOrderAsc(const char *, bool ignoreCase = false);
	CppHibernateCriteria& addOrderDesc(const char *, bool ignoreCase = false);
	CppHibernateCriteria& addEq(const char *, CppHibernateJObject *);
	CppHibernateCriteria& addGe(const char *, CppHibernateJObject *);
	CppHibernateCriteria& addGt(const char *, CppHibernateJObject *);
	CppHibernateCriteria& addLe(const char *, CppHibernateJObject *);
	CppHibernateCriteria& addLt(const char *, CppHibernateJObject *);
	CppHibernateCriteria& addNe(const char *, CppHibernateJObject *);
	CppHibernateCriteria& addIlike(const char *, CppHibernateJStringObject*,
			CppHibernateMatchMode matchMode = CppHibernateMatchMode::START);
	CppHibernateCriteria& addLike(const char *, CppHibernateJStringObject *,
			CppHibernateMatchMode matchMode = CppHibernateMatchMode::START);
	CppHibernateCriteria& addIdEq(CppHibernateJObject*);
	CppHibernateCriteria& addBetween(const char *, CppHibernateJObject *,
			CppHibernateJObject *);
	CppHibernateCriteria& addIn(const char *,
			std::deque<CppHibernateJObject *>&);
	CppHibernateCriteria& addIsNotNULL(const char *);
	CppHibernateCriteria& addIsNULL(const char *);
	CppHibernateCriteria& setCachable(bool);
	CppHibernateCriteria& setCacheRegion(const char *);

	virtual ~CppHibernateCriteria();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATECRITERIA_H_ */
