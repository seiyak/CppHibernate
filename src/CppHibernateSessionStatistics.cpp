/*
 * CppHibernateSessionStatistics.cpp
 *
 *  Created on: Dec 9, 2011
 *      Author: seiyak
 */

#include "CppHibernateSessionStatistics.h"
#include "CppHibernateAccessor.h"

namespace cppHibernate {

const char *CppHibernateSessionStatistics::ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETCOLLECTIONCOUNT_NAME =
		"getCollectionCount";
const char *CppHibernateSessionStatistics::ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETCOLLECTIONCOUNT_SIGNATURE =
		"()I";
const char *CppHibernateSessionStatistics::ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETCOLLECTIONKEYS_NAME =
		"getCollectionKeys";
const char *CppHibernateSessionStatistics::ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETCOLLECTIONKEYS_SIGNATURE =
		"()Ljava/util/Set;";
const char *CppHibernateSessionStatistics::ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETENTITYCOUNT_NAME =
		"getEntityCount";
const char *CppHibernateSessionStatistics::ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETENTITYCOUNT_SIGNATURE =
		"()I";
const char *CppHibernateSessionStatistics::ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETENTITYKEYS_NAME =
		"getEntityKeys";
const char *CppHibernateSessionStatistics::ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETENTITYKEYS_SIGNATURE =
		"()Ljava/util/Set;";

CppHibernateSessionStatistics::CppHibernateSessionStatistics(JNIEnv *env,
		jobject obj, jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateStatisticsBase(env, obj, objClass, classLoader) {

}

/**
 * Gets the number of collection on the session.
 * @return int Number of collections.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
int CppHibernateSessionStatistics::getCollectionCount() {

	jmethodID getCollectionCountId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateSessionStatistics::ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETCOLLECTIONCOUNT_NAME,
					CppHibernateSessionStatistics::ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETCOLLECTIONCOUNT_SIGNATURE);
	if (getCollectionCountId == NULL) {
		this->throwException();
	}

	jint collectionCount = this->env->CallIntMethod(this->obj,
			getCollectionCountId);
	this->checkAndThrow();

	return collectionCount;
}

/**
 * Gets all the keys of the collection on the session.
 * @return CppHibernateJCollectionObject * Returns CppHibernateJCollectionObject object having all the keys.The returned object must be deleted when the job is done.
 * @throws Throws exceptions when JNI encounters exceptions.
 */
CppHibernateJCollectionObject *CppHibernateSessionStatistics::getCollectionKeys() {

	jmethodID getCollectionKeysId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateSessionStatistics::ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETCOLLECTIONKEYS_NAME,
					CppHibernateSessionStatistics::ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETCOLLECTIONKEYS_SIGNATURE);
	if (getCollectionKeysId == NULL) {
		this->throwException();
	}

	jobject keys = this->env->CallObjectMethod(this->obj, getCollectionKeysId);
	this->checkAndThrow();

	return new CppHibernateJCollectionObject(
			this->env,
			this->env->NewGlobalRef(keys),
			(jclass) (((this->env->NewGlobalRef(this->env->GetObjectClass(keys))))),
			this->classLoader);
}

/**
 * Gets the number of entities on the session.
 * @return int Returns the number of entities on the session.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
int CppHibernateSessionStatistics::getEntityCount() {
	jmethodID getEntityCountId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateSessionStatistics::ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETENTITYCOUNT_NAME,
					CppHibernateSessionStatistics::ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETENTITYCOUNT_SIGNATURE);
	if (getEntityCountId == NULL) {
		this->checkAndThrow();
	}

	jint count = this->env->CallIntMethod(this->obj, getEntityCountId);
	this->checkAndThrow();
	return count;
}

/**
 * Gets keys from all the entities.
 * @return CppHibernateJCollectionObject * Returns the keys as CppHibernateJCollectionObject object.The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateJCollectionObject *CppHibernateSessionStatistics::getEntityKeys() {
	jmethodID getEntityKeysId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateSessionStatistics::ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETENTITYKEYS_NAME,
					CppHibernateSessionStatistics::ORG_HIBERNATE_STAT_SESSIONSTATISTICS_GETENTITYKEYS_SIGNATURE);
	if (getEntityKeysId == NULL) {
		this->throwException();
	}

	jobject keys = this->env->CallObjectMethod(this->obj, getEntityKeysId);
	this->checkAndThrow();
	return new CppHibernateJCollectionObject(this->env,
			this->env->NewGlobalRef(keys),
			(jclass) (this->env->NewGlobalRef(this->env->GetObjectClass(keys))),
			this->classLoader);
}

const char *CppHibernateSessionStatistics::toString() {
	return CppHibernateAccessor::toString(this->env, this->obj, this->objClass);
}

CppHibernateSessionStatistics::~CppHibernateSessionStatistics() {

}

} /* namespace cppHibernate */
