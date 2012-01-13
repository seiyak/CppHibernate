/*
 * CppHibernateOrder.cpp
 *
 *  Created on: Dec 6, 2011
 *      Author: seiyak
 */

#include "CppHibernateOrder.h"
#include "CppHibernateAccessor.h"

namespace cppHibernate {

const char *CppHibernateOrder::ORG_HIBERNATE_CRITERION_ASC_NAME = "asc";
const char *CppHibernateOrder::ORG_HIBERNATE_CRITERION_ASC_SIGNATURE =
		"(Ljava/lang/String;)Lorg/hibernate/criterion/Order;";
const char *CppHibernateOrder::ORG_HIBERNATE_CRITERION_DESC_NAME = "desc";
const char *CppHibernateOrder::ORG_HIBERNATE_CRITERION_DESC_SIGNATURE =
		"(Ljava/lang/String;)Lorg/hibernate/criterion/Order;";
const char *CppHibernateOrder::ORG_HIBERNATE_CRITERION_IGNORECASE_NAME =
		"ignoreCase";
const char *CppHibernateOrder::ORG_HIBERNATE_CRITERION_IGNORECASE_SIGNATURE =
		"()Lorg/hibernate/criterion/Order;";
const char *CppHibernateOrder::ORG_HIBERNATE_CRITERION_TOSTRING_NAME =
		"toString";
const char *CppHibernateOrder::ORG_HIBERNATE_CRITERION_TOSTRING_SIGNATURE =
		"()Ljava/lang/String;";

CppHibernateOrder::CppHibernateOrder(JNIEnv *env, jobject obj, jclass objClass,
		AbstractClassLoader *classLoader) :
		CppHibernateCommons(env, obj, objClass, classLoader) {

}

/**
 * Applies ascending order by the specified property.
 * @param const char *propertyName Property to be based on ascending order.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateOrder& CppHibernateOrder::asc(const char *propertyName) {

	jobject ascId = this->findAscOrDes(true);
	jobject order = this->env->CallStaticObjectMethod(this->objClass,
			(jmethodID) (ascId), this->env->NewStringUTF(propertyName));
	this->env->DeleteGlobalRef(ascId);
	this->checkAndThrow();

	this->setObj(this->env->NewGlobalRef(order));
	return *(this);
}

/**
 * Applies descending order by the specified property.
 * @param const char *propertyName Property to be based on descending order.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateOrder & CppHibernateOrder::desc(const char *propertyName) {
	jobject descId = this->findAscOrDes(false);
	jobject order = this->env->CallStaticObjectMethod(this->objClass,
			(jmethodID) (descId), this->env->NewStringUTF(propertyName));
	this->env->DeleteGlobalRef(descId);
	this->checkAndThrow();
	this->setObj(this->env->NewGlobalRef(order));
	return *(this);
}

/**
 * Depending on the isAsc flag, finds the corresponding method id.
 * @param bool isAsc A flag if it's ascending order or not.
 * @return jobject Returns the method id as jobject. The returned object must be deleted when the job is done.
 */
jobject CppHibernateOrder::findAscOrDes(bool isAsc) {
	jmethodID orderId = NULL;
	if (isAsc) {
		orderId = this->env->GetStaticMethodID(this->objClass,
				CppHibernateOrder::ORG_HIBERNATE_CRITERION_ASC_NAME,
				CppHibernateOrder::ORG_HIBERNATE_CRITERION_ASC_SIGNATURE);
	} else if (!isAsc) {
		orderId = this->env->GetStaticMethodID(this->objClass,
				CppHibernateOrder::ORG_HIBERNATE_CRITERION_DESC_NAME,
				CppHibernateOrder::ORG_HIBERNATE_CRITERION_DESC_SIGNATURE);
	}

	if (orderId == NULL) {
		this->throwException();
	}
	return this->env->NewGlobalRef((jobject) (orderId));
}

/**
 * Ignores the case when ordering objects.
 */
CppHibernateOrder & CppHibernateOrder::ignoreCase() {
	//// TODO test this method
	jmethodID ignoreCaseId = this->env->GetMethodID(this->objClass,
			CppHibernateOrder::ORG_HIBERNATE_CRITERION_IGNORECASE_NAME,
			CppHibernateOrder::ORG_HIBERNATE_CRITERION_IGNORECASE_SIGNATURE);
	if (ignoreCaseId == NULL) {
		this->throwException();
	}

	jobject order = this->env->CallObjectMethod(this->obj, ignoreCaseId);
	this->checkAndThrow();
	this->setObj(this->env->NewGlobalRef(order));
	return *(this);
}

CppHibernateOrder::~CppHibernateOrder() {
	// TODO Auto-generated destructor stub
}

} /* namespace cppHibernate */
