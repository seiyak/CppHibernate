/*
 * CppHibernatePropertiesAccessor.h
 *
 *  Created on: Nov 18, 2011
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEPROPERTIESACCESSOR_H_
#define CPPHIBERNATEPROPERTIESACCESSOR_H_s

#include "CppHibernateAccessor.h"

namespace cppHibernate {

class CppHibernatePropertiesAccessor: public CppHibernateAccessor {

private:
	JNIEnv *env;
	AbstractClassLoader *classLoader;

protected:
	jobject findFieldWith(jobject, jclass, const char *);
	jobject getType(jobject, jclass);

public:
	static const char *JAVA_LANG_REFLECT_FIELD;
	static const char *JAVA_LANG_CLASS_GETDECLAREDFIELDS_NAME;
	static const char *JAVA_LANG_CLASS_GETDECLAREDFIELDS_SIGNATURE;
	static const char *JAVA_LANG_REFLECT_FIELD_GETTYPE_NAME;
	static const char *JAVA_LANG_REFLECT_FIELD_GETTYPE_SIGNATURE;

	CppHibernatePropertiesAccessor(JNIEnv *, AbstractClassLoader *);
	virtual const char *searchTypeFrom(jobject, jclass, const char*);
	const char *reflectField(jobject, jclass, const char *);
	virtual ~CppHibernatePropertiesAccessor();
};

}

/* namespace cppHibernate */
#endif /* CPPHIBERNATEPROPERTIESACCESSOR_H_ */
