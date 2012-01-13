/*
 * CppHibernateJBooleanObject.h
 *
 *  Created on: Nov 15, 2011
 *      Author: apple
 */

#ifndef CPPHIBERNATEJBOOLEANOBJECT_H_
#define CPPHIBERNATEJBOOLEANOBJECT_H_

#include <cstring>
#include "CppHibernateJObject.h"

namespace cppHibernate {

class CppHibernateJBooleanObject: public cppHibernate::CppHibernateJObject {

private:
	jobject createBooleanValue(bool val = false);

public:
	static const char *JAVA_LANG_BOOLEAN;
	static const char *JAVA_BOOLEAN_TRUE;
	static const char *JAVA_BOOLEAN_FALSE;
	static const char *JAVA_LANG_BOOLEAN_BOOLEANVALUE_NAME;
	static const char *JAVA_LANG_BOOLEAN_SIGNATURE;
	static const char *JAVA_LANG_BOOLEAN_PRIMITIVE_SIGNATURE;

	CppHibernateJBooleanObject(JNIEnv*, jobject, jclass, AbstractClassLoader*);
	const char *toString();
	bool getVal();
	void setVal(bool);
	bool equals(CppHibernateJBooleanObject *);
	virtual ~CppHibernateJBooleanObject();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEJBOOLEANOBJECT_H_ */
