/*
 * CppHibernateJStringObject.h
 *
 *  Created on: Nov 15, 2011
 *      Author: apple
 */

#ifndef CPPHIBERNATEJSTRINGOBJECT_H_
#define CPPHIBERNATEJSTRINGOBJECT_H_

#include <sstream>
#include "CppHibernateJObject.h"

namespace cppHibernate {

class CppHibernateJStringObject: public cppHibernate::CppHibernateJObject {

public:
	static const char *JAVA_LANG_STRING;
	static const char *JAVA_LANG_STRING_SIGNATURE;

	const char *getVal();
	void setVal(const char*);
	CppHibernateJStringObject(JNIEnv*, jobject, jclass, AbstractClassLoader*);

	//// TODO concat and other methods are ncessary ??

	CppHibernateJStringObject& concat(CppHibernateJStringObject*);
	CppHibernateJStringObject& concat(const char *);
	virtual ~CppHibernateJStringObject();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEJSTRINGOBJECT_H_ */
