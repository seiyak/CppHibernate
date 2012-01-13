/*
 * CppHibernateRestrictions.cpp
 *
 *  Created on: Dec 6, 2011
 *      Author: seiyak
 */

#include <cstring>
#include "CppHibernateRestrictions.h"

namespace cppHibernate {

const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_EQ_NAME =
		"eq";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_EQ_SIGNATURE =
		"(Ljava/lang/String;Ljava/lang/Object;)Lorg/hibernate/criterion/SimpleExpression;";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_GE_NAME =
		"ge";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_GE_SIGNATURE =
		"(Ljava/lang/String;Ljava/lang/Object;)Lorg/hibernate/criterion/SimpleExpression;";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_GT_NAME =
		"gt";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_GT_SIGNATURE =
		"(Ljava/lang/String;Ljava/lang/Object;)Lorg/hibernate/criterion/SimpleExpression;";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_LE_NAME =
		"le";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_LE_SIGNATURE =
		"(Ljava/lang/String;Ljava/lang/Object;)Lorg/hibernate/criterion/SimpleExpression;";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_LT_NAME =
		"lt";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_LT_SIGNATURE =
		"(Ljava/lang/String;Ljava/lang/Object;)Lorg/hibernate/criterion/SimpleExpression;";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_NE_NAME =
		"ne";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_NE_SIGNATURE =
		"(Ljava/lang/String;Ljava/lang/Object;)Lorg/hibernate/criterion/SimpleExpression;";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_ILIKE_NAME =
		"ilike";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_ILIKE_SIGNATURE =
		"(Ljava/lang/String;Ljava/lang/String;Lorg/hibernate/criterion/MatchMode;)Lorg/hibernate/criterion/Criterion;";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_LIKE_NAME =
		"like";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_LIKE_SIGNATURE =
		"(Ljava/lang/String;Ljava/lang/String;Lorg/hibernate/criterion/MatchMode;)Lorg/hibernate/criterion/SimpleExpression;";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_IDEQ_NAME =
		"idEq";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_IDEQ_SIGNATURE =
		"(Ljava/lang/Object;)Lorg/hibernate/criterion/Criterion;";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_BETWEEN_NAME =
		"between";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_BETWEEN_SIGNATURE =
		"(Ljava/lang/String;Ljava/lang/Object;Ljava/lang/Object;)Lorg/hibernate/criterion/Criterion;";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_IN_NAME =
		"in";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_IN_SIGNATURE =
		"(Ljava/lang/String;[Ljava/lang/Object;)Lorg/hibernate/criterion/Criterion;";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_ISNOTNULL_NAME =
		"isNotNull";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_ISNOTNULL_SIGNATURE =
		"(Ljava/lang/String;)Lorg/hibernate/criterion/Criterion;";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_ISNULL_NAME =
		"isNull";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_ISNULL_SIGNATURE =
		"(Ljava/lang/String;)Lorg/hibernate/criterion/Criterion;";

const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_MATCHMODE_SIGNATURE =
		"Lorg/hibernate/criterion/MatchMode;";
const char *CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_MATCHMODE =
		"org.hibernate.criterion.MatchMode";
const char *CppHibernateRestrictions::MATCHMODE_ANYWHERE = "ANYWHERE";
const char *CppHibernateRestrictions::MATCHMODE_END = "END";
const char *CppHibernateRestrictions::MATCHMODE_EXACT = "EXACT";
const char *CppHibernateRestrictions::MATCHMODE_START = "START";

CppHibernateRestrictions::CppHibernateRestrictions(JNIEnv *env, jobject obj,
		jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateCommons(env, obj, objClass, classLoader) {
}

/**
 * Applies eq restriction on the specified property.
 * @param const char *propertyName Property used to check the eq restriction.
 * @param CppHibernateJObject *& obj Object used to check against the property.
 * @return CppHibernateRestrictions Returns new CppHibernateRestrictions object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateRestrictions CppHibernateRestrictions::eq(const char *propertyName,
		CppHibernateJObject *& object) {

	jmethodID eqId =
			this->env->GetStaticMethodID(
					this->objClass,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_EQ_NAME,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_EQ_SIGNATURE);
	if (eqId == NULL) {
		this->throwException();
	}

	return this->callForStringObjectParams(
			this->env->NewGlobalRef(
					(jobject) (((((((((((((((eqId)))))))))))))))), propertyName,
			object);
}

/**
 * Applies ge restriction on the specified property.
 * @param const char *propertyName Property used to check the ge restriction.
 * @param CppHibernateJObject *& obj Object used to check against the property.
 * @return CppHibernateRestrictions Returns new CppHibernateRestrictions object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateRestrictions CppHibernateRestrictions::ge(const char *propertyName,
		CppHibernateJObject *& object) {
	jmethodID geId =
			this->env->GetStaticMethodID(
					this->objClass,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_GE_NAME,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_GE_SIGNATURE);
	if (geId == NULL) {
		this->throwException();
	}

	return this->callForStringObjectParams(
			this->env->NewGlobalRef(
					(jobject) (((((((((((((((geId)))))))))))))))), propertyName,
			object);
}

/**
 * Applies gt restriction on the specified property.
 * @param const char *propertyName Property used to check the gt restriction.
 * @param CppHibernateJObject *& obj Object used to check against the property.
 * @return CppHibernateRestrictions Returns new CppHibernateRestrictions object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateRestrictions CppHibernateRestrictions::gt(const char *propertyName,
		CppHibernateJObject *& object) {
	jmethodID gtId =
			this->env->GetStaticMethodID(
					this->objClass,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_GT_NAME,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_GT_SIGNATURE);
	if (gtId == NULL) {
		this->throwException();
	}

	return this->callForStringObjectParams(
			this->env->NewGlobalRef((jobject) ((((((((((((((gtId))))))))))))))),
			propertyName, object);
}

/**
 * Applies le restriction on the specified property.
 * @param const char *propertyName Property used to check the le restriction.
 * @param CppHibernateJObject *& obj Object used to check against the property.
 * @return CppHibernateRestrictions Returns new CppHibernateRestrictions object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateRestrictions CppHibernateRestrictions::le(const char *propertyName,
		CppHibernateJObject *& object) {
	jmethodID leId =
			this->env->GetStaticMethodID(
					this->objClass,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_LE_NAME,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_LE_SIGNATURE);
	if (leId == NULL) {
		this->throwException();
	}

	return this->callForStringObjectParams(
			this->env->NewGlobalRef((jobject) ((((leId))))), propertyName,
			object);
}

/**
 * Applies lt restriction on the specified property.
 * @param const char *propertyName Property used to check the lt restriction.
 * @param CppHibernateJObject *& obj Object used to check against the property.
 * @return CppHibernateRestrictions Returns new CppHibernateRestrictions object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateRestrictions CppHibernateRestrictions::lt(const char *propertyName,
		CppHibernateJObject *& object) {
	jmethodID ltId =
			this->env->GetStaticMethodID(
					this->objClass,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_LT_NAME,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_LT_SIGNATURE);
	if (ltId == NULL) {
		this->throwException();
	}

	return this->callForStringObjectParams(
			this->env->NewGlobalRef((jobject) (ltId)), propertyName, object);
}

/**
 * Applies ne restriction on the specified property.
 * @param const char *propertyName Property used to check the ne restriction.
 * @param CppHibernateJObject *& obj Object used to check against the property.
 * @return CppHibernateRestrictions Returns new CppHibernateRestrictions object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateRestrictions CppHibernateRestrictions::ne(const char *propertyName,
		CppHibernateJObject *& object) {

	jmethodID neId =
			this->env->GetStaticMethodID(
					this->objClass,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_NE_NAME,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_NE_SIGNATURE);
	if (neId == NULL) {
		this->throwException();
	}

	return this->callForStringObjectParams(
			this->env->NewGlobalRef((jobject) neId), propertyName, object);
}

/**
 * Calls methods on org.hibernate.criterion.Restrictions with two parameters, java.lang.String and java.lang.Object.
 * @param jobject methodId Method id to be invoked,
 * @param const char * propertyName Property to be constrained.
 * @param CppHibernateJObject *& object Use to be against the specified property.
 * @return CppHibernateRestrictions Returns new CppHibernateRestrictions object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateRestrictions CppHibernateRestrictions::callForStringObjectParams(
		jobject methodId, const char *propertyName,
		CppHibernateJObject *& object) {
	jobject restrictions = this->env->CallStaticObjectMethod(this->objClass,
			(jmethodID) (((((((((((((((methodId))))))))))))))),
			this->env->NewStringUTF(propertyName), object->getObj());
	this->env->DeleteGlobalRef(methodId);
	this->deleteObj(object);
	this->checkAndThrow();
	return CppHibernateRestrictions(
			this->env,
			this->env->NewGlobalRef(restrictions),
			(jclass) ((((((((((((((((((this->env->NewGlobalRef(
					this->env->GetObjectClass(restrictions)))))))))))))))))))),
			this->classLoader);
}

/**
 * Applies idEq restriction.
 * @param CppHibernateJObject *& object Object to be used against the id. The specified object is deleted during the method call.
 * @return CppHibernateRestrictions Returns new CppHibernateRestrictions object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateRestrictions CppHibernateRestrictions::idEq(
		CppHibernateJObject *& object) {
	jmethodID idEqId =
			this->env->GetStaticMethodID(
					this->objClass,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_IDEQ_NAME,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_IDEQ_SIGNATURE);
	if (idEqId == NULL) {
		this->throwException();
	}
	jobject restrictions = this->env->CallStaticObjectMethod(this->objClass,
			idEqId, object->getObj());
	delete object;
	object = NULL;
	this->checkAndThrow();
	return CppHibernateRestrictions(
			this->env,
			this->env->NewGlobalRef(restrictions),
			(jclass) (((((((((((((this->env->NewGlobalRef(
					this->env->GetObjectClass(restrictions))))))))))))))),
			this->classLoader);
}

/**
 * Applies between restriction on the specified property.
 * @param const char * Property to be constrained.
 * @param CppHibernateJObject *& lo Lower part of the constrain. The specified object for the lower part of the constrain
 * is deleted during the method call.
 * @param CppHibernateJObject *& hi Higher part of the constrain. The specified object for the higher part of the constarin
 * is deleted during the method call.
 * @return CppHibernateRestrictions Returns new CppHibernateRestrictions object.
 */
CppHibernateRestrictions CppHibernateRestrictions::between(
		const char *propertyName, CppHibernateJObject *& lo,
		CppHibernateJObject *& hi) {
	jmethodID betweenId =
			this->env->GetStaticMethodID(
					this->objClass,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_BETWEEN_NAME,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_BETWEEN_SIGNATURE);
	if (betweenId == NULL) {
		this->throwException();
	}

	jobject restrictions = this->env->CallStaticObjectMethod(this->objClass,
			betweenId, this->env->NewStringUTF(propertyName), lo->getObj(),
			hi->getObj());
	this->deleteObj(lo);
	this->deleteObj(hi);
	this->checkAndThrow();
	return CppHibernateRestrictions(
			this->env,
			this->env->NewGlobalRef(restrictions),
			(jclass) ((((((((((((((((this->env->NewGlobalRef(
					this->env->GetObjectClass(restrictions)))))))))))))))))),
			this->classLoader);
}

/**
 * Applies in constrain on the specified property.
 * @param const char *propertyName Property to be constrained.
 * @param std::deque<CppHibernateJObject *>& Candidates to be against the specified property. The specified std::deque is cleared during the method call.
 * @return CppHibernateRestrictions Returns new CppHibernateRestrictions object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateRestrictions CppHibernateRestrictions::in(const char *propertyName,
		std::deque<CppHibernateJObject*> & objects) {
	jmethodID inId =
			this->env->GetStaticMethodID(
					this->objClass,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_IN_NAME,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_IN_SIGNATURE);
	if (inId == NULL) {
		this->throwException();
	}

	jobject objArray = this->convertFrom(objects);
	jobject restrictions = this->env->CallStaticObjectMethod(this->objClass,
			inId, this->env->NewStringUTF(propertyName), objArray);
	this->env->DeleteGlobalRef(objArray);
	this->checkAndThrow();
	return CppHibernateRestrictions(
			this->env,
			this->env->NewGlobalRef(restrictions),
			(jclass) ((((((((this->env->NewGlobalRef(
					this->env->GetObjectClass(restrictions)))))))))),
			this->classLoader);
}

/**
 * Converts std::deque to Java array.
 * @param std::deque<CppHibernateJObject *>& objects Stores the constraints for CppHibernateRestrictions::in() method. The specified deque is cleared
 * during the method call.
 * @return jobject Returns the Java array. The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
jobject CppHibernateRestrictions::convertFrom(
		std::deque<CppHibernateJObject*> & objects) {
	int size = objects.size();
	jclass objectClass = this->env->FindClass("java/lang/Object");
	jobjectArray array = this->env->NewObjectArray(objects.size(), objectClass,
			NULL);
	this->checkAndThrow();
	int i;
	for (i = 0; i < size; i++) {
		this->env->SetObjectArrayElement(array, i, objects[i]->getObj());
		this->checkAndThrow();
	}
	objects.clear();
	return this->env->NewGlobalRef(array);
}

/**
 * Applies case insensitive like constrain on the specified property.
 * @param const char *propertyName Property to be constrained.
 * @param CppHibernateJStringObject *& object Object used to be against the specified property. The specified object is deleted during the method call.
 * @param const char *matchMode Match mode. One of 'ANYWHERE','END','EXACT' and 'START'. The default match mode is 'START'.
 * @return CppHibernateRestrictions Returns new CppHibernateRestrictions object.
 * @throw Throws exceptions when JNI encounters exceptions and invalid matchMode is specified.
 */
CppHibernateRestrictions CppHibernateRestrictions::ilike(
		const char *propertyName, CppHibernateJStringObject *& object,
		const char *matchMode) {
	jmethodID ilikeId =
			this->env->GetStaticMethodID(
					this->objClass,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_ILIKE_NAME,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_ILIKE_SIGNATURE);
	if (ilikeId == NULL) {
		this->throwException();
	}
	return this->callForLike(this->env->NewGlobalRef((jobject) ((ilikeId))),
			propertyName, object, matchMode);
}

/**
 * Applies case sensitive like constrain on the specified property.
 * @param const char *propertyName Property to be constrained.
 * @param CppHibernateJStringObject *& object Object used to be against the specified property. The specified object is deleted during the method call.
 * @param const char *matchMode Match mode. One of 'ANYWHERE','END','EXACT' and 'START'. The default match mode is 'START'.
 * @return CppHibernateRestrictions Returns new CppHibernateRestrictions object.
 * @throw Throws exceptions when JNI encounters exceptions and invalid matchMode is specified.
 */
CppHibernateRestrictions CppHibernateRestrictions::like(
		const char *propertyName, CppHibernateJStringObject *& object,
		const char *matchMode) {
	jmethodID likeId =
			this->env->GetStaticMethodID(
					this->objClass,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_LIKE_NAME,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_LIKE_SIGNATURE);
	if (likeId == NULL) {
		this->throwException();
	}
	return this->callForLike(this->env->NewGlobalRef((jobject) ((likeId))),
			propertyName, object, matchMode);
}

CppHibernateRestrictions CppHibernateRestrictions::callForLike(jobject methodId,
		const char *propertyName, CppHibernateJStringObject *& object,
		const char *matchMode) {
	jobject mMode = NULL;
	try {
		mMode = this->getMatchMode(matchMode);
	} catch (CppHibernateException& e) {
		delete object;
		object = NULL;
		throw e;
	}
	jobject restrictions = this->env->CallStaticObjectMethod(this->objClass,
			(jmethodID) ((methodId)), this->env->NewStringUTF(propertyName),
			object->getObj(), mMode);
	this->env->DeleteGlobalRef(methodId);
	this->env->DeleteGlobalRef(mMode);
	delete object;
	object = NULL;
	this->checkAndThrow();
	return CppHibernateRestrictions(
			this->env,
			this->env->NewGlobalRef(restrictions),
			(jclass) ((((((((((this->env->NewGlobalRef(
					this->env->GetObjectClass(restrictions)))))))))))),
			this->classLoader);
}

jobject CppHibernateRestrictions::getMatchMode(const char *matchMode) {
	if (std::strncmp(CppHibernateRestrictions::MATCHMODE_ANYWHERE, matchMode,
			std::strlen(CppHibernateRestrictions::MATCHMODE_ANYWHERE)) == 0) {
		return this->createMatchMode(
				CppHibernateRestrictions::MATCHMODE_ANYWHERE);
	} else if (std::strncmp(CppHibernateRestrictions::MATCHMODE_END, matchMode,
			std::strlen(CppHibernateRestrictions::MATCHMODE_END)) == 0) {
		return this->createMatchMode(CppHibernateRestrictions::MATCHMODE_END);
	} else if (std::strncmp(CppHibernateRestrictions::MATCHMODE_EXACT,
			matchMode, std::strlen(CppHibernateRestrictions::MATCHMODE_EXACT))
			== 0) {
		return this->createMatchMode(CppHibernateRestrictions::MATCHMODE_EXACT);
	} else if (std::strncmp(CppHibernateRestrictions::MATCHMODE_START,
			matchMode, std::strlen(CppHibernateRestrictions::MATCHMODE_START))
			== 0) {
		return this->createMatchMode(CppHibernateRestrictions::MATCHMODE_START);
	}

	std::string errorMessage("Invalid match mode is specified, ");
	errorMessage += matchMode;
	throw CppHibernateException(errorMessage.c_str());
}

/**
 * Gets org.hibernate.criterion.MatchMode field.
 * @return jobject Returns the field. The returned object must be deleted whent he job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
jobject CppHibernateRestrictions::createMatchMode(const char *matchMode) {
	jobject matchModeObj = this->classLoader->loadClass(
			CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_MATCHMODE);
	this->checkAndThrow();
	jfieldID fieldId =
			this->env->GetStaticFieldID(
					(jclass) ((((((((((matchModeObj)))))))))),
					matchMode,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_MATCHMODE_SIGNATURE);
	if (fieldId == NULL) {
		this->throwException();
	}
	jobject fieldObj = this->env->GetStaticObjectField(
			(jclass) ((((((((((matchModeObj)))))))))), fieldId);
	this->env->DeleteGlobalRef(matchModeObj);
	this->checkAndThrow();
	return this->env->NewGlobalRef(fieldObj);
}

/**
 * Applies is not null constrain on the specified property.
 * @param const char *propertyName Property to be constrained.
 * @return CppHibernateRestrictions Returns new CppHibernateRestrictions object.
 */
CppHibernateRestrictions CppHibernateRestrictions::isNotNULL(
		const char *propertyName) {
	jmethodID isNotNullId =
			this->env->GetStaticMethodID(
					this->objClass,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_ISNOTNULL_NAME,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_ISNOTNULL_SIGNATURE);
	if (isNotNullId == NULL) {
		this->throwException();
	}

	return this->callForNull(
			this->env->NewGlobalRef((jobject) (((((isNotNullId)))))),
			propertyName);
}

/**
 * Applies is null constrain on the specified property.
 * @param const char *propertyName Property to be constrained.
 * @return CppHibernateRestrictions Returns new CppHibernateRestrictions object.
 */
CppHibernateRestrictions CppHibernateRestrictions::isNULL(
		const char *propertyName) {
	jmethodID isNullId =
			this->env->GetStaticMethodID(
					this->objClass,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_ISNULL_NAME,
					CppHibernateRestrictions::ORG_HIBERNATE_CRITERION_RESTRICTIONS_ISNULL_SIGNATURE);
	if (isNullId == NULL) {
		this->throwException();
	}

	return this->callForNull(
			this->env->NewGlobalRef((jobject) (((((isNullId)))))), propertyName);
}

CppHibernateRestrictions CppHibernateRestrictions::callForNull(jobject methodId,
		const char *propertyName) {
	jobject restrictions = this->env->CallStaticObjectMethod(this->objClass,
			(jmethodID) (((((methodId))))),
			this->env->NewStringUTF(propertyName));
	this->env->DeleteGlobalRef(methodId);
	this->checkAndThrow();
	return CppHibernateRestrictions(
			this->env,
			this->env->NewGlobalRef(restrictions),
			(jclass) (((((((this->env->NewGlobalRef(
					this->env->GetObjectClass(restrictions))))))))),
			this->classLoader);
}

/**
 * Calls destructor on the specified object.
 * @param CppHibernateJObject *& object Object to be deleted.
 */
void CppHibernateRestrictions::deleteObj(CppHibernateJObject *& object) {
	delete object;
	object = NULL;
}

CppHibernateRestrictions::~CppHibernateRestrictions() {

}

} /* namespace cppHibernate */
