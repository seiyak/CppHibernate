/*
 * ClassLoader.h
 *
 *  Created on: Nov 4, 2011
 *      Author: apple
 */

#ifndef CLASSLOADER_H_
#define CLASSLOADER_H_

#include <jni.h>

namespace cppHibernate {

class ClassLoader {
public:
	ClassLoader();
	virtual jobject loadClass(const char*) = 0;
	virtual jobject findClass(const char *) = 0;
	virtual ~ClassLoader();
};

} /* namespace cppHibernate */
#endif /* CLASSLOADER_H_ */
