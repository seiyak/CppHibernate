/*
 * CppHibernateJFloatObject.h
 *
 *  Created on: Nov 28, 2011
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEJFLOATOBJECT_H_
#define CPPHIBERNATEJFLOATOBJECT_H_

#include "CppHibernateJObject.h"

namespace cppHibernate {

class CppHibernateJFloatObject: public cppHibernate::CppHibernateJObject {
public:
	static const char *JAVA_LANG_FLOAT;
	static const char *JAVA_LANG_FLOAT_SIGNATURE;
	static const char *JAVA_LANG_FLOAT_PRIMITIVE_SIGNATURE;
	static const char *JAVA_LANG_FLOAT_FLOATVALUE_NAME;
	static const char *JAVA_LANG_FLOAT_FLOATVALUE_SIGNATURE;

	CppHibernateJFloatObject(JNIEnv*, jobject, jclass, AbstractClassLoader*);
	float getVal();
	void setVal(float val = 0);
	virtual ~CppHibernateJFloatObject();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEJFLOATOBJECT_H_ */
