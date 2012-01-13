/*
 * CppHibernateJVMConfiguration.h
 *
 *  Created on: Nov 6, 2011
 *      Author: apple
 */

#ifndef CPPHIBERNATEJVMCONFIGURATION_H_
#define CPPHIBERNATEJVMCONFIGURATION_H_

#include <cstring>
#include <string>
#include <jni.h>
#include "CppHibernateJVMException.h"

namespace cppHibernate {

class CppHibernateJVMConfiguration {

private:
	JNIEnv *env;
	JavaVM *jvm;
	JavaVMOption options[1];
	JavaVMInitArgs vm_args;

public:
	CppHibernateJVMConfiguration(const char *);
	JNIEnv *getJNIEnv();
	JavaVM *getJavaVM();
	void configureJVM(std::string&);
	virtual ~CppHibernateJVMConfiguration();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEJVMCONFIGURATION_H_ */
