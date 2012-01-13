/*
 * CppHibernateQuery.cpp
 *
 *  Created on: Dec 7, 2011
 *      Author: seiyak
 */

#include <sstream>
#include "CppHibernateQuery.h"

namespace cppHibernate {

const char *CppHibernateQuery::ORG_HIBERNATE_QUERY_LIST_NAME = "list";
const char *CppHibernateQuery::ORG_HIBERNATE_QUERY_LIST_SIGNATURE =
		"()Ljava/util/List;";
const char *CppHibernateQuery::ORG_HIBERNATE_QUERY_SETMAXRESULTS_NAME =
		"setMaxResults";
const char *CppHibernateQuery::ORG_HIBERNATE_QUERY_SETMAXRESULTS_SIGNATURE =
		"(I)Lorg/hibernate/Query;";
const char *CppHibernateQuery::ORG_HIBERNATE_QUERY_SETPARAMETER_NAME =
		"setParameter";
const char *CppHibernateQuery::ORG_HIBERNATE_QUERY_SETPARAMETER_SIGNATURE =
		"(Ljava/lang/String;Ljava/lang/Object;)Lorg/hibernate/Query;";
const char *CppHibernateQuery::ORG_HIBERNATE_QUERY_SETCACHEABLE_NAME =
		"setCacheable";
const char *CppHibernateQuery::ORG_HIBERNATE_QUERY_SETCACHEABLE_SIGNATURE =
		"(Z)Lorg/hibernate/Query;";
const char *CppHibernateQuery::ORG_HIBERNATE_QUERY_SETCACHEREGION_NAME =
		"setCacheRegion";
const char *CppHibernateQuery::ORG_HIBERNATE_QUERY_SETCACHEREGION_SIGNATURE =
		"(Ljava/lang/String;)Lorg/hibernate/Query;";

CppHibernateQuery::CppHibernateQuery(JNIEnv *env, jobject obj, jclass objClass,
		AbstractClassLoader *classLoader) :
		CppHibernateCommons(env, obj, objClass, classLoader) {

}

/**
 * Gets the query result as java.util.List object.
 * @return CppHibernateJCollectionObject * Returns CppHibernateJCollectionObject object holding the result object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateJCollectionObject *CppHibernateQuery::list() {

	jmethodID listId = this->env->GetMethodID(this->objClass,
			CppHibernateQuery::ORG_HIBERNATE_QUERY_LIST_NAME,
			CppHibernateQuery::ORG_HIBERNATE_QUERY_LIST_SIGNATURE);
	if (listId == NULL) {
		this->throwException();
	}

	jobject res = this->env->CallObjectMethod(this->obj, listId);
	this->checkAndThrow();

	return new CppHibernateJCollectionObject(
			this->env,
			this->env->NewGlobalRef(res),
			(jclass) ((this->env->NewGlobalRef(this->env->GetObjectClass(res)))),
			this->classLoader);
}

/**
 * Sets the max number of results. If the number of results is less than the specified number, then only the available
 * results are returned.
 * @param jint numberOfResults Max number of results on this query.
 * @return CppHibernateQuery & Returns this object.
 * @throw Throws exceptions when JNI encounters exceptions and invalid number of results < 1 is specified.
 */
CppHibernateQuery & CppHibernateQuery::setMaxResults(jint numberOfResults) {
	if (numberOfResults < 1) {
		std::string errorMessage(
				"number of results for setMaxResults must be >= 1, but ");
		std::stringstream ss;
		ss << numberOfResults;
		errorMessage += ss.str();
		errorMessage += " specified.";
		throw CppHibernateException(errorMessage.c_str());
	}
	jmethodID setMaxResultsId = this->env->GetMethodID(this->objClass,
			CppHibernateQuery::ORG_HIBERNATE_QUERY_SETMAXRESULTS_NAME,
			CppHibernateQuery::ORG_HIBERNATE_QUERY_SETMAXRESULTS_SIGNATURE);
	if (setMaxResultsId == NULL) {
		this->throwException();
	}

	jobject query = this->env->CallObjectMethod(this->obj, setMaxResultsId,
			numberOfResults);
	this->checkAndThrow();
	this->setObj(this->env->NewGlobalRef(query));
	return *(this);
}

/**
 * Sets parameter on this query.
 * @param CppHibernateJStringObject *parameterName Name to be substituted by the specified object. The specified object is deleted
 * during the method call.
 * @param CppHibernateJObject *object Object to be actually used in the query. The specified object is deleted
 * during the method call.
 * @return CppHibernateQuery & Returns this object.
 * @throw Throws exceptions when JNI encounters exceptions and invalid parameters such as NULL are specified.
 */
CppHibernateQuery & CppHibernateQuery::setParameter(
		CppHibernateJStringObject * parameterName,
		CppHibernateJObject * object) {

	if (parameterName == NULL || object == NULL) {
		throw CppHibernateException(
				"NULL can not be accepted. Please specify the correct parameters for CppHibernateQuery::setParameter().");
	}

	jmethodID setParameterId = this->env->GetMethodID(this->objClass,
			CppHibernateQuery::ORG_HIBERNATE_QUERY_SETPARAMETER_NAME,
			CppHibernateQuery::ORG_HIBERNATE_QUERY_SETPARAMETER_SIGNATURE);
	if (setParameterId == NULL) {
		this->throwException();
	}

	jobject query = this->env->CallObjectMethod(this->obj, setParameterId,
			parameterName->getObj(), object->getObj());
	delete parameterName;
	parameterName = NULL;
	delete object;
	object = NULL;
	this->checkAndThrow();
	this->setObj(this->env->NewGlobalRef(query));
	return *(this);
}

CppHibernateQuery & CppHibernateQuery::setCacheable(bool cacheable) {

	jmethodID setCacheableId = this->env->GetMethodID(this->objClass,
			CppHibernateQuery::ORG_HIBERNATE_QUERY_SETCACHEABLE_NAME,
			CppHibernateQuery::ORG_HIBERNATE_QUERY_SETCACHEABLE_SIGNATURE);
	if (setCacheableId == NULL) {
		this->throwException();
	}

	jobject query = this->env->CallObjectMethod(this->obj, setCacheableId,
			cacheable);
	this->checkAndThrow();
	this->setObj(this->env->NewGlobalRef(query));
	return *(this);
}

CppHibernateQuery & CppHibernateQuery::setCacheRegion(const char *regionName) {

	jmethodID setCacheRegionId = this->env->GetMethodID(this->objClass,
			CppHibernateQuery::ORG_HIBERNATE_QUERY_SETCACHEREGION_NAME,
			CppHibernateQuery::ORG_HIBERNATE_QUERY_SETCACHEREGION_SIGNATURE);
	if (setCacheRegionId == NULL) {
		this->throwException();
	}

	jobject query = this->env->CallObjectMethod(this->obj, setCacheRegionId,
			this->env->NewStringUTF(regionName));
	this->checkAndThrow();
	this->setObj(this->env->NewGlobalRef(query));
	return *(this);
}

CppHibernateQuery::~CppHibernateQuery() {

}

}

/* namespace cppHibernate */
