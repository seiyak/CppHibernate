/*
 * CppHibernateTransaction.cpp
 *
 *  Created on: Nov 11, 2011
 *      Author: apple
 */

#include "CppHibernateTransaction.h"

namespace cppHibernate {

CppHibernateTransaction::CppHibernateTransaction(JNIEnv *env, jobject obj,
		jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateCommons(env, obj, objClass, classLoader), ORG_HIBERNATE_TRANSACTION_COMMIT_NAME(
				"commit"), ORG_HIBERNATE_TRANSACTION_ROLLBACK_NAME("rollback") {
}

/**
 * Commits the updates on an object to the underlying database.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
void CppHibernateTransaction::commit() {

	jmethodID commitId = this->env->GetMethodID(this->objClass,
			this->ORG_HIBERNATE_TRANSACTION_COMMIT_NAME, "()V");

	if (commitId != NULL) {
		this->env->CallVoidMethod(this->obj, commitId);

		if (this->env->ExceptionCheck()) {
			this->env->ExceptionClear();
			this->rollback();
		}
	} else {
		this->throwException();
	}
}

/**
 * Rolls back the updates on an object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
void CppHibernateTransaction::rollback() {

	jmethodID rollbackId = this->env->GetMethodID(this->objClass,
			this->ORG_HIBERNATE_TRANSACTION_ROLLBACK_NAME, "()V");

	if (rollbackId != NULL) {
		this->env->CallVoidMethod(this->obj, rollbackId);

		if (this->env->ExceptionCheck()) {
			this->throwException();
		}
	} else {
		this->throwException();
	}
}

CppHibernateTransaction::~CppHibernateTransaction() {
	// TODO Auto-generated destructor stub
}

} /* namespace cppHibernate */
