/*
 * CppHibernateSession.cpp
 *
 *  Created on: Nov 10, 2011
 *      Author: apple
 */

#include <cstring>
#include "CppHibernateSession.h"
#include "CppHibernateObjectHelper.h"

namespace cppHibernate {

const char *CppHibernateSession::ORG_HIBERNATE_TRANSACTION =
		"org.hibernate.Transaction";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_CLOSE_NAME = "close";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_CLOSE_SIGNATURE =
		"()Ljava/sql/Connection;";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_BEGINTRANSACTION_NAME =
		"beginTransaction";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_BEGINTRANSACTION_SIGNATURE =
		"()Lorg/hibernate/Transaction;";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_ISOPEN_NAME = "isOpen";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_ISOPEN_SIGNATURE = "()Z";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_SAVE_NAME = "save";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_SAVE_SIGNATURE =
		"(Ljava/lang/Object;)Ljava/io/Serializable;";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_DELETE_NAME = "delete";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_DELETE_SIGNATURE =
		"(Ljava/lang/Object;)V";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_UPDATE_NAME = "update";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_UPDATE_SIGNATURE =
		"(Ljava/lang/Object;)V";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_FLUSH_NAME = "flush";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_FLUSH_SIGNATURE = "()V";
const char *CppHibernateSession::ORG_HIBERNATE_FLUSHMODE =
		"org.hibernate.FlushMode";
const char *CppHibernateSession::ORG_HIBERNATE_FLUSHMODE_SIGNATURE =
		"Lorg/hibernate/FlushMode;";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_SETFLUSHMODE_NAME =
		"setFlushMode";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_SETFLUSHMODE_SIGNATURE =
		"(Lorg/hibernate/FlushMode;)V";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_CREATECRITERIA_NAME =
		"createCriteria";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_CREATECRITERIA_SIGNATURE =
		"(Ljava/lang/Class;)Lorg/hibernate/Criteria;";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_CREATEQUERY_NAME =
		"createQuery";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_CREATEQUERY_SIGNATURE =
		"(Ljava/lang/String;)Lorg/hibernate/Query;";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_GETSTATISTICS_NAME =
		"getStatistics";
const char *CppHibernateSession::ORG_HIBERNATE_SESSION_GETSTATISTICS_SIGNATURE =
		"()Lorg/hibernate/stat/SessionStatistics;";
const char *CppHibernateSession::FLUSHMODE_ALWAYS = "ALWAYS";
const char *CppHibernateSession::FLUSHMODE_AUTO = "AUTO";
const char *CppHibernateSession::FLUSHMODE_COMMIT = "COMMIT";
const char *CppHibernateSession::FLUSHMODE_MANUAL = "MANUAL";
const char *CppHibernateSession::JAVA_SQL_CONNECTION = "java/sql/Connection";

CppHibernateSession::CppHibernateSession(JNIEnv *env, jobject session,
		jclass sessionClass, AbstractClassLoader *classLoader) :
		CppHibernateCommons(env, session, sessionClass, classLoader) {
}

/**
 * Begins a new transaction ,unit of work.
 * @return CppHiberanteTransaction * An object representing org.hibernate.Transaction class.
 * @throw Throws when JNI encounters exceptions.
 */
CppHibernateTransaction *CppHibernateSession::beginTransaction() {

	jclass transactionClass =
			(jclass) (((((((((((((this->classLoader->loadClass(
					CppHibernateSession::ORG_HIBERNATE_TRANSACTION))))))))))))));
	CppHibernateTransaction *transaction = NULL;
	if (transactionClass != NULL) {
		jmethodID beginTransactionId =
				this->env->GetMethodID(
						this->objClass,
						CppHibernateSession::ORG_HIBERNATE_SESSION_BEGINTRANSACTION_NAME,
						CppHibernateSession::ORG_HIBERNATE_SESSION_BEGINTRANSACTION_SIGNATURE);

		if (beginTransactionId != NULL) {
			jobject transactionLocalObj = this->env->CallObjectMethod(this->obj,
					beginTransactionId);

			if (transactionLocalObj != NULL) {
				jobject transactionGlobalObj = this->env->NewGlobalRef(
						transactionLocalObj);
				transaction = new CppHibernateTransaction(this->env,
						transactionGlobalObj, transactionClass,
						this->classLoader);
			} else {
				this->throwException();
			}
		} else {
			this->throwException();
		}

	} else {
		this->throwException();
	}
	return transaction;
}

/**
 * Closes session.
 * @param bool closedConnection True if closed connection object is needed and false if closed connection object is not needed after this method call.
 * @return CppHibernateConnection * An object representing java.sql.Connection class. This is a closed connection object or NULL.
 * If the parameter is set to true but the connection object is not available, then returns NULL. If it's available, then returns the object. The parameter is
 * a suggestion flag and may be ignored by the program.
 * @throw Throws when JNI encounters exceptions.
 */
CppHibernateConnection *CppHibernateSession::close(bool closedConnection) {
	CppHibernateConnection *connection = NULL;
	jmethodID closeId = this->env->GetMethodID(this->objClass,
			CppHibernateSession::ORG_HIBERNATE_SESSION_CLOSE_NAME,
			CppHibernateSession::ORG_HIBERNATE_SESSION_CLOSE_SIGNATURE);
	if (closeId != NULL) {
		jclass connectionClass = this->env->FindClass(
				this->JAVA_SQL_CONNECTION);
		if (connectionClass != NULL) {
			jobject connectionObj = this->env->CallObjectMethod(this->obj,
					closeId);
			if (connectionObj != NULL) {
				if (closedConnection) {
					connection = new CppHibernateConnection(this->env,
							connectionObj, connectionClass, this->classLoader);
				}
			} else {
				this->throwException();
			}
		} else {

		}
	} else {
		this->throwException();
	}
	return connection;
}

/**
 * Checks if the session is still open or not.
 * @return bool Returns true if it's open, false otherwise.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
bool CppHibernateSession::isOpen() {
	bool isOpen = false;
	jmethodID isOpenId = this->env->GetMethodID(this->objClass,
			CppHibernateSession::ORG_HIBERNATE_SESSION_ISOPEN_NAME,
			CppHibernateSession::ORG_HIBERNATE_SESSION_ISOPEN_SIGNATURE);
	if (isOpenId != NULL) {
		if (this->env->CallBooleanMethod(this->obj, isOpenId) == JNI_TRUE) {
			isOpen = true;
		}
	} else {
		this->throwException();
	}
	return isOpen;
}

/**
 * Saves the specified object onto the database.
 * @param CppHibernateJObject *obj Object to be stored.
 * @throw Throws exceptions when JNI encounters exceptions and the specified object is NULL.
 */
void CppHibernateSession::saveObj(CppHibernateJObject *obj) {
	this->checkNull(obj);
	jmethodID saveId = this->env->GetMethodID(this->objClass,
			CppHibernateSession::ORG_HIBERNATE_SESSION_SAVE_NAME,
			CppHibernateSession::ORG_HIBERNATE_SESSION_SAVE_SIGNATURE);
	if (saveId == NULL) {
		this->throwException();
	}

	jobject rtnObj = this->env->CallObjectMethod(this->obj, saveId,
			obj->getObj());
	this->checkAndThrow();
}

/**
 * Deletes the specified object from the database.
 * @param CppHibernateJObject *obj Object to be deleted.
 * @throw Throws exceptions when JNI encounters exceptions and the specified object is NULL.
 */
void CppHibernateSession::deleteObj(CppHibernateJObject *obj) {
	this->checkNull(obj);
	jmethodID deleteId = this->env->GetMethodID(this->objClass,
			CppHibernateSession::ORG_HIBERNATE_SESSION_DELETE_NAME,
			CppHibernateSession::ORG_HIBERNATE_SESSION_DELETE_SIGNATURE);
	if (deleteId == NULL) {
		this->throwException();
	}

	this->env->CallVoidMethod(this->obj, deleteId, obj->getObj());
	this->checkAndThrow();
}

/**
 * Updates the specified object.
 * @param CppHibernateJObject *obj Object to be updated.
 * @throw Throws exceptions when JNI encounters exceptions and the specified object is NULL.
 */
void CppHibernateSession::updateObj(CppHibernateJObject *obj) {
	this->checkNull(obj);
	jmethodID updateId = this->env->GetMethodID(this->objClass,
			CppHibernateSession::ORG_HIBERNATE_SESSION_SAVE_NAME,
			CppHibernateSession::ORG_HIBERNATE_SESSION_SAVE_SIGNATURE);
	if (updateId == NULL) {
		this->throwException();
	}
	this->env->CallVoidMethod(this->obj, updateId, obj->getObj());
	this->checkAndThrow();
}

/**
 * Checks if the parameter is NULL or not. If so, throws an exception. If not, does nothing.
 */
void CppHibernateSession::checkNull(CppHibernateJObject *obj) {
	if (obj == NULL) {
		throw CppHibernateException(
				"The parameter is NULL. Please specify the correct value");
	}
}

/**
 * Flushes this session.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
void CppHibernateSession::flush() {
	jmethodID flushId = this->env->GetMethodID(this->objClass,
			CppHibernateSession::ORG_HIBERNATE_SESSION_FLUSH_NAME,
			CppHibernateSession::ORG_HIBERNATE_SESSION_FLUSH_SIGNATURE);
	if (flushId == NULL) {
		this->throwException();
	}
	this->env->CallVoidMethod(this->obj, flushId);
	this->checkAndThrow();
}

/**
 * Sets the flush mode for this session.
 * @param const char *flushMode Flush mode to be used on this session. This flush mode is one of 'ALWAYS','AUTO','COMMIT','MANUAL'. The default value is set to
 * 'COMMIT'.
 * @throw Throws exceptions when JNI encounters exceptions and the specified flush mode is invalid.
 */
void CppHibernateSession::setFlushMode(const char *flushMode) {
	if (!this->checkFlushMode(flushMode)) {
		std::string errorMessage("The specified flush mode is invalid, ");
		errorMessage += flushMode;
		throw CppHibernateException(errorMessage.c_str());
	}
	jmethodID setFlushModeId = this->env->GetMethodID(this->objClass,
			CppHibernateSession::ORG_HIBERNATE_SESSION_SETFLUSHMODE_NAME,
			CppHibernateSession::ORG_HIBERNATE_SESSION_SETFLUSHMODE_SIGNATURE);
	if (setFlushModeId == NULL) {
		this->throwException();
	}

	jobject fMode = this->findFlushMode(flushMode);
	this->env->CallVoidMethod(this->obj, setFlushModeId, fMode);
	this->env->DeleteGlobalRef(fMode);
	this->checkAndThrow();
}

/**
 * Checks if the specified flush mode is valid or not.
 * @param const char *flushMode Flush mode to be set on this session.
 * @return bool if the specified flush mode is valid, false otherwise.
 */
bool CppHibernateSession::checkFlushMode(const char *flushMode) {
	if (std::strncmp(flushMode, CppHibernateSession::FLUSHMODE_ALWAYS,
			std::strlen(CppHibernateSession::FLUSHMODE_ALWAYS)) == 0) {
		return true;
	} else if (std::strncmp(flushMode, CppHibernateSession::FLUSHMODE_AUTO,
			std::strlen(CppHibernateSession::FLUSHMODE_AUTO)) == 0) {
		return true;
	} else if (std::strncmp(flushMode, CppHibernateSession::FLUSHMODE_COMMIT,
			std::strlen(CppHibernateSession::FLUSHMODE_COMMIT)) == 0) {
		return true;
	} else if (std::strncmp(flushMode, CppHibernateSession::FLUSHMODE_MANUAL,
			std::strlen(CppHibernateSession::FLUSHMODE_MANUAL)) == 0) {
		return true;
	}

	return false;
}

/**
 * Finds the corresponding flush mode field on org.hibernate.FlushMode class.
 * @param const char *flushMode Flush mode to be found.
 * @return jobject Returns org.hibernate.FlushMode object as the field value. The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
jobject CppHibernateSession::findFlushMode(const char *flushMode) {
	jobject flushModeClass = this->classLoader->loadClass(
			CppHibernateSession::ORG_HIBERNATE_FLUSHMODE);
	if (flushModeClass == NULL) {
		this->throwException();
	}

	jfieldID flushModeId = this->env->GetStaticFieldID(
			(jclass) (((flushModeClass))), flushMode,
			CppHibernateSession::ORG_HIBERNATE_FLUSHMODE_SIGNATURE);
	if (flushModeId == NULL) {
		this->env->DeleteGlobalRef(flushModeClass);
		this->throwException();
	}

	jobject flushModeVal = this->env->GetStaticObjectField(
			(jclass) (((flushModeClass))), flushModeId);
	this->env->DeleteGlobalRef(flushModeClass);
	this->checkAndThrow();
	return this->env->NewGlobalRef(flushModeVal);
}

/**
 * Creates org.hibernate.Criteria object with the specified class. The returned object lets you work on the database with object oriented way.
 * @param CppHibernateJObject * Object to be used to create the org.hibernate.Criteria object.
 * @return CppHibernateCriteria Returns CppHibernateCriteria object. The returned object must be deleted when the job is done.
 * @throws Throws exceptions when JNI encounters exceptions and the specified class name is invalid.
 */
CppHibernateCriteria CppHibernateSession::createCriteria(
		CppHibernateJObject *obj) {
	this->checkNull(obj);
	jmethodID createCriteriaId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateSession::ORG_HIBERNATE_SESSION_CREATECRITERIA_NAME,
					CppHibernateSession::ORG_HIBERNATE_SESSION_CREATECRITERIA_SIGNATURE);
	if (createCriteriaId == NULL) {
		this->throwException();
	}

	jobject criteria = this->env->CallObjectMethod(this->obj, createCriteriaId,
			obj->getObjClass());
	this->checkAndThrow();
	return CppHibernateCriteria(
			this->env,
			this->env->NewGlobalRef(criteria),
			(jclass) ((this->env->NewGlobalRef(
					this->env->GetObjectClass(criteria)))), this->classLoader);
}

/**
 * Creates org.hibernate.Query object based on the specified query.
 * @param const char *queryString HQL query string.
 * @return CppHibernateQuery Returns new CppHibernateQueryObject.
 * @throw Throws exceptions when JNI encounters exceptions and an empty query is specified.
 */
CppHibernateQuery CppHibernateSession::createQuery(const char *queryString) {
	if (std::strlen(queryString) == 0) {
		throw CppHibernateException(
				"Empty string can not be specified as the query string for CppHibernateSession::createQuery().");
	}
	jmethodID createQueryId = this->env->GetMethodID(this->objClass,
			CppHibernateSession::ORG_HIBERNATE_SESSION_CREATEQUERY_NAME,
			CppHibernateSession::ORG_HIBERNATE_SESSION_CREATEQUERY_SIGNATURE);
	if (createQueryId == NULL) {
		this->throwException();
	}

	jobject query = this->env->CallObjectMethod(this->obj, createQueryId,
			this->env->NewStringUTF(queryString));
	this->checkAndThrow();
	return CppHibernateQuery(
			this->env,
			this->env->NewGlobalRef(query),
			(jclass) (this->env->NewGlobalRef(this->env->GetObjectClass(query))),
			this->classLoader);
}

/**
 * Gets statistics about the first level cache.
 * @return CppHibernateSessionStatistics * Returns new CppHibernateSessionStatistics object.
 * @throws Throws exceptions when JNI encounters exceptions.
 */
CppHibernateSessionStatistics *CppHibernateSession::getStatistics() {

	jmethodID getStatisticsId = this->env->GetMethodID(this->objClass,
			CppHibernateSession::ORG_HIBERNATE_SESSION_GETSTATISTICS_NAME,
			CppHibernateSession::ORG_HIBERNATE_SESSION_GETSTATISTICS_SIGNATURE);
	if (getStatisticsId == NULL) {
		this->throwException();
	}

	jobject statistics = this->env->CallObjectMethod(this->obj,
			getStatisticsId);
	this->checkAndThrow();

	return new CppHibernateSessionStatistics(
			this->env,
			this->env->NewGlobalRef(statistics),
			(jclass) this->env->NewGlobalRef(
					this->env->GetObjectClass(statistics)), this->classLoader);
}

CppHibernateSession::~CppHibernateSession() {

	if (this->isOpen()) {
		this->close();
	}
}

} /* namespace cppHibernate */
