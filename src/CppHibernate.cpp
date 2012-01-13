/*
 * CppHibernate.cpp
 *
 *  Created on: Nov 3, 2011
 *      Author: apple
 */

#include <cstring>
#include "CppHibernate.h"

namespace cppHibernate {

CppHibernate::CppHibernate(CppHibernateJVMConfiguration *hibernateConfiguration,
		AbstractClassLoader *classLoader, const char *resource) :
		env(NULL), configuration(NULL), configurationClass(NULL), sessionFactory(
				NULL), ORG_HIBERNATE_CFG_CONFIGURATION(
				"org.hibernate.cfg.Configuration"), JAVA_CONSTRUCTOR_NAME(
				"<init>"), ORG_HIBERNATE_CFG_CONFIGURATION_CONFIGURE_NAME(
				"configure"), HIBERNATE_CONFIG_FILE_NAME("hibernate.cfg.xml"), UNIX_SEPARATOR(
				"/"), ORG_HIBERNATE_CFG_CONFIGURATION_BUILDSESSIONFACTORY_NAME(
				"buildSessionFactory"), ORG_HIBERNATE_SESSIONFACTORY(
				"org.hibernate.SessionFactory") {

	if (hibernateConfiguration == NULL) {
		throw CppHibernateException(
				"Please specify hibernateConfiguration parameter correctly.");
	}

	if (classLoader == NULL) {
		throw CppHibernateException(
				"Please specify classLoader parameter correctly.");
	}

	this->env = hibernateConfiguration->getJNIEnv();
	this->jvm = hibernateConfiguration->getJavaVM();

	this->classLoader = classLoader;

	this->createHibernateConfiguration();
	if (std::strcmp(resource, "") == 0) {
		this->configure();
	} else {
		this->configure(resource);
	}

	this->buildSessionFactory();
}

/**
 * Instantiates a new org.hibernate.cfg.Configuration object.
 */
void CppHibernate::createHibernateConfiguration() {
	if (this->isEnvNull()) {
		this->throwJNIEnvNull();
	}
	jclass configClass = (jclass) (((((((((((this->classLoader->loadClass(
			this->ORG_HIBERNATE_CFG_CONFIGURATION))))))))))));
	if (configClass != NULL) {

		jmethodID configurationConstructorId = this->env->GetMethodID(
				configClass, "<init>", "()V");

		if (configurationConstructorId != NULL) {
			jobject configurationObj = this->env->NewObject(configClass,
					configurationConstructorId);

			if (configurationObj != NULL) {
				this->configuration = this->env->NewGlobalRef(configurationObj);
				this->configurationClass = (jclass) this->env->NewGlobalRef(
						configClass);
			} else {
				this->throwException();
			}
		} else {
			this->throwException();
		}
	}
}

/**
 * Configures org.hibernate.cfg.Configuration object by './hibernate.cfg.xml' file, in the root class path.
 * @throw CppHibernateException Throws when env property, JNIEnv* is not set before calling this method.
 */
void CppHibernate::configure() {
	if (this->isEnvNull()) {
		this->throwJNIEnvNull();
	}
	if (this->configuration == NULL) {
		throw CppHibernateException(
				"configuration property is not set yet. Please set it before calling this method");
	}
	jmethodID configureId = this->env->GetMethodID(this->configurationClass,
			this->ORG_HIBERNATE_CFG_CONFIGURATION_CONFIGURE_NAME,
			"()Lorg/hibernate/cfg/Configuration;");
	if (configureId != NULL) {
		jobject configObj = this->env->CallObjectMethod(this->configuration,
				configureId);

		if (configObj != NULL) {
			this->env->DeleteGlobalRef(this->configuration);
			this->configuration = NULL;
			this->configuration = this->env->NewGlobalRef(configObj);
		} else {
			this->throwException();
		}
	} else {
		this->throwException();
	}
}

/**
 * Configures org.hibernate.cfg.Configuration object by hibernate.cfg.xml at a specific location instead of the root class path.
 * @param const char *resource Specific location to look for hibernate.cfg.xml file.
 * @throw CppHibernateException Throws when env property, JNIEnv* is not set before calling this method or
 * the specified resource does not exist.
 */
void CppHibernate::configure(const char *resource) {
	if (resource == NULL) {
		throw CppHibernateException("NULL is specified for the resource");
	}
	if (this->classLoader == NULL) {
		throw CppHibernateException(
				"Please set classLoader property before calling this method");
	}
	if (this->isEnvNull()) {
		this->throwJNIEnvNull();
	}
	if (this->configuration == NULL) {
		throw CppHibernateException(
				"configuration property is not set yet. Please set it calling 'createHibernateConfiguration()' method before this method");
	}
	if (this->configurationClass == NULL) {
		throw CppHibernateException(
				"configurationClass property is not set yet. Please set it before calling this method");
	}
	jobject fileObj = this->classLoader->createFileFrom(resource);
	if (fileObj != NULL) {

		if (this->checkHibernateConfigFileName(resource)) {

			jmethodID configureWithFile = this->env->GetMethodID(
					this->configurationClass,
					this->ORG_HIBERNATE_CFG_CONFIGURATION_CONFIGURE_NAME,
					"(Ljava/io/File;)Lorg/hibernate/cfg/Configuration;");

			if (configureWithFile != NULL) {
				jobject configObj = this->env->CallObjectMethod(
						this->configuration, configureWithFile, fileObj);

				if (configObj != NULL) {
					if (this->configuration != NULL) {
						this->env->DeleteGlobalRef(this->configuration);
						this->configuration = NULL;
						this->configuration = this->env->NewGlobalRef(
								configObj);
					} else {
						this->throwException();
					}
				} else {
					this->throwException();
				}
			} else {
				this->throwException();
			}
		} else {
			std::string errorMessage(
					"the resource does not point to 'hibernate.cfg.xml' file, ");
			errorMessage += resource;
			errorMessage += " .";

			throw CppHibernateException(errorMessage.c_str());
		}
	} else {
		std::string errorMessage("the resource does not exist, ");
		errorMessage += resource;
		throw CppHibernateException(errorMessage.c_str());
	}
}

/**
 * Checks if the resource correctly specifies 'hibernate.cfg.xml' file or not.
 * @param const char *resource Path to be checked if it points to 'hibernate.cfg.xml'.
 * @return bool Returns true when it points to the file, otherwise returns false.
 */
bool CppHibernate::checkHibernateConfigFileName(const char *resource) {
	if (resource == NULL) {
		return false;
	}
	std::string resourceStr(resource);
	size_t pos = resourceStr.find_last_of(this->UNIX_SEPARATOR);
	if (pos == std::string::npos) {
		return false;
	}
	if (resourceStr.substr(pos + 1, resourceStr.length()).compare(
			this->HIBERNATE_CONFIG_FILE_NAME) == 0) {
		return true;
	}
	return false;
}

/**
 * Instantiates org.hibernate.SessionFactory with the configuration up to calling this method. After this call,
 * CppHibernate::configuration and CppHibernate::configurationClass become NULL. CppHibernate::sessionFactory is instantiated
 * in the method call holding the global refs for org.hibernate.SessionFactory class representation and object itself.
 */
void CppHibernate::buildSessionFactory() {
	if (this->classLoader == NULL) {
		throw CppHibernateException(
				"Please set classLoader property before calling this method");
	}
	if (this->isEnvNull()) {
		this->throwJNIEnvNull();
	}
	if (this->configuration == NULL) {
		throw CppHibernateException(
				"configuration property is not set yet. Please set it calling 'createHibernateConfiguration()' method before this method");
	}
	if (this->configurationClass == NULL) {
		throw CppHibernateException(
				"configurationClass property is not set yet. Please set it calling 'createHibernateConfiguration()' method before this method");
	}
	jclass sessionFactoryCls = (jclass) ((((((this->classLoader->loadClass(
			this->ORG_HIBERNATE_SESSIONFACTORY)))))));
	if (sessionFactoryCls != NULL) {
		jmethodID buildSessionFactoryId = this->env->GetMethodID(
				this->configurationClass,
				this->ORG_HIBERNATE_CFG_CONFIGURATION_BUILDSESSIONFACTORY_NAME,
				"()Lorg/hibernate/SessionFactory;");

		if (buildSessionFactoryId != NULL) {
			jobject sessionFactoryObj = this->env->CallObjectMethod(
					this->configuration, buildSessionFactoryId);

			if (sessionFactoryObj != NULL) {

				this->sessionFactory = new CppHibernateSessionFactory(this->env,
						this->env->NewGlobalRef(sessionFactoryObj),
						(jclass) this->env->NewGlobalRef(sessionFactoryCls),
						this->classLoader);

				this->env->DeleteGlobalRef(this->configuration);
				this->configuration = NULL;
				this->env->DeleteGlobalRef(this->configurationClass);
				this->configurationClass = NULL;
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

/**
 * Gets configuration property representing org.hibernate.cfg.Configuration.
 * @return jobject Object representing org.hibernate.cfg.Configuration or NULL before calling CppHibernate::createHibernateConfiguration() method or after
 * calling CppHibernate::buildSessionFactory() method and successfully creating SessionFactory object.
 */
jobject CppHibernate::getConfiguration() {
	return this->configuration;
}

/**
 * Gets sessionFactory property representing org.hibernate.SessionFactory.
 * @return CppHibernateSessionFactory* Wrapper object representing org.hibernate.SessionFactory or NULL before calling CppHibernate::buildSessionFactory() method.
 */
CppHibernateSessionFactory *CppHibernate::getSessionFactory() {
	return this->sessionFactory;
}

/**
 * Checks if CppHibernate::sessionFactory property is null or not. This property must be set before using this method
 * to work with hibernate methods on JVM.
 */
void CppHibernate::throwIfSessionFactoryNull() {
	if (this->sessionFactory == NULL) {
		throw CppHibernateException(
				"CppHibernate::sessionFactory is not set yet.Please call CppHibernate::buildSessionFactory() method before this method");
	}
}

/**
 * Checks if env property is null or not.
 * @return bool True if it's NULL, false otherwise.
 */
bool CppHibernate::isEnvNull() {
	if (this->env == NULL) {
		return true;
	}
	return false;
}

/**
 * Throws CppHiberanteException. Called with CppHibernate::isEnvNULL() method.
 * @throw CppHiberanteException Throws when env property, JNIEnv*, is NULL but tries to call methods on Java objects.
 */
void CppHibernate::throwJNIEnvNull() {
	throw CppHibernateException(
			"env pproperty, JNIEnv is NULL. Please set it before calling any methods on Java objects");
}

/**
 * Throws CppHibernateException. Called when JNI method calls encounter errors.
 */
void CppHibernate::throwException() {
	this->env->ExceptionDescribe();
	this->env->ExceptionClear();
	//TODO need to think about how to get exception messages and causes from the jthrowable object.
	throw CppHibernateException("error occurred");
}

CppHibernate::~CppHibernate() {
	if (this->configuration != NULL) {
		this->env->DeleteGlobalRef(this->configuration);
		this->configuration = NULL;
	}

	if (this->configurationClass != NULL) {
		this->env->DeleteGlobalRef(this->configurationClass);
		this->configurationClass = NULL;
	}

	if (this->sessionFactory != NULL) {
		delete this->sessionFactory;
	}
}

} /* namespace cppHibernate */
