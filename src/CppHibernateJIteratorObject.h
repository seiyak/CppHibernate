/*
 * CppHibernateJIteratorObject.h
 *
 *  Created on: Jan 9, 2012
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEJITERATOROBJECT_H_
#define CPPHIBERNATEJITERATOROBJECT_H_

#include "CppHibernateJObject.h"

namespace cppHibernate {

class CppHibernateJIteratorObject: public cppHibernate::CppHibernateJObject {
public:
	static const char *JAVA_UTIL_ITERATOR_HASNEXT_NAME;
	static const char *JAVA_UTIL_ITERATOR_HASNEXT_SIGNATURE;
	static const char *JAVA_UTIL_ITERATOR_NEXT_NAME;
	static const char *JAVA_UTIL_ITERATOR_NEXT_SIGNATURE;
	static const char *JAVA_UTIL_ITERATOR_REMOVE_NAME;
	static const char *JAVA_UTIL_ITERATOR_REMOVE_SIGNATURE;

	CppHibernateJIteratorObject(JNIEnv *, jobject, jclass,
			AbstractClassLoader *);
	bool hasNext();
	CppHibernateJObject *next();
	void remove();
	virtual ~CppHibernateJIteratorObject();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEJITERATOROBJECT_H_ */
