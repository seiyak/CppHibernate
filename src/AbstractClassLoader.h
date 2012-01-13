/*
 * AbstractClassLoader.h
 *
 *  Created on: Nov 4, 2011
 *      Author: apple
 */

#ifndef ABSTRACTCLASSLOADER_H_
#define ABSTRACTCLASSLOADER_H_

#include <string>
#include <deque>

#include "ClassLoader.h"
#include "CppHibernateIOException.h"
#include "CppHibernateIndexException.h"
#include "CppHibernateClassLoaderException.h"

namespace cppHibernate {

class AbstractClassLoader: public ClassLoader {
private:
	std::deque<std::string*> *classPaths;
	jobject classLoader;
	jobject classLoaderClass;
	const std::string PERIOD;
	const std::string UNIX_SEPARATOR;
	const std::string LOWER_CASE_JAR;
	const std::string UPPER_CASE_JAR;

	bool isJarFile(std::string&);
	void deleteClassPaths();
	bool isEndedWithSeparator(std::string&);
	void deleteClassLoader();

protected:
	void throwException();
	bool isEnvNull();
	void setClassLoader(jobject);
	void setClassLoaderClass(jobject);
	//// another version of createURLsFrom() probably needed.
	//jobject createURLsFrom();

	JNIEnv *env;

	const char *JAVA_IO_FILE;
	const char *JAVA_IO_FILE_EXIST_NAME;
	const char *JAVA_IO_FILE_TOURI_NAME;
	const char *JAVA_NET_URI;
	const char *JAVA_NET_URI_TOURL_NAME;
	const char *JAVA_NET_URL;
	const char *JAVA_CONSTRUCTOR_NAME;
	const char *JAVA_LANG_CLASSLOADER_LOADCLASS_NAME;
	const char *JAVA_LANG_CLASSLOADER_FINDCLASS_NAME;

public:
	jobject createURLsFrom();
	AbstractClassLoader(JNIEnv*);
	AbstractClassLoader();
	bool exist(jclass, jobject);
	jobject createFileFrom(const char*);
	jobject createURIFrom(jobject);
	jobject createURLFrom(jobject);
	jobject createURLsFrom(jobject);
	int findJars(std::string&);
	virtual jobject loadClass(const char*);
	virtual jobject findClass(const char*);
	int size();
	const std::string get(int);
	jobject getClassLoader();
	jobject getClassLoaderClass();
	virtual ~AbstractClassLoader();
};

} /* namespace cppHibernate */
#endif /* ABSTRACTCLASSLOADER_H_ */
