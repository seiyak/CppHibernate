/*
 * CppHibernateJCollectionsObject.h
 *
 *  Created on: Jan 6, 2012
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEJCOLLECTIONSOBJECT_H_
#define CPPHIBERNATEJCOLLECTIONSOBJECT_H_

#include "CppHibernateJObject.h"

namespace cppHibernate {

class CppHibernateJCollectionsObject: public cppHibernate::CppHibernateJObject {

protected:
	void checkInstanceOfCollectionOrMap();

public:
	static const char *JAVA_UTIL_CLEAR_NAME;
	static const char *JAVA_UTIL_CLEAR_SIGNATURE;
	static const char *JAVA_UTIL_SIZE_NAME;
	static const char *JAVA_UTIL_SIZE_SIGNATURE;
	static const char *JAVA_UTIL_ISEMPTY_NAME;
	static const char *JAVA_UTIL_ISEMPTY_SIGNATURE;
	static const char *JAVA_UTIL_COLLECTION;
	static const char *RETURN_BOOL_PARAM_OBJECT_SIGNATURE;
	static const char *JAVA_UTIL_MAP;

	CppHibernateJCollectionsObject(JNIEnv *, jobject, jclass,
			AbstractClassLoader *);
	int size();
	bool isEmpty();

	virtual ~CppHibernateJCollectionsObject();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEJCOLLECTIONSOBJECT_H_ */
