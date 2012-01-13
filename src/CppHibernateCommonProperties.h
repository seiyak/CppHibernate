/*
 * CppHibernateCommonProperties.h
 *
 *  Created on: Nov 10, 2011
 *      Author: apple
 */

#ifndef CPPHIBERNATECOMMONPROPERTIES_H_
#define CPPHIBERNATECOMMONPROPERTIES_H_

#include <jni.h>
#include "AbstractClassLoader.h"

namespace cppHibernate {

class CppHibernateCommonProperties {
public:
	CppHibernateCommonProperties();
	virtual void checkCommonProperties(JNIEnv*, jobject, jclass,
			AbstractClassLoader*) = 0;
	virtual ~CppHibernateCommonProperties();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATECOMMONPROPERTIES_H_ */
