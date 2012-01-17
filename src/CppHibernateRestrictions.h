/*
 * CppHibernateRestrictions.h
 *
 *  Created on: Dec 6, 2011
 *      Author: seiyak
 */

#ifndef CPPHIBERNATERESTRICTIONS_H_
#define CPPHIBERNATERESTRICTIONS_H_

#include "CppHibernateCommons.h"
#include "CppHibernateJObject.h"
#include "CppHibernateJStringObject.h"
#include "CppHibernateMatchMode.h"

namespace cppHibernate {

class CppHibernateRestrictions: public CppHibernateCommons {

private:
	void deleteObj(CppHibernateJObject *&);
	CppHibernateRestrictions callForStringObjectParams(jobject, const char *,
			CppHibernateJObject *&);
	jobject getMatchMode(const char *);
	jobject createMatchMode(const char *);
	jobject convertFrom(std::deque<CppHibernateJObject*>&);
	CppHibernateRestrictions callForNull(jobject, const char *);
	CppHibernateRestrictions callForLike(jobject, const char *,
			CppHibernateJStringObject *&, const char *);

public:
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_EQ_NAME;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_EQ_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_GE_NAME;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_GE_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_GT_NAME;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_GT_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_LE_NAME;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_LE_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_LT_NAME;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_LT_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_NE_NAME;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_NE_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_ILIKE_NAME;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_ILIKE_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_LIKE_NAME;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_LIKE_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_IDEQ_NAME;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_IDEQ_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_BETWEEN_NAME;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_BETWEEN_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_IN_NAME;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_IN_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_ISNOTNULL_NAME;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_ISNOTNULL_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_ISNULL_NAME;
	static const char *ORG_HIBERNATE_CRITERION_RESTRICTIONS_ISNULL_SIGNATURE;

	static const char *ORG_HIBERNATE_CRITERION_MATCHMODE_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERION_MATCHMODE;
	static const char *MATCHMODE_ANYWHERE;
	static const char *MATCHMODE_END;
	static const char *MATCHMODE_EXACT;
	static const char *MATCHMODE_START;

	CppHibernateRestrictions(JNIEnv *, jobject, jclass, AbstractClassLoader *);

	CppHibernateRestrictions eq(const char *, CppHibernateJObject *&);
	CppHibernateRestrictions ge(const char *, CppHibernateJObject *&);
	CppHibernateRestrictions gt(const char *, CppHibernateJObject *&);
	CppHibernateRestrictions le(const char *, CppHibernateJObject *&);
	CppHibernateRestrictions lt(const char *, CppHibernateJObject *&);
	CppHibernateRestrictions ne(const char *, CppHibernateJObject *&);
	CppHibernateRestrictions idEq(CppHibernateJObject *&);
	CppHibernateRestrictions between(const char *, CppHibernateJObject *&,
			CppHibernateJObject *&);
	CppHibernateRestrictions ilike(const char *, CppHibernateJStringObject *&,
			CppHibernateMatchMode matchMode = CppHibernateMatchMode::START);
	CppHibernateRestrictions like(const char *, CppHibernateJStringObject *&,
			CppHibernateMatchMode matchMode = CppHibernateMatchMode::START);
	CppHibernateRestrictions in(const char *,
			std::deque<CppHibernateJObject*>&);
	CppHibernateRestrictions isNotNULL(const char *);
	CppHibernateRestrictions isNULL(const char *);
	virtual ~CppHibernateRestrictions();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATERESTRICTIONS_H_ */
