/*
 * CppHibernateMethodInvoker.h
 *
 *  Created on: Dec 1, 2011
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEMETHODINVOKER_H_
#define CPPHIBERNATEMETHODINVOKER_H_

#include <cstdarg>
#include "CppHibernateAccessor.h"
#include "CppHibernateJavaObject.h"

namespace cppHibernate {

class CppHibernateMethodInvoker: public CppHibernateAccessor {

private:
	JNIEnv *env;
	AbstractClassLoader *classLoader;
	jobject searchDeclaredMethods(jobject, jclass);
	jobject getMethod(const char*,jobject,jclass);
	std::string getReturnType(jobject, jclass);
	std::string getParametersType(jobject, jclass);

protected:
	virtual const char *searchTypeFrom(jobject, jclass, const char*);

public:
	static const char *JAVA_METHOD_PARAMETER_PREFIX_SIGNATURE;
	static const char *JAVA_METHOD_PARAMETER_SUFFIX_SIGNATURE;

	CppHibernateMethodInvoker(JNIEnv *, AbstractClassLoader *);
	CppHibernateJavaObject invoke(jobject, jclass, const char *, int&, va_list);
	const char *getMethodReturnSignature(jobject, jclass, const char *);
	const char *getMethodParametersSignature(jobject, jclass, const char *);
	const char *getMethodSignature(jobject, jclass, const char *);
	virtual ~CppHibernateMethodInvoker();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEMETHODINVOKER_H_ */
