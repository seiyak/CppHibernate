/*
 * URLClassLoader.cpp
 *
 *  Created on: Nov 6, 2011
 *      Author: apple
 */

#include "URLClassLoader.h"

namespace cppHibernate {

URLClassLoader::URLClassLoader(JNIEnv *env, const char *searchPath) :
		AbstractClassLoader(env), JAVA_NET_URLCLASSLOADER(
				"java/net/URLClassLoader"), JAVA_NET_NEWINSTANCE_NAME(
				"newInstance") {

	std::string path(searchPath);
	this->findJars(path);

	this->urlArray = this->createURLsFrom();
	this->newInstance(this->urlArray);
	this->env->DeleteGlobalRef(this->urlArray);
}

/**
 * Create a new instance of java.net.URLClassLoader.
 * @param jobject urlArray An array of java.net.URL used as the additional search paths. Array of java.net.URL is expected.
 */
void URLClassLoader::newInstance(jobject urls) {

	if (urlArray == NULL) {
		this->throwException();
	}

	jclass urlClassLoaderClass = this->env->FindClass(
			this->JAVA_NET_URLCLASSLOADER);

	if (urlClassLoaderClass != NULL) {

		jmethodID newInstanceId = this->env->GetStaticMethodID(
				urlClassLoaderClass, this->JAVA_NET_NEWINSTANCE_NAME,
				"([Ljava/net/URL;)Ljava/net/URLClassLoader;");

		if (newInstanceId != NULL) {

			jobject loader = this->env->CallStaticObjectMethod(
					urlClassLoaderClass, newInstanceId, urls);

			if (loader != NULL) {
				this->setClassLoader(this->env->NewGlobalRef(loader));
				this->setClassLoaderClass(
						this->env->NewGlobalRef(urlClassLoaderClass));
			} else {
				this->throwException();
			}
		} else {
			this->throwException();
		}

	} else {
		this->throwException();
	}
}

URLClassLoader::~URLClassLoader() {

}

} /* namespace cppHibernate */
