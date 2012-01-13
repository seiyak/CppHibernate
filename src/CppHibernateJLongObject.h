/*
 * CppHibernateJLongObject.h
 *
 *  Created on: Nov 28, 2011
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEJLONGOBJECT_H_
#define CPPHIBERNATEJLONGOBJECT_H_

#include "CppHibernateJObject.h"

namespace cppHibernate {

class CppHibernateJLongObject: public cppHibernate::CppHibernateJObject {
public:
	static const char *JAVA_LANG_LONG;
	static const char *JAVA_LANG_LONG_SIGNATURE;
	static const char *JAVA_LANG_LONG_PRIMITIVE_SIGNATURE;
	static const char *JAVA_LANG_LONG_LONGVALUE_NAME;
	static const char *JAVA_LANG_LONG_LONGVALUE_SIGNATURE;

	CppHibernateJLongObject(JNIEnv *, jobject, jclass, AbstractClassLoader *);
	long getVal();
	void setVal(long val = 0);
	virtual ~CppHibernateJLongObject();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEJLONGOBJECT_H_ */
