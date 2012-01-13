/*
 * CppHibernateAccessor.h
 *
 *  Created on: Nov 18, 2011
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEACCESSOR_H_
#define CPPHIBERNATEACCESSOR_H_

#include <map>
#include <jni.h>
#include "AbstractClassLoader.h"
#include "CppHibernateCommonExceptionChecks.h"
#include "CppHibernateCommonProperties.h"

namespace cppHibernate {

class CppHibernateAccessor: CppHibernateCommonExceptionChecks,
		CppHibernateCommonProperties {

private:
	JNIEnv *env;
	AbstractClassLoader *classLoader;

	const char *getPrimitiveSignature(const char*);
	const char *createObjectSignature(const char*);
	const char *createArraySignature(const char*);

protected:
	jobject getGetClassId(jclass objClass);
	virtual const char *searchTypeFrom(jobject, jclass, const char*) = 0;
	bool isStartedWith(const char *, const char *);
	const char *createCorrespondingSignature(const char *);
	jobject getTarget(const char*, jobject, jclass, jobject);
	bool containArrayPrefix(const char *);

public:
	static const char *JAVA_LANG_CLASS_GETCLASS_NAME;
	static const char *JAVA_LANG_CLASS_GETCLASS_SIGNATURE;
	static const char *JAVA_LANG_CLASS;
	static const char *JAVA_LANG_CLASS_GETDECLAREDMETHODS_NAME;
	static const char *JAVA_LANG_CLASS_GETDECLAREDMETHODS_SIGNATURE;
	static const char *JAVA_LANG_CLASS_GETSUPERCLASS_NAME;
	static const char *JAVA_LANG_CLASS_GETSUPERCLASS_SIGNATURE;
	static const char *JAVA_LANG_REFLECT_METHOD;
	static const char *JAVA_LANG_REFLECT_METHOD_GETNAME_NAME;
	static const char *JAVA_LANG_REFLECT_METHOD_GETNAME_SIGNATURE;
	static const char *JAVA_LANG_REFLECT_METHOD_GETRETURNTYPE_NAME;
	static const char *JAVA_LANG_REFLECT_METHOD_GETRETURNTYPE_SIGNATURE;
	static const char *JAVA_LANG_REFLECT_METHOD_GETPARAMETERTYPES_NAME;
	static const char *JAVA_LANG_REFLECT_METHOD_GETPARAMETERTYPES_SIGNATURE;
	static const char *JAVA_LANG_REFLECT_ACCESSIBLEOBJECT_SETACCESSIBLE_NAME;
	static const char *JAVA_LANG_REFLECT_ACCESSIBLEOBJECT_SET_ACCESSIBLE_SIGNATURE;
	static const char *JAVA_LANG_GETNAME_NAME;
	static const char *JAVA_LANG_GETNAME_SIGNATURE;

	CppHibernateAccessor(JNIEnv *, AbstractClassLoader *);
	jobject callGetClass(jobject, jclass);
	static const char *copyStringFrom(JNIEnv*, jstring);
	static void replaceAll(std::string&, const char*, const char*, size_t);
	std::string constructObjectSignature(std::string&);
	virtual void checkCommonProperties(JNIEnv*, jobject, jclass,
			AbstractClassLoader*);
	virtual void throwException();
	virtual void checkAndThrow();
	static const char *toString(JNIEnv *, jobject, jclass);
	virtual ~CppHibernateAccessor();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEACCESSOR_H_ */
