/*
 * CppHibernateJDoubleObject.h
 *
 *  Created on: Nov 28, 2011
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEJDOUBLEOBJECT_H_
#define CPPHIBERNATEJDOUBLEOBJECT_H_

#include "CppHibernateJObject.h"

namespace cppHibernate {

class CppHibernateJDoubleObject: public cppHibernate::CppHibernateJObject {
public:
	static const char *JAVA_LANG_DOUBLE;
	static const char *JAVA_LANG_DOUBLE_SIGNATURE;
	static const char *JAVA_LANG_DOUBLE_PRIMITIVE_SIGNATURE;
	static const char *JAVA_LANG_DOUBLE_DOUBLEVALUE_NAME;
	static const char *JAVA_LANG_DOUBLE_DOUBLEVALUE_SIGNATURE;

	CppHibernateJDoubleObject(JNIEnv *, jobject, jclass, AbstractClassLoader *);
	double getVal();
	void setVal(double val = 0);
	virtual ~CppHibernateJDoubleObject();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEJDOUBLEOBJECT_H_ */
