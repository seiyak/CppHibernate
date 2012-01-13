/*
 * CppHibernateJCollectionObject.h
 *
 *  Created on: Jan 6, 2012
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEJCOLLECTIONOBJECT_H_
#define CPPHIBERNATEJCOLLECTIONOBJECT_H_

#include "CppHibernateJCollectionsObject.h"
#include "CppHibernateJIteratorObject.h"

namespace cppHibernate {

class CppHibernateJCollectionObject: public cppHibernate::CppHibernateJCollectionsObject {

private:
	jobjectArray objArray;

	void fillObjArray();
	void checkInstanceOfCollection();
	void checkValidIndex(int&);

public:
	static const char *JAVA_UTIL_COLLECTION_TOARRAY_NAME;
	static const char *JAVA_UTIL_COLLECTION_TOARRAY_SIGNATURE;
	static const char *JAVA_UTIL_COLLECTION_ADD_NAME;
	static const char *JAVA_UTIL_COLLECTION_ADD_SIGNATURE;
	static const char *JAVA_UTIL_COLLECTION_REMOVE_NAME;
	static const char *JAVA_UTIL_COLLECTION_REMOVE_SIGNATURE;
	static const char *JAVA_UTIL_COLLECTION_ITERATOR_NAME;
	static const char *JAVA_UTIL_COLLECTION_ITERATOR_SIGNATURE;

	CppHibernateJCollectionObject(JNIEnv*, jobject, jclass,
			AbstractClassLoader *);
	void clear();
	CppHibernateJObject *get(int);
	bool add(CppHibernateJObject *);
	bool remove(CppHibernateJObject *);
	CppHibernateJIteratorObject iterator();
	virtual ~CppHibernateJCollectionObject();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEJCOLLECTIONOBJECT_H_ */
