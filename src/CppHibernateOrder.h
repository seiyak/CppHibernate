/*
 * CppHibernateOrder.h
 *
 *  Created on: Dec 6, 2011
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEORDER_H_
#define CPPHIBERNATEORDER_H_

#include "CppHibernateCommons.h"

namespace cppHibernate {

class CppHibernateOrder: public cppHibernate::CppHibernateCommons {

private:
	jobject findAscOrDes(bool isAsc = true);

public:
	static const char *ORG_HIBERNATE_CRITERION_ASC_NAME;
	static const char *ORG_HIBERNATE_CRITERION_ASC_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERION_DESC_NAME;
	static const char *ORG_HIBERNATE_CRITERION_DESC_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERION_IGNORECASE_NAME;
	static const char *ORG_HIBERNATE_CRITERION_IGNORECASE_SIGNATURE;
	static const char *ORG_HIBERNATE_CRITERION_TOSTRING_NAME;
	static const char *ORG_HIBERNATE_CRITERION_TOSTRING_SIGNATURE;

	CppHibernateOrder(JNIEnv*, jobject, jclass, AbstractClassLoader *);
	CppHibernateOrder& asc(const char *);
	CppHibernateOrder& desc(const char *);
	CppHibernateOrder& ignoreCase();
	virtual ~CppHibernateOrder();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEORDER_H_ */
