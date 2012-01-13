/*
 * URLClassLoader.h
 *
 *  Created on: Nov 6, 2011
 *      Author: apple
 */

#ifndef URLCLASSLOADER_H_
#define URLCLASSLOADER_H_

#include "AbstractClassLoader.h"

namespace cppHibernate {

class URLClassLoader: public cppHibernate::AbstractClassLoader {

private:
	void newInstance(jobject);

	jobject urlArray;

protected:
	const char *JAVA_NET_URLCLASSLOADER;
	const char *JAVA_NET_NEWINSTANCE_NAME;

public:
	URLClassLoader(JNIEnv*,const char*);
	URLClassLoader(const char*);
	virtual ~URLClassLoader();
};

} /* namespace cppHibernate */
#endif /* URLCLASSLOADER_H_ */
