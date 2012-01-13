/*
 * CppHibernateJIntegerObject.h
 *
 *  Created on: Nov 22, 2011
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEJINTEGEROBJECT_H_
#define CPPHIBERNATEJINTEGEROBJECT_H_

#include "CppHibernateJObject.h"

namespace cppHibernate {

class CppHibernateJIntegerObject: public cppHibernate::CppHibernateJObject {

public:
	static const char *JAVA_LANG_INTEGER;
	static const char *JAVA_LANG_INTEGER_SIGNATURE;
	static const char *JAVA_LANG_INTEGER_PRIMITIVE_SIGNATURE;
	static const char *JAVA_LANG_INTEGER_INTVALUE_NAME;
	static const char *JAVA_LANG_INTEGER_INTVALUE_SIGNATURE;

	CppHibernateJIntegerObject(JNIEnv *, jobject, jclass, AbstractClassLoader*);
	int getVal();
	void setVal(int val = 0);
	virtual ~CppHibernateJIntegerObject();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEJINTEGEROBJECT_H_ */
