/*
 * CppHibernateCriteria.cpp
 *
 *  Created on: Dec 5, 2011
 *      Author: seiyak
 */

#include <cstring>
#include "CppHibernateCriteria.h"
#include "CppHibernateOrder.h"

namespace cppHibernate {

const char *CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_LIST_NAME = "list";
const char *CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_LIST_SIGNATURE =
		"()Ljava/util/List;";
const char *CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_CREATEALIAS_NAME =
		"createCriteria";
const char *CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_CREATEALIAS_SIGNATURE =
		"(Ljava/lang/String;Ljava/lang/String;)Lorg/hibernate/Criteria";
const char *CppHibernateCriteria::ORG_HIBERNATE_CRITERION_ORDER =
		"org.hibernate.criterion.Order";
const char *CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_ADDORDER_NAME =
		"addOrder";
const char *CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_ADDORDER_SIGNATURE =
		"(Lorg/hibernate/criterion/Order;)Lorg/hibernate/Criteria;";
const char *CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_ADD_NAME = "add";
const char *CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_ADD_SIGNATURE =
		"(Lorg/hibernate/criterion/Criterion;)Lorg/hibernate/Criteria;";
const char *CppHibernateCriteria::ORG_HIBERNATE_CRITERION_RESTRICTIONS =
		"org.hibernate.criterion.Restrictions";
const char *CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_SETCACHEABLE_NAME =
		"setCacheable";
const char *CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_SETCACHEABLE_SIGNATURE =
		"(Z)Lorg/hibernate/Criteria;";
const char *CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_SETCACHEREGION_NAME =
		"setCacheRegion";
const char *CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_SETCACHEREGION_SIGNATURE =
		"(Ljava/lang/String;)Lorg/hibernate/Criteria;";

CppHibernateCriteria::CppHibernateCriteria(JNIEnv *env, jobject obj,
		jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateCommons(env, obj, objClass, classLoader) {

}

/**
 * Joins the specified object path as the specified alias. after calling this method, the alias can be used on queries.
 * @param const char * objPath Object path to be aliased.
 * @param const char *alias Alias to be used to express the path.
 * @return CppHibernateCriteria& Returns this criteria object.
 * @throw Throws exceptions when JNI encounters exceptions and the parameters are invalid.
 */
CppHibernateCriteria & CppHibernateCriteria::createAlias(const char *objPath,
		const char *alias) {
	//// TODO need to test this method when getting a little more practical sample java class.
	this->checkAliasParams(objPath, alias);

	jmethodID createAliasId = this->env->GetMethodID(this->objClass,
			CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_CREATEALIAS_NAME,
			CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_CREATEALIAS_SIGNATURE);
	if (createAliasId == NULL) {
		this->throwException();
	}

	jobject criteria = this->env->CallObjectMethod(this->obj, createAliasId,
			this->env->NewStringUTF(objPath), this->env->NewStringUTF(alias));
	this->checkAndThrow();

	this->setObj(this->env->NewGlobalRef(criteria));
	return *(this);
}

/**
 * Checks if the specified parameters for CppHibernateCriteria::createAlias() are valid or not. If so ,does nothing. If not,
 * throws an exception.
 */
void CppHibernateCriteria::checkAliasParams(const char *objPath,
		const char *alias) {

	if (std::strlen(objPath) == 0 || std::strlen(alias) == 0) {
		std::string errorMessage(
				"the parameters are invalid. Please specify the correct parameters, objPath: ");
		errorMessage += objPath;
		errorMessage += ", alias: ";
		errorMessage += alias;
		errorMessage += ".";
		throw CppHibernateException(errorMessage.c_str());
	}
}

/**
 * Gets the query result on this org.hibernate.Criteria object.
 * @return CppHibernateJCollectionObject * Object storing the results as java.lang.List object. The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateJCollectionObject *CppHibernateCriteria::list() {

	jmethodID listId = this->env->GetMethodID(this->objClass,
			CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_LIST_NAME,
			CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_LIST_SIGNATURE);
	if (listId == NULL) {
		this->throwException();
	}

	jobject res = this->env->CallObjectMethod(this->obj, listId);
	this->checkAndThrow();

	return new CppHibernateJCollectionObject(
			this->env,
			this->env->NewGlobalRef(res),
			(jclass) (((((((((((((((((((((((((((this->env->NewGlobalRef(
					this->env->GetObjectClass(res))))))))))))))))))))))))))))),
			this->classLoader);
}

/**
 * Adds ascending order on this org.hibernate.Criteria object based on the specified property.
 * @param const char *propertyName Property to be used for ascending order.
 * @param bool ignoreCase True if ignores the case, false otherwise. The default value is false.
 * @return CppHibernateCriteria & Returns this org.hibernate.Criteria object,
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateCriteria & CppHibernateCriteria::addOrderAsc(
		const char *propertyName, bool ignoreCase) {
	jobject orderObj = this->classLoader->loadClass(
			CppHibernateCriteria::ORG_HIBERNATE_CRITERION_ORDER);
	this->checkAndThrow();

	jobject addOrderId = this->findAddOrderId();
	jobject criteria = NULL;
	if (ignoreCase) {
		criteria = this->orderAsc(orderObj,
				(jmethodID) ((((((((((((((((((((addOrderId)))))))))))))))))))),
				propertyName, true);
	} else {
		criteria = this->orderAsc(orderObj,
				(jmethodID) ((((((((((((((((((((addOrderId)))))))))))))))))))),
				propertyName, false);
	}
	this->env->DeleteGlobalRef(addOrderId);
	this->env->DeleteGlobalRef(orderObj);
	this->setObj(criteria);
	this->checkAndThrow();
	return *(this);
}

/**
 * Applies ascending order on the specified org.hibernate.criterion.Order object.
 * @param jobject orderObj org.hibernate.criterion.Order object.
 * @param jmethodID addOrderId Method id for org.hiberante.criteria.addOrder() method.
 * @param const char *propertyName Property to be used for ascending order.
 * @param bool ignoreCase True if ignores the case, false otherwise.
 * @return jobject Returns org.hibernate.criterion.Order object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
jobject CppHibernateCriteria::orderAsc(jobject orderObj, jmethodID addOrderId,
		const char *propertyName, bool ignoreCase) {
	jobject criteria = NULL;
	if (ignoreCase) {
		//// TODO test this execution path
		this->env->CallObjectMethod(
				this->obj,
				(jmethodID) (((((((((((((((((((((addOrderId))))))))))))))))))))),
				CppHibernateOrder(
						this->env,
						orderObj,
						(jclass) (((((((((((((((((((((((orderObj))))))))))))))))))))))),
						this->classLoader).asc(propertyName).ignoreCase().getObj());
		this->checkAndThrow();

	} else {

		criteria =
				this->env->CallObjectMethod(
						this->obj,
						(jmethodID) (((((((((((((((((((((addOrderId))))))))))))))))))))),
						CppHibernateOrder(
								this->env,
								orderObj,
								(jclass) (((((((((((((((((((((((orderObj))))))))))))))))))))))),
								this->classLoader).asc(propertyName).getObj());
		this->checkAndThrow();
	}
	return this->env->NewGlobalRef(criteria);
}

/**
 * Adds descending order on this org.hibernate.Criteria object based on the specified property.
 * @param const char *propertyName Property to be used for descending order.
 * @param bool ignoreCase True if ignores the case, false otherwise. The default value is false.
 * @return CppHibernateCriteria & Returns this org.hibernate.Criteria object,
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateCriteria & CppHibernateCriteria::addOrderDesc(
		const char *propertyName, bool ignoreCase) {
	jobject orderObj = this->classLoader->loadClass(
			CppHibernateCriteria::ORG_HIBERNATE_CRITERION_ORDER);
	this->checkAndThrow();

	jobject addOrderId = this->findAddOrderId();
	jobject criteria = NULL;
	if (ignoreCase) {
		criteria = this->orderDesc(orderObj,
				(jmethodID) ((((((((((((((((((((addOrderId)))))))))))))))))))),
				propertyName, true);
	} else {
		criteria = this->orderDesc(orderObj,
				(jmethodID) ((((((((((((((((((((addOrderId)))))))))))))))))))),
				propertyName, false);
	}
	this->env->DeleteGlobalRef(addOrderId);
	this->env->DeleteGlobalRef(orderObj);
	this->setObj(criteria);
	this->checkAndThrow();
	return *(this);
}

/**
 * Applies descending order on the specified org.hibernate.criterion.Order object.
 * @param jobject orderObj org.hibernate.criterion.Order object.
 * @param jmethodID addOrderId Method id for org.hiberante.criteria.addOrder() method.
 * @param const char *propertyName Property to be used for descending order.
 * @param bool ignoreCase True if ignores the case, false otherwise.
 * @return jobject Returns org.hibernate.criterion.Order object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
jobject CppHibernateCriteria::orderDesc(jobject orderObj, jmethodID addOrderId,
		const char *propertyName, bool ignoreCase) {
	jobject criteria = NULL;
	if (ignoreCase) {
		//// TODO test this execution path
		this->env->CallObjectMethod(
				this->obj,
				(jmethodID) (((((((((((((((((((((addOrderId))))))))))))))))))))),
				CppHibernateOrder(
						this->env,
						orderObj,
						(jclass) (((((((((((((((((((((((orderObj))))))))))))))))))))))),
						this->classLoader).desc(propertyName).ignoreCase().getObj());
		this->checkAndThrow();

	} else {

		criteria =
				this->env->CallObjectMethod(
						this->obj,
						(jmethodID) (((((((((((((((((((((addOrderId))))))))))))))))))))),
						CppHibernateOrder(
								this->env,
								orderObj,
								(jclass) (((((((((((((((((((((((orderObj))))))))))))))))))))))),
								this->classLoader).desc(propertyName).getObj());
		this->checkAndThrow();
	}
	return this->env->NewGlobalRef(criteria);
}

/**
 * Finds org.hibernate.Criteri.addOrder method on this class.
 * @return jobject Returns the method id as jobject. The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
jobject CppHibernateCriteria::findAddOrderId() {
	jmethodID addOrderId = this->env->GetMethodID(this->objClass,
			CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_ADDORDER_NAME,
			CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_ADDORDER_SIGNATURE);
	if (addOrderId == NULL) {
		this->throwException();
	}

	return this->env->NewGlobalRef(
			(jobject) (((((((((((((((((((((addOrderId))))))))))))))))))))));
}

/**
 * Adds eq restriction on this object.
 * @param const char * propertyName Property to be used for eq restriction.
 * @param CppHibernateJObject *object Object examined to be equal to the value of the specified property. The specified object
 * is deleted during the method call.
 * @return CppHibernateCriteria & Returns this object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateCriteria & CppHibernateCriteria::addEq(const char *propertyName,
		CppHibernateJObject *object) {
	jobject restrictionsObj = this->loadRestrictionsClass();
	CppHibernateRestrictions restrictions = CppHibernateRestrictions(this->env,
			restrictionsObj,
			(jclass) ((((((((((((((((restrictionsObj)))))))))))))))),
			this->classLoader).eq(propertyName, object);
	return this->add(restrictionsObj, restrictions);
}

/**
 * Adds ge restriction on this object.
 * @param const char * propertyName Property to be used for ge restriction.
 * @param CppHibernateJObject *object Object examined to be greater than or equal to the value of the specified property. The specified object
 * is deleted during the method call.
 * @return CppHibernateCriteria & Returns this object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateCriteria & CppHibernateCriteria::addGe(const char *propertyName,
		CppHibernateJObject *object) {
	jobject restrictionsObj = this->loadRestrictionsClass();
	CppHibernateRestrictions restrictions = CppHibernateRestrictions(this->env,
			restrictionsObj,
			(jclass) ((((((((((((((restrictionsObj)))))))))))))),
			this->classLoader).ge(propertyName, object);
	return this->add(restrictionsObj, restrictions);
}

/**
 * Adds gt restriction on this object.
 * @param const char * propertyName Property to be used for gt restriction.
 * @param CppHibernateJObject *object Object examined to be greater than the value of the specified property. The specified object
 * is deleted during the method call.
 * @return CppHibernateCriteria & Returns this object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateCriteria & CppHibernateCriteria::addGt(const char *propertyName,
		CppHibernateJObject *object) {
	jobject restrictionsObj = this->loadRestrictionsClass();
	CppHibernateRestrictions restrictions = CppHibernateRestrictions(this->env,
			restrictionsObj, (jclass) (((((((((((restrictionsObj))))))))))),
			this->classLoader).gt(propertyName, object);
	return this->add(restrictionsObj, restrictions);
}

/**
 * Adds le restriction on this object.
 * @param const char * propertyName Property to be used for le restriction.
 * @param CppHibernateJObject *object Object examined to be less than or equal to the value of the specified property. The specified object
 * is deleted during the method call.
 * @return CppHibernateCriteria & Returns this object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateCriteria & CppHibernateCriteria::addLe(const char *propertyName,
		CppHibernateJObject *object) {
	jobject restrictionsObj = this->loadRestrictionsClass();
	CppHibernateRestrictions restrictions = CppHibernateRestrictions(this->env,
			restrictionsObj, (jclass) (((((restrictionsObj))))),
			this->classLoader).le(propertyName, object);
	return this->add(restrictionsObj, restrictions);
}

/**
 * Adds lt restriction on this object.
 * @param const char * propertyName Property to be used for lt restriction.
 * @param CppHibernateJObject *object Object examined to be less than the value of the specified property. The specified object
 * is deleted during the method call.
 * @return CppHibernateCriteria & Returns this object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateCriteria & CppHibernateCriteria::addLt(const char *propertyName,
		CppHibernateJObject *object) {
	jobject restrictionsObj = this->loadRestrictionsClass();
	CppHibernateRestrictions restrictions =
			CppHibernateRestrictions(this->env, restrictionsObj,
					(jclass) (((restrictionsObj))), this->classLoader).lt(
					propertyName, object);
	return this->add(restrictionsObj, restrictions);
}

/**
 * Adds ne restriction on this object.
 * @param const char * propertyName Property to be used for lt restriction.
 * @param CppHibernateJObject *object Object examined to be not equal to the value of the specified property. The specified object
 * is deleted during the method call.
 * @return CppHibernateCriteria & Returns this object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateCriteria & CppHibernateCriteria::addNe(const char *propertyName,
		CppHibernateJObject *object) {
	jobject restrictionsObj = this->loadRestrictionsClass();
	CppHibernateRestrictions restrictions =
			CppHibernateRestrictions(this->env, restrictionsObj,
					(jclass) ((restrictionsObj)), this->classLoader).ne(
					propertyName, object);
	return this->add(restrictionsObj, restrictions);
}

/**
 * Adds ilike restriction on this object.
 * @param const char *propertyName Property to be constrained.
 * @param CppHibernateJStringObject *object Object used to be against the specified property. The specified object is deleted during the method call.
 * @param CppHibernateMatchMode matchMode Match mode. One of CppHibernateMatchMode::ANYWHERE,CppHibernateMatchMode::END,CppHibernateMatchMode::EXACT
 * and CppHibernateMatchModeSTART. The default match mode is CppHibernateMatchMode::START.
 * @return CppHibernateCriteria & Returns this object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateCriteria & CppHibernateCriteria::addIlike(const char *propertyName,
		CppHibernateJStringObject *object, CppHibernateMatchMode matchMode) {
	jobject restrictionsObj = this->loadRestrictionsClass();
	CppHibernateRestrictions restrictions = CppHibernateRestrictions(this->env,
			restrictionsObj, (jclass) (((((((((restrictionsObj))))))))),
			this->classLoader).ilike(propertyName, object,
			matchMode.getMatchMode());
	return this->add(restrictionsObj, restrictions);
}

/**
 * Adds like restriction on this object.
 * @param const char *propertyName Property to be constrained.
 * @param CppHibernateJStringObject *object Object used to be against the specified property. The specified object is deleted during the method call.
 * @param CppHibernateMatchMode matchMode Match mode. One of CppHibernateMatchMode::ANYWHERE,CppHibernateMatchMode::END,CppHibernateMatchMode::EXACT
 * and CppHibernateMatchModeSTART. The default match mode is CppHibernateMatchMode::START.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateCriteria & CppHibernateCriteria::addLike(const char *propertyName,
		CppHibernateJStringObject *object, CppHibernateMatchMode matchMode) {
	jobject restrictionsObj = this->loadRestrictionsClass();
	CppHibernateRestrictions restrictions = CppHibernateRestrictions(this->env,
			restrictionsObj, (jclass) ((((restrictionsObj)))),
			this->classLoader).like(propertyName, object,
			matchMode.getMatchMode());
	return this->add(restrictionsObj, restrictions);
}

/**
 * Adds between restriction on this object.
 * @param const char * propertyName Property to be used for between restriction.
 * @param CppHibernateJObject *lo The lower part of the constrain. The specified object
 * is deleted during the method call.
 * @param CppHibernateJObject *hi The higher part of the constrain. The specified object is deleted during the method call.
 * @return CppHibernateCriteria & Returns this object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateCriteria & CppHibernateCriteria::addBetween(
		const char *propertyName, CppHibernateJObject *lo,
		CppHibernateJObject *hi) {
	jobject restrictionsObj = this->loadRestrictionsClass();
	CppHibernateRestrictions restrictions = CppHibernateRestrictions(this->env,
			restrictionsObj, (jclass) (((((((((((((restrictionsObj))))))))))))),
			this->classLoader).between(propertyName, lo, hi);
	return this->add(restrictionsObj, restrictions);
}

/**
 * Adds idEq restriction on this object. Checks the id column to see if the id is equal to the specified object.
 * @param CppHibernateJObject *object Object to be used against the id. The specified object is deleted during the method call.
 * @return CppHibernateCriteria & Returns this object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateCriteria & CppHibernateCriteria::addIdEq(
		CppHibernateJObject *object) {
	jobject restrictionsObj = this->loadRestrictionsClass();
	CppHibernateRestrictions restrictions = CppHibernateRestrictions(this->env,
			restrictionsObj, (jclass) ((((((((((restrictionsObj)))))))))),
			this->classLoader).idEq(object);
	return this->add(restrictionsObj, restrictions);
}

/**
 * Adds in restriction on this object.
 * @param cosnt char *propertyName Property to be constrained.
 * @param std::deque<CppHibernateJObject*>& objects Stores the candidates to be against the specified property.
 * The specified std::deque is cleared during the method call.
 * @return CppHibernateCriteria & Returns this object.
 * @throw Throws exceptions when JNI encounters exceptions and the specified std::deque is empty.
 */
CppHibernateCriteria & CppHibernateCriteria::addIn(const char *propertyName,
		std::deque<CppHibernateJObject*> & objects) {
	if (objects.size() == 0) {
		throw CppHibernateException(
				"the specified objects is empty. 'in' constrain can not be used with an empty container.");
	}
	jobject restrictionsObj = this->loadRestrictionsClass();
	CppHibernateRestrictions restrictions = CppHibernateRestrictions(this->env,
			restrictionsObj, (jclass) ((((((((restrictionsObj)))))))),
			this->classLoader).in(propertyName, objects);
	return this->add(restrictionsObj, restrictions);
}

/**
 * Adds is not null restriction on this object.
 * @param const char *propertyName Property to be constrained.
 * @return CppHibernateCriteria & Returns this object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateCriteria & CppHibernateCriteria::addIsNotNULL(
		const char *propertyName) {
	jobject restrictionsObj = this->loadRestrictionsClass();
	CppHibernateRestrictions restrictions = CppHibernateRestrictions(this->env,
			restrictionsObj, (jclass) (((((((restrictionsObj))))))),
			this->classLoader).isNotNULL(propertyName);
	return this->add(restrictionsObj, restrictions);
}

/**
 * Adds is null restriction on this object.
 * @param const char *propertyName Property to be constrained.
 * @return CppHibernateCriteria & Returns this object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateCriteria & CppHibernateCriteria::addIsNULL(
		const char *propertyName) {
	jobject restrictionsObj = this->loadRestrictionsClass();
	CppHibernateRestrictions restrictions = CppHibernateRestrictions(this->env,
			restrictionsObj, (jclass) ((((((restrictionsObj)))))),
			this->classLoader).isNULL(propertyName);
	return this->add(restrictionsObj, restrictions);
}

CppHibernateCriteria & CppHibernateCriteria::add(jobject restrictionsObj,
		CppHibernateRestrictions & restrictions) {
	jobject addId = this->findAddId();
	jobject criteria = this->env->CallObjectMethod(this->obj,
			(jmethodID) ((((((((((((((((addId)))))))))))))))),
			restrictions.getObj());
	this->env->DeleteGlobalRef(restrictionsObj);
	this->env->DeleteGlobalRef(addId);
	this->checkAndThrow();

	this->setObj(this->env->NewGlobalRef(criteria));
	return *(this);
}

/**
 * Loads org.hibernate.criterion.Restrictions class.
 * @return jobject Returns the corresponding class as the result of loading the class. The returned object must be deleted
 * when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
jobject CppHibernateCriteria::loadRestrictionsClass() {
	jobject restrictionsObj = this->classLoader->loadClass(
			CppHibernateCriteria::ORG_HIBERNATE_CRITERION_RESTRICTIONS);
	if (restrictionsObj == NULL) {
		this->throwException();
	}

	return restrictionsObj;
}

/**
 * Finds org.hibernate.criteria.add() method id.
 * @return jobject Returns the method id. The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
jobject CppHibernateCriteria::findAddId() {
	jmethodID addId = this->env->GetMethodID(this->objClass,
			CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_ADD_NAME,
			CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_ADD_SIGNATURE);
	if (addId == NULL) {
		this->throwException();
	}

	return this->env->NewGlobalRef(
			(jobject) ((((((((((((((((addId)))))))))))))))));
}

/**
 * Sets if it's cacheable or not on this object.
 * @param bool true if sets to cacheable, false otherwise.
 * @return CppHibernateCriteria& Returns this object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateCriteria & CppHibernateCriteria::setCachable(bool cachable) {
	//// TODO test with cache settings.
	jmethodID setCachableId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_SETCACHEABLE_NAME,
					CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_SETCACHEABLE_SIGNATURE);
	if (setCachableId == NULL) {
		this->throwException();
	}
	jobject criteria = this->env->CallObjectMethod(this->obj, setCachableId,
			cachable);
	this->checkAndThrow();

	this->setObj(this->env->NewGlobalRef(criteria));
	return *(this);
}

/**
 * Sets cache region name for this criteria.
 * @param const char *regionName Region Name to be used to cache.
 * @return CppHibernateCriteria & Returns this object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateCriteria & CppHibernateCriteria::setCacheRegion(
		const char *regionName) {
	jmethodID setCacheRegionId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_SETCACHEREGION_NAME,
					CppHibernateCriteria::ORG_HIBERNATE_CRITERIA_SETCACHEREGION_SIGNATURE);
	if (setCacheRegionId == NULL) {
		this->throwException();
	}

	jobject criteria = this->env->CallObjectMethod(this->obj, setCacheRegionId,
			this->env->NewStringUTF(regionName));
	this->checkAndThrow();

	this->setObj(this->env->NewGlobalRef(criteria));

	return *(this);
}

CppHibernateCriteria::~CppHibernateCriteria() {

}

} /* namespace cppHibernate */
