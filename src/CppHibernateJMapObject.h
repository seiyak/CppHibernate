/*
 * CppHibernateJMapObject.h
 *
 *  Created on: Jan 6, 2012
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEJMAPOBJECT_H_
#define CPPHIBERNATEJMAPOBJECT_H_

#include "CppHibernateJCollectionObject.h"

namespace cppHibernate {

class CppHibernateJMapObject: public cppHibernate::CppHibernateJCollectionsObject {

private:
	void checkInstanceOfMap();

public:
	static const char *JAVA_UTIL_MAP_CONTAINSKEY_NAME;
	static const char *JAVA_UTIL_MAP_CONTAINSVALUE_NAME;
	static const char *JAVA_UTIL_MAP_PUT_NAME;
	static const char *JAVA_UTIL_MAP_PUT_SIGNATURE;
	static const char *JAVA_UTIL_MAP_GET_NAME;
	static const char *JAVA_UTIL_MAP_GET_SIGNATURE;
	static const char *JAVA_UTIL_MAP_KEYSET_NAME;
	static const char *JAVA_UTIL_MAP_KEYSET_SIGNATURE;
	static const char *JAVA_UTIL_MAP_PUTALL_NAME;
	static const char *JAVA_UTIL_MAP_PUTALL_SIGNATURE;
	static const char *JAVA_UTIL_MAP_VALUES_NAME;
	static const char *JAVA_UTIL_MAP_VALUES_SIGNATURE;
	static const char *JAVA_UTIL_MAP_ENTRYSET_NAME;
	static const char *JAVA_UTIL_MAP_ENTRYSET_SIGNATURE;
	static const char *JAVA_UTIL_HASHMAP_ENTRY;

	CppHibernateJMapObject(JNIEnv *, jobject, jclass, AbstractClassLoader *);
	bool containsKey(CppHibernateJObject *);
	bool containsValue(CppHibernateJObject *);
	CppHibernateJObject *put(CppHibernateJObject*, CppHibernateJObject*,
			bool returnOldObj = false);
	CppHibernateJObject *get(CppHibernateJObject*);
	CppHibernateJCollectionObject *keySet();
	void putAll(CppHibernateJMapObject *);
	void clear();
	CppHibernateJCollectionObject *values();
	//// TODO implement entrySet() method
	virtual ~CppHibernateJMapObject();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEJMAPOBJECT_H_ */
