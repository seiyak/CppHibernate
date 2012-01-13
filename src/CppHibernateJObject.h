/*
 * CppHibernateJObject.h
 *
 *  Created on: Nov 14, 2011
 *      Author: apple
 */

#ifndef CPPHIBERNATEJOBJECT_H_
#define CPPHIBERNATEJOBJECT_H_

#include "CppHibernateCommons.h"
#include "CppHibernatePropertiesAccessor.h"
#include "CppHibernateMethodInvoker.h"

namespace cppHibernate {

class CppHibernateJObject: public cppHibernate::CppHibernateCommons {

private:
	CppHibernatePropertiesAccessor propertiesAccessor;
	CppHibernateMethodInvoker methodInvoker;

	const char *findCanonicalName(jobject, jclass);

protected:
	jobject findToString(jclass);
	const char *getCanonicalName(jobject);
	void checkNull(CppHibernateJObject *);
	std::string createSimpleErrorMessage(const char*);
	CppHibernateJObject *createReturnObj(jobject);

public:
	static const char *PRIMITIVE_CLASS_CONSTRUCTOR_SIGNATURE;
	static const char *JAVA_TOSTRING_NAME;
	static const char *JAVA_TOSTRING_SIGNATURE;
	static const char *JAVA_CONSTRUCTOR_NAME;
	static const char *JAVA_DEFAULT_CONSTRUCTOR_SIGNATURE;
	static const char *JAVA_ARRAY_SIGNATURE;
	static const char *JAVA_CLASS_PREFIX_SIGNATURE;
	static const char *JAVA_HASHCODE_NAME;
	static const char *JAVA_HASHCODE_SIGNATURE;
	static const char *JAVA_EQUALS_NAME;
	static const char *JAVA_EQUALS_SIGNATURE;

	CppHibernateJObject(JNIEnv *, jobject, jclass, AbstractClassLoader *);
	void setVal(const char *, CppHibernateJObject *);
	CppHibernateJObject *getVal(const char *);
	const char *toString();
	bool isInstanceOf(const char *);
	CppHibernateJObject *invoke(const char *, int, ...);
	const char *getCanonicalName();
	int hashCode();
	bool equals(CppHibernateJObject *);
	virtual ~CppHibernateJObject();
};

}
/* namespace cppHibernate */
#endif /* CPPHIBERNATEJOBJECT_H_ */
