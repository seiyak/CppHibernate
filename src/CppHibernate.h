/*
 * CppHibernate.h
 *
 *  Created on: Nov 3, 2011
 *      Author: apple
 */

#ifndef CPPHIBERNATE_H_
#define CPPHIBERNATE_H_

#include <jni.h>
#include "CppHibernateException.h"
#include "URLClassLoader.h"
#include "CppHibernateJVMConfiguration.h"
#include "CppHibernateSessionFactory.h"
#include "CppHibernateSession.h"

namespace cppHibernate {

class CppHibernate {

private:
	JNIEnv *env;
	JavaVM *jvm;
	AbstractClassLoader *classLoader;
	const char *UNIX_SEPARATOR;
	const char *HIBERNATE_CONFIG_FILE_NAME;

protected:
	const char *JAVA_CONSTRUCTOR_NAME;
	const char *ORG_HIBERNATE_CFG_CONFIGURATION;
	const char *ORG_HIBERNATE_SESSIONFACTORY;
	const char *ORG_HIBERNATE_CFG_CONFIGURATION_CONFIGURE_NAME;
	const char *ORG_HIBERNATE_CFG_CONFIGURATION_BUILDSESSIONFACTORY_NAME;
	jobject configuration;
	jclass configurationClass;
	CppHibernateSessionFactory *sessionFactory;

	bool isEnvNull();
	void throwException();
	void throwJNIEnvNull();
	bool checkHibernateConfigFileName(const char*);
	virtual void createHibernateConfiguration();
	void buildSessionFactory();
	virtual void configure();
	void configure(const char*);
	void throwIfSessionFactoryNull();

public:
	CppHibernate(CppHibernateJVMConfiguration*, AbstractClassLoader *,
			const char *resource = "");
	jobject getConfiguration();
	CppHibernateSessionFactory *getSessionFactory();
	virtual ~CppHibernate();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATE_H_ */
