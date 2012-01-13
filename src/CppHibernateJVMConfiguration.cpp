/*
 * CppHibernateJVMConfiguration.cpp
 *
 *  Created on: Nov 6, 2011
 *      Author: apple
 */

#include "CppHibernateJVMConfiguration.h"

namespace cppHibernate {

CppHibernateJVMConfiguration::CppHibernateJVMConfiguration(
		const char *rootPath) {

	std::string prefixRootPath("-Djava.class.path=");
	prefixRootPath += rootPath;
	this->configureJVM(prefixRootPath);
}

JNIEnv *CppHibernateJVMConfiguration::getJNIEnv() {
	return this->env;
}

JavaVM *CppHibernateJVMConfiguration::getJavaVM() {
	return this->jvm;
}

/**
 * Configures Java VM to make Hibernate available from the native code, C++.
 * @param std::string& rootPath Java root class path where the hibernate.cfg.xml file is placed.
 * @throw CppHibernateJVMException Throws when can't create Java VM correctly.
 */
void CppHibernateJVMConfiguration::configureJVM(std::string& rootPath) {

	this->options[0].optionString = const_cast<char*>(rootPath.c_str());
	//this->options[1].optionString = "-verbose:class";
	std::memset(&(this->vm_args), 0, sizeof(this->vm_args));
	vm_args.version = JNI_VERSION_1_6;
	vm_args.nOptions = 1;
	vm_args.options = this->options;
	jint javaVMStatus = JNI_CreateJavaVM(&(this->jvm), (void**) &(this->env),
			&vm_args);
	if (javaVMStatus != JNI_OK) {
		throw CppHibernateJVMException("could not create java vm successfully");
	}
}

CppHibernateJVMConfiguration::~CppHibernateJVMConfiguration() {
	this->jvm->DestroyJavaVM();
}

} /* namespace cppHibernate */
