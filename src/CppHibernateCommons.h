/*
 * CppHibernateCommons.h
 *
 *  Created on: Nov 10, 2011
 *      Author: apple
 */

#ifndef CPPHIBERNATECOMMONS_H_
#define CPPHIBERNATECOMMONS_H_

#include "CppHibernateCommonProperties.h"
#include "CppHibernateCommonExceptionChecks.h"

namespace cppHibernate {

class CppHibernateCommons: public CppHibernateCommonProperties,
		CppHibernateCommonExceptionChecks {

protected:
	JNIEnv *env;
	jobject obj;
	jclass objClass;
	AbstractClassLoader *classLoader;

	void setObj(jobject);

public:
	CppHibernateCommons(JNIEnv*, jobject, jclass, AbstractClassLoader*);
	jobject getObj();
	jclass getObjClass();
	virtual void checkCommonProperties(JNIEnv*, jobject, jclass,
			AbstractClassLoader*);
	virtual void throwException();
	virtual void checkAndThrow();
	virtual ~CppHibernateCommons();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATECOMMONS_H_ */
