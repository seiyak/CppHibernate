/*
 * CppHibernateStatistics.cpp
 *
 *  Created on: Dec 9, 2011
 *      Author: seiyak
 */

#include <memory>
#include "CppHibernateStatistics.h"
#include "CppHibernateAccessor.h"
#include "CppHibernateMutex.h"

namespace cppHibernate {

const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_CLEAR_NAME =
		"clear";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_CLEAR_SIGNATURE =
		"()V";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETCLOSESTATEMENTCOUNT_NAME =
		"getCloseStatementCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONFETCHCOUNT_NAME =
		"getCollectionFetchCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONLOADCOUNT_NAME =
		"getCollectionLoadCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONRECREATECOUNT_NAME =
		"getCollectionRecreateCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONREMOVECOUNT_NAME =
		"getCollectionRemoveCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONROLENAMES_NAME =
		"getCollectionRoleNames";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONSTATISTICS_NAME =
		"getCollectionStatistics";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONSTATISTICS_SIGNATURE =
		"(Ljava/lang/String;)Lorg/hibernate/stat/CollectionStatistics;";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONUPDATECOUNT_NAME =
		"getCollectionUpdateCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETCONNECTCOUNT_NAME =
		"getConnectCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETENTITYDELETECOUNT_NAME =
		"getEntityDeleteCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETENTITYFETCHCOUNT_NAME =
		"getEntityFetchCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETENTITYINSERTCOUNT_NAME =
		"getEntityInsertCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETENTITYLOADCOUNT_NAME =
		"getEntityLoadCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETENTITYNAMES_NAME =
		"getEntityNames";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETENTITYSTATISTICS_NAME =
		"getEntityStatistics";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETENTITYSTATISTICS_SIGNATURE =
		"(Ljava/lang/String;)Lorg/hibernate/stat/EntityStatistics;";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETENTITYUPDATECOUNT_NAME =
		"getEntityUpdateCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETFLUSHCOUNT_NAME =
		"getFlushCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETOPTMISTICFAILURECOUNT_NAME =
		"getOptimisticFailureCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETPREPARESTATEMENTCOUNT_NAME =
		"getPrepareStatementCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETQUERIES_NAME =
		"getQueries";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETQUERYCACHEHITCOUNT_NAME =
		"getQueryCacheHitCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETQUERYCACHEMISSCOUNT_NAME =
		"getQueryCacheMissCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETQUERYCACHEPUTCOUNT_NAME =
		"getQueryCachePutCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETQUERYEXECUTIONCOUNT_NAME =
		"getQueryExecutionCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETQUERYEXECUTIONMAXTIME_NAME =
		"getQueryExecutionMaxTime";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETQUERYEXECUTIONMAXTIMEQUERYSTRING_NAME =
		"getQueryExecutionMaxTimeQueryString";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETQUERYEXECUTIONMAXTIMEQUERYSTRING_SIGNATURE =
		"()Ljava/lang/String;";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETQUERYSTATISTICS_NAME =
		"getQueryStatistics";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETQUERYSTATISTICS_SIGNATURE =
		"(Ljava/lang/String;)Lorg/hibernate/stat/QueryStatistics;";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETSECONDLEVELCACHEHITCOUNT_NAME =
		"getSecondLevelCacheHitCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETSECONDLEVELCACHEMISSCOUNT_NAME =
		"getSecondLevelCacheMissCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETSECONDLEVELCACHEPUTCOUNT_NAME =
		"getSecondLevelCachePutCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETSECONDLEVELCACHEREGIONNAMES_NAME =
		"getSecondLevelCacheRegionNames";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETSECONDLEVELCACHESTATISTICS_NAME =
		"getSecondLevelCacheStatistics";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETSECONDLEVELCACHESTATISTICS_SIGNATURE =
		"(Ljava/lang/String;)Lorg/hibernate/stat/SecondLevelCacheStatistics;";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETSESSIONCLOSECOUNT_NAME =
		"getSessionCloseCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETSESSIONOPENCOUNT_NAME =
		"getSessionOpenCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETSTARTTIME_NAME =
		"getStartTime";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETSUCCESSFULTRANSACTIONCOUNT_NAME =
		"getSuccessfulTransactionCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETTRANSACTIONCOUNT_NAME =
		"getTransactionCount";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_ISSTATISCTICSENABLED_NAME =
		"isStatisticsEnabled";
const char *CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_ISSTATISCTICSENABLED_SIGNATURE =
		"()Z";
const char *CppHibernateStatistics::STRINGARRAYRETURN_VOIDPARAM_SIGNATURE =
		"()[Ljava/lang/String;";

CppHibernateStatistics::CppHibernateStatistics(JNIEnv *env, jobject obj,
		jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateStatisticsBase(env, obj, objClass, classLoader) {

}

/**
 * Clears all the statistics.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
void CppHibernateStatistics::clear() {

	jmethodID clearId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_CLEAR_NAME,
					CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_CLEAR_SIGNATURE);
	if (clearId == NULL) {
		this->throwException();
	}
	this->env->CallVoidMethod(this->obj, clearId);
	this->checkAndThrow();
}

/**
 *  The number of prepared statements that were released. From http://docs.jboss.org/hibernate/core/3.6/javadocs/.
 *  @return long The number of prepared statements.
 *  @throw Throws exceptions when JNI encounters exceptions.
 */
long CppHibernateStatistics::getCloseStatementCount() {

	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETCLOSESTATEMENTCOUNT_NAME);
}

/**
 * Global number of collections fetched. From http://docs.jboss.org/hibernate/core/3.6/javadocs/.
 * @return long The number of collections fetched.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
long CppHibernateStatistics::getCollectionFetchCount() {

	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONFETCHCOUNT_NAME);
}

/**
 * Global number of collections loaded.From http://docs.jboss.org/hibernate/core/3.6/javadocs/.
 * @return long Returns the number of collections loaded.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
long CppHibernateStatistics::getCollectionLoadCount() {

	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONLOADCOUNT_NAME);
}

/**
 * Global number of collections recreated. From http://docs.jboss.org/hibernate/core/3.6/javadocs/.
 * @return long Returns the number of collections recreated.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
long CppHibernateStatistics::getCollectionRecreateCount() {

	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONRECREATECOUNT_NAME);

}

/**
 * Global number of collections removed. From http://docs.jboss.org/hibernate/core/3.6/javadocs/.
 * @return long Returns the number of collections removed.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
long CppHibernateStatistics::getCollectionRemoveCount() {

	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONREMOVECOUNT_NAME);
}

/**
 * Global number of collections updated. From http://docs.jboss.org/hibernate/core/3.6/javadocs/.
 * @return long Returns the number of collection updated.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
long CppHibernateStatistics::getCollectionUpdateCount() {
	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONUPDATECOUNT_NAME);
}

/**
 * Gets the number of connections on the session.
 * @return long Returns the number of connections.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
long CppHibernateStatistics::getConnectCount() {

	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETCONNECTCOUNT_NAME);
}

/**
 * Gets the number of deleted entities.
 * @return long Returns the number of deleted entities.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
long CppHibernateStatistics::getEntityDeleteCount() {

	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETENTITYDELETECOUNT_NAME);
}

/**
 * Gets the number of fetched entities.
 * @return long Returns the number of fetched entities.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
long CppHibernateStatistics::getEntityFetchCount() {
	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETENTITYFETCHCOUNT_NAME);
}

long CppHibernateStatistics::getEntityInsertCount() {

	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETENTITYINSERTCOUNT_NAME);
}

/**
 * Gets the number of loaded entities.
 * @return long Returns the number of loaded entities.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
long CppHibernateStatistics::getEntityLoadCount() {
	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETENTITYLOADCOUNT_NAME);
}

/**
 * Get the names of all collection roles. From http://docs.jboss.org/hibernate/core/3.6/javadocs/.
 * @return std::deque<std::string> Returns the collection roles' names.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
std::deque<std::string> CppHibernateStatistics::getCollectionRoleNames() {
	return this->getNames(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONROLENAMES_NAME);
}

/**
 * Gets all the entities' names.
 * @return std::deque<std::string> Returns all the names.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
std::deque<std::string> CppHibernateStatistics::getEntityNames() {

	return this->getNames(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETENTITYNAMES_NAME);
}

std::deque<std::string> CppHibernateStatistics::getNames(
		const char *methodName) {

	jmethodID methodId = this->env->GetMethodID(this->objClass, methodName,
			CppHibernateStatistics::STRINGARRAYRETURN_VOIDPARAM_SIGNATURE);
	if (methodId == NULL) {
		this->throwException();
	}
	jobject array = this->env->CallObjectMethod(this->obj, methodId);
	this->checkAndThrow();

	return this->convertFrom(this->env->NewGlobalRef(array));
}

/**
 * Converts the given Java array to std::deque<std::string>.
 * @param object array Java String array.
 * @return std::deque<std::string> Returns converted std::deque.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
std::deque<std::string> CppHibernateStatistics::convertFrom(jobject array) {

	int size =
			this->env->GetArrayLength(
					(jobjectArray) (((((((((((((((((((((((((((((((((((array))))))))))))))))))))))))))))))))))));
	std::auto_ptr<CppHibernateMutex> cppHibernateMutex(new CppHibernateMutex);
	int i;
	std::deque<std::string> strArray;
	for (i = 0; i < size; i++) {
		strArray.push_back(
				std::string(
						CppHibernateAccessor::copyStringFrom(
								this->env,
								(jstring) (((((((((((((((((((((((((((((((((((this->env->GetObjectArrayElement(
										(jobjectArray) (((((((((((((((((((((((((((((((((((array))))))))))))))))))))))))))))))))))),
										i)))))))))))))))))))))))))))))))))))))));
		this->checkAndThrow();
	}
	this->env->DeleteGlobalRef(array);
	return strArray;
}

/**
 * Get collection statistics per role.From http://docs.jboss.org/hibernate/core/3.6/javadocs/.
 * @param const char *role Role.
 * @return CppHibernateCollectionStatistics * Returns new CppHibernateCollectionStatistics object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateCollectionStatistics *CppHibernateStatistics::getCollectionStatistics(
		const char *role) {
	jmethodID getCollectionStatisticsId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONSTATISTICS_NAME,
					CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETCOLLECTIONSTATISTICS_SIGNATURE);
	if (getCollectionStatisticsId == NULL) {
		this->throwException();
	}

	jobject statistics = this->env->CallObjectMethod(this->obj,
			getCollectionStatisticsId, this->env->NewStringUTF(role));
	this->checkAndThrow();
	return new CppHibernateCollectionStatistics(
			this->env,
			this->env->NewGlobalRef(statistics),
			(jclass) ((((((((((((((((((((((((((((((((((this->env->NewGlobalRef(
					this->env->GetObjectClass(statistics)))))))))))))))))))))))))))))))))))),
			this->classLoader);
}

/**
 * find entity statistics per name.From http://docs.jboss.org/hibernate/core/3.6/javadocs/.
 * @param const char *entityName Entity name to be used to get the statisitcs.
 * @return CppHibernateEntityStatistics * Returns new CppHibernateEntityStatistics object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateEntityStatistics *CppHibernateStatistics::getEntityStatistics(
		const char *entityName) {
	jmethodID getEntityStatisticsId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETENTITYSTATISTICS_NAME,
					CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETENTITYSTATISTICS_SIGNATURE);
	if (getEntityStatisticsId == NULL) {
		this->throwException();
	}

	jobject statistics = this->env->CallObjectMethod(this->obj,
			getEntityStatisticsId, this->env->NewStringUTF(entityName));
	this->checkAndThrow();
	return new CppHibernateEntityStatistics(
			this->env,
			this->env->NewGlobalRef(statistics),
			(jclass) (((((((((((((((((((((((this->env->NewGlobalRef(
					this->env->GetObjectClass(statistics))))))))))))))))))))))))),
			this->classLoader);
}

long CppHibernateStatistics::getEntityUpdateCount() {
	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETENTITYUPDATECOUNT_NAME);
}

long CppHibernateStatistics::getFlushCount() {
	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETFLUSHCOUNT_NAME);
}

long CppHibernateStatistics::getOptimisticFailureCount() {
	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETOPTMISTICFAILURECOUNT_NAME);
}

long CppHibernateStatistics::getPrepareStatementCount() {
	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETPREPARESTATEMENTCOUNT_NAME);
}

std::deque<std::string> CppHibernateStatistics::getQueries() {
	return this->getNames(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETQUERIES_NAME);
}

long CppHibernateStatistics::getQueryCacheHitCount() {
	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETQUERYCACHEHITCOUNT_NAME);
}

long CppHibernateStatistics::getQueryCacheMissCount() {
	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETQUERYCACHEMISSCOUNT_NAME);
}

long CppHibernateStatistics::getQueryCachePutCount() {
	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETQUERYCACHEPUTCOUNT_NAME);
}

long CppHibernateStatistics::getQueryExecutionCount() {
	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETQUERYEXECUTIONCOUNT_NAME);
}

long CppHibernateStatistics::getQueryExecutionMaxTime() {
	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETQUERYEXECUTIONMAXTIME_NAME);
}

std::string CppHibernateStatistics::getQueryExecutionMaxTimeQueryString() {
	jmethodID getQueryExecutionMaxTimeQueryStringId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETQUERYEXECUTIONMAXTIMEQUERYSTRING_NAME,
					CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETQUERYEXECUTIONMAXTIMEQUERYSTRING_SIGNATURE);
	if (getQueryExecutionMaxTimeQueryStringId == NULL) {
		this->throwException();
	}

	jobject str = this->env->CallObjectMethod(this->obj,
			getQueryExecutionMaxTimeQueryStringId);
	this->checkAndThrow();

	if (str == NULL) {
		return std::string("");
	}

	std::string strVal(
			CppHibernateAccessor::copyStringFrom(
					this->env,
					(jstring) ((((((((((((this->env->NewGlobalRef(str)))))))))))))));
	this->checkAndThrow();
	this->env->DeleteGlobalRef(str);
	return strVal;
}

CppHibernateQueryStatistics *CppHibernateStatistics::getQueryStatistics(
		const char *query) {
	jmethodID getQueryStatisticsId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETQUERYSTATISTICS_NAME,
					CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETQUERYSTATISTICS_SIGNATURE);
	if (getQueryStatisticsId == NULL) {
		this->throwException();
	}
	jobject statistics = this->env->CallObjectMethod(this->obj,
			getQueryStatisticsId);
	this->checkAndThrow();
	return new CppHibernateQueryStatistics(
			this->env,
			this->env->NewGlobalRef(statistics),
			(jclass) (((((((((((this->env->NewGlobalRef(
					this->env->GetObjectClass(statistics))))))))))))),
			this->classLoader);
}

long CppHibernateStatistics::getSecondLevelCacheHitCount() {
	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETSECONDLEVELCACHEHITCOUNT_NAME);
}

long CppHibernateStatistics::getSecondLevelCacheMissCount() {
	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETSECONDLEVELCACHEMISSCOUNT_NAME);
}

long CppHibernateStatistics::getSecondLevelCachePutCount() {
	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETSECONDLEVELCACHEPUTCOUNT_NAME);
}

std::deque<std::string> CppHibernateStatistics::getSecondLevelCacheRegionNames() {
	return this->getNames(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETSECONDLEVELCACHEREGIONNAMES_NAME);
}

CppHibernateSecondLevelCacheStatistics *CppHibernateStatistics::getSecondLevelCacheStatistics(
		const char *region) {

	jmethodID getSecondLevelCacheStatisticsId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETSECONDLEVELCACHESTATISTICS_NAME,
					CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETSECONDLEVELCACHESTATISTICS_SIGNATURE);
	if (getSecondLevelCacheStatisticsId == NULL) {
		this->throwException();
	}

	jobject statistics = this->env->CallObjectMethod(this->obj,
			getSecondLevelCacheStatisticsId, this->env->NewStringUTF(region));
	this->checkAndThrow();
	if (statistics == NULL) {
		return NULL;
	}

	return new CppHibernateSecondLevelCacheStatistics(
			this->env,
			this->env->NewGlobalRef(statistics),
			(jclass) ((((((this->env->NewGlobalRef(
					this->env->GetObjectClass(statistics)))))))),
			this->classLoader);
}

long CppHibernateStatistics::getSessionCloseCount() {
	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETSESSIONCLOSECOUNT_NAME);
}

long CppHibernateStatistics::getSessionOpenCount() {
	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETSESSIONOPENCOUNT_NAME);
}

long CppHibernateStatistics::getStartTime() {
	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETSTARTTIME_NAME);
}

long CppHibernateStatistics::getSuccessfulTransactionCount() {
	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETSUCCESSFULTRANSACTIONCOUNT_NAME);
}

long CppHibernateStatistics::getTransactionCount() {
	return this->getCount(
			CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_GETTRANSACTIONCOUNT_NAME);
}

bool CppHibernateStatistics::isStatisticsEnabled() {
	jmethodID isStatisticsEnabledId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_ISSTATISCTICSENABLED_NAME,
					CppHibernateStatistics::ORG_HIBERNATE_STAT_STATISTICS_ISSTATISCTICSENABLED_SIGNATURE);
	if (isStatisticsEnabledId == NULL) {
		this->throwException();
	}

	jboolean b = this->env->CallBooleanMethod(this->obj, isStatisticsEnabledId);
	this->checkAndThrow();
	return b;
}

CppHibernateStatistics::~CppHibernateStatistics() {

}

} /* namespace cppHibernate */
