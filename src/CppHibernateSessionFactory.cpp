/*
 * CppHibernateSessionFactory.cpp
 *
 *  Created on: Nov 10, 2011
 *      Author: apple
 */

#include "CppHibernateSessionFactory.h"

namespace cppHibernate {

const char *CppHibernateSessionFactory::ORG_HIBERNATE_CLASSIC_SESSION =
		"org.hibernate.classic.Session";
const char *CppHibernateSessionFactory::ORG_HIBERNATE_SESSIONFACTORY_OPENSESSION_NAME =
		"openSession";
const char *CppHibernateSessionFactory::ORG_HIBERNATE_SESSIONFACTORY_OPENSESSION_SIGNATURE =
		"()Lorg/hibernate/classic/Session;";
const char *CppHibernateSessionFactory::ORG_HIBERNATE_SESSIONFACTORY_GETCURRENTSESSION_NAME =
		"getCurrentSession";
const char *CppHibernateSessionFactory::ORG_HIBERNATE_SESSIONFACTORY_GETCURRENTSESSION_SIGNATURE =
		"()Lorg/hibernate/classic/Session;";
const char *CppHibernateSessionFactory::ORG_HIBERNATE_SESSIONFACTORY_CLOSE_NAME =
		"close";
const char *CppHibernateSessionFactory::ORG_HIBERNATE_SESSIONFACTORY_CLOSE_SIGNATURE =
		"()V";
const char *CppHibernateSessionFactory::ORG_HIBERNATE_SESSIONFACTORY_ISCLOSED_NAME =
		"isClosed";
const char *CppHibernateSessionFactory::ORG_HIBERNATE_SESSIONFACTORY_ISCLOSED_SIGNATURE =
		"()Z";
const char *CppHibernateSessionFactory::ORG_HIBERNATE_SESSIONFACTORY_GETSTATISTICS_NAME =
		"getStatistics";
const char *CppHibernateSessionFactory::ORG_HIBERNATE_SESSIONFACTORY_GETSTATISTICS_SIGNATURE =
		"()Lorg/hibernate/stat/Statistics;";

CppHibernateSessionFactory::CppHibernateSessionFactory(JNIEnv *env,
		jobject sessionFactory, jclass sessionFactoryClass,
		AbstractClassLoader *classLoader) :
		CppHibernateCommons(env, sessionFactory, sessionFactoryClass,
				classLoader) {
}

/**
 * Creates a new org.hibernate.classic.Session object. The returned object must be deleted once the job is done.
 * @return CppHibernateSession An object representing org.hibernate.classic.Session class.
 * @throw Throws exception when JNI encounters exception.
 */
CppHibernateSession *CppHibernateSessionFactory::openSession() {

	jclass sessionClass = (jclass) ((((this->classLoader->loadClass(
			CppHibernateSessionFactory::ORG_HIBERNATE_CLASSIC_SESSION)))));
	if (sessionClass != NULL) {
		jmethodID openSessionId =
				this->env->GetMethodID(
						this->objClass,
						CppHibernateSessionFactory::ORG_HIBERNATE_SESSIONFACTORY_OPENSESSION_NAME,
						CppHibernateSessionFactory::ORG_HIBERNATE_SESSIONFACTORY_OPENSESSION_SIGNATURE);

		if (openSessionId != NULL) {
			jobject session = this->env->CallObjectMethod(this->obj,
					openSessionId);

			if (session != NULL) {
				CppHibernateSession *sessionObj = new CppHibernateSession(
						this->env, this->env->NewGlobalRef(session),
						(jclass) this->env->NewGlobalRef(sessionClass),
						this->classLoader);

				return sessionObj;

			} else {
				this->throwException();
			}
		} else {
			this->throwException();
		}
	} else {
		this->throwException();
	}
	return NULL;
}

/**
 * Gets the current session.
 * @return CppHibernateSession * Current session.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateSession *CppHibernateSessionFactory::getCurrentSession() {
	jmethodID getCurrentSessionId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateSessionFactory::ORG_HIBERNATE_SESSIONFACTORY_GETCURRENTSESSION_NAME,
					CppHibernateSessionFactory::ORG_HIBERNATE_SESSIONFACTORY_GETCURRENTSESSION_SIGNATURE);
	if (getCurrentSessionId == NULL) {
		this->throwException();
	}
	jobject session = this->env->CallObjectMethod(this->obj,
			getCurrentSessionId);
	this->checkAndThrow();
	jobject sessionClass = this->classLoader->loadClass(
			CppHibernateSessionFactory::ORG_HIBERNATE_CLASSIC_SESSION);
	this->checkAndThrow();
	return new CppHibernateSession(this->env, this->env->NewGlobalRef(session),
			(jclass) (this->env->NewGlobalRef(sessionClass)), this->classLoader);
}

/**
 * Destroys this org.hibernate.SessionFactory object and releases connection.
 * @throw Throws when JNI encounters exceptions.
 */
void CppHibernateSessionFactory::close() {
	jmethodID closeId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateSessionFactory::ORG_HIBERNATE_SESSIONFACTORY_CLOSE_NAME,
					CppHibernateSessionFactory::ORG_HIBERNATE_SESSIONFACTORY_CLOSE_SIGNATURE);
	if (closeId != NULL) {
		this->env->CallVoidMethod(this->obj, closeId);
		this->throwException();
	} else {
		this->throwException();
	}
}

/**
 * Checks if session is already closed or not.
 * @return bool Returns true if session is already closed, false otherwise.
 * @throw Throws when JIN encounters exceptions.
 */
bool CppHibernateSessionFactory::isClosed() {
	jmethodID isClosedId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateSessionFactory::ORG_HIBERNATE_SESSIONFACTORY_ISCLOSED_NAME,
					CppHibernateSessionFactory::ORG_HIBERNATE_SESSIONFACTORY_ISCLOSED_SIGNATURE);
	if (isClosedId != NULL) {
		jboolean closed = this->env->CallBooleanMethod(this->obj, isClosedId);

		if (closed == JNI_TRUE) {
			return true;
		}
	} else {
		this->throwException();
	}
	return false;
}

/**
 * Gets statistics.
 * @return CppHibernateStatistics * Returns CppHibernateStatistics object. The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateStatistics *CppHibernateSessionFactory::getStatistics() {

	jmethodID getStatisticsId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateSessionFactory::ORG_HIBERNATE_SESSIONFACTORY_GETSTATISTICS_NAME,
					CppHibernateSessionFactory::ORG_HIBERNATE_SESSIONFACTORY_GETSTATISTICS_SIGNATURE);
	if (getStatisticsId == NULL) {
		this->throwException();
	}
	jobject statistics = this->env->CallObjectMethod(this->obj,
			getStatisticsId);
	this->checkAndThrow();

	return new CppHibernateStatistics(
			this->env,
			this->env->NewGlobalRef(statistics),
			(jclass) this->env->NewGlobalRef(
					this->env->GetObjectClass(statistics)), this->classLoader);
}

CppHibernateSessionFactory::~CppHibernateSessionFactory() {
	this->close();
}

} /* namespace cppHibernate */
