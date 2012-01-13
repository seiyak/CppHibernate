/*
 * CppHibernateJMapObject.cpp
 *
 *  Created on: Jan 6, 2012
 *      Author: seiyak
 */

#include <iostream>
#include <cstring>
#include "CppHibernateJMapObject.h"

namespace cppHibernate {

const char *CppHibernateJMapObject::JAVA_UTIL_MAP_CONTAINSKEY_NAME =
		"containsKey";
const char *CppHibernateJMapObject::JAVA_UTIL_MAP_CONTAINSVALUE_NAME =
		"containsValue";
const char *CppHibernateJMapObject::JAVA_UTIL_MAP_PUT_NAME = "put";
const char *CppHibernateJMapObject::JAVA_UTIL_MAP_PUT_SIGNATURE =
		"(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;";
const char *CppHibernateJMapObject::JAVA_UTIL_MAP_GET_NAME = "get";
const char *CppHibernateJMapObject::JAVA_UTIL_MAP_GET_SIGNATURE =
		"(Ljava/lang/Object;)Ljava/lang/Object;";
const char *CppHibernateJMapObject::JAVA_UTIL_MAP_KEYSET_NAME = "keySet";
const char *CppHibernateJMapObject::JAVA_UTIL_MAP_KEYSET_SIGNATURE =
		"()Ljava/util/Set;";
const char *CppHibernateJMapObject::JAVA_UTIL_MAP_PUTALL_NAME = "putAll";
const char *CppHibernateJMapObject::JAVA_UTIL_MAP_PUTALL_SIGNATURE =
		"(Ljava/util/Map;)V";
const char *CppHibernateJMapObject::JAVA_UTIL_MAP_VALUES_NAME = "values";
const char *CppHibernateJMapObject::JAVA_UTIL_MAP_VALUES_SIGNATURE =
		"()Ljava/util/Collection;";
const char *CppHibernateJMapObject::JAVA_UTIL_MAP_ENTRYSET_NAME = "entrySet";
const char *CppHibernateJMapObject::JAVA_UTIL_MAP_ENTRYSET_SIGNATURE =
		"()Ljava/util/Set;";
const char *CppHibernateJMapObject::JAVA_UTIL_HASHMAP_ENTRY =
		"java.util.HashMap.Entry";

CppHibernateJMapObject::CppHibernateJMapObject(JNIEnv *env, jobject obj,
		jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateJCollectionsObject(env, obj, objClass, classLoader) {

	this->checkInstanceOfMap();
}

/**
 * Checks if this object as an instance of java.util.Map contains the specified object or not.
 * @param CppHibernateJObject * obj Object to be examined with this object.
 * @return bool Returns true if this object contains the specified object. False otherwise.
 * @throw Throws exceptions when JNI encounters exceptions and also throws an exception when this object is not an instance
 * of java.util.Map.
 */
bool CppHibernateJMapObject::containsKey(CppHibernateJObject *obj) {

	this->checkInstanceOfMap();

	jmethodID containsKeyId = this->env->GetMethodID(this->objClass,
			CppHibernateJMapObject::JAVA_UTIL_MAP_CONTAINSKEY_NAME,
			CppHibernateJCollectionsObject::RETURN_BOOL_PARAM_OBJECT_SIGNATURE);
	this->checkAndThrow();

	bool result = this->env->CallBooleanMethod(this->obj, containsKeyId,
			obj->getObj());
	this->checkAndThrow();

	return result;
}

/**
 * Checks if this as an instance of java.util.Map contains the specified object as a value or not.
 * @param CppHibernateJObject *value Value object to be searched for as a value.
 * @return bool Returns true if this contains the specified object as a value, otherwise returns false.
 * @throw Throws exceptions when JNI encounters exceptions and this is not an instance of java.util.Map.
 */
bool CppHibernateJMapObject::containsValue(CppHibernateJObject *value) {
	this->checkInstanceOfMap();

	jmethodID containsValueId = this->env->GetMethodID(this->objClass,
			CppHibernateJMapObject::JAVA_UTIL_MAP_CONTAINSVALUE_NAME,
			CppHibernateJCollectionsObject::RETURN_BOOL_PARAM_OBJECT_SIGNATURE);
	this->checkAndThrow();

	bool result = this->env->CallBooleanMethod(this->obj, containsValueId,
			value->getObj());
	this->checkAndThrow();

	return result;
}

/**
 * Puts a key and value pair onto this object as an instance of Java.util.Map.
 * @param CppHibernateJObject *key Key for this object.
 * @param CppHibernateJObject *value Value for this object.
 * @param bool returnOldObj True if the replaced object is required. False otherwise. The default value is false.
 * @return CppHibernateJObject * Returns The replaced object with the same key or NULL. The returned value is dependent on the returnOldObj parameter.
 * The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions and also this object is not instance of java.util.Map.
 */
CppHibernateJObject *CppHibernateJMapObject::put(CppHibernateJObject *key,
		CppHibernateJObject *value, bool returnOldObj) {

	this->checkInstanceOfMap();
	jmethodID putId = this->env->GetMethodID(this->objClass,
			CppHibernateJMapObject::JAVA_UTIL_MAP_PUT_NAME,
			CppHibernateJMapObject::JAVA_UTIL_MAP_PUT_SIGNATURE);
	this->checkAndThrow();

	jobject result = this->env->CallObjectMethod(this->obj, putId,
			key->getObj(), value->getObj());
	this->checkAndThrow();

	if (!returnOldObj) {
		return NULL;
	}

	if (result == NULL) {
		return NULL;
	}

	return this->createReturnObj(this->env->NewGlobalRef(result));
}

/**
 * Gets value keyed by the specified object.
 * @param CppHibernateJObject * Key object to be used to retrieve the corresponding value.
 * @return CppHibernateJObject * Returns the corresponding value as CppHibernateJObject or NULL if there is no value for the specified key,
 * The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateJObject *CppHibernateJMapObject::get(CppHibernateJObject *key) {

	this->checkInstanceOfMap();
	jmethodID getId = this->env->GetMethodID(this->objClass,
			CppHibernateJMapObject::JAVA_UTIL_MAP_GET_NAME,
			CppHibernateJMapObject::JAVA_UTIL_MAP_GET_SIGNATURE);
	this->checkAndThrow();

	jobject result = this->env->CallObjectMethod(this->obj, getId,
			key->getObj());
	this->checkAndThrow();

	if (result == NULL) {
		return NULL;
	}

	return this->createReturnObj(this->env->NewGlobalRef(result));
}

/**
 * Returns all the keys as an instance of java.util.Set.
 * @return CppHibernateJObject * Returns a CppHibernateKeySetObject holding all the keys in this object as an instance of java.util.Map.
 * The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions and this object is not an instance of java.util.Map.
 */
CppHibernateJCollectionObject *CppHibernateJMapObject::keySet() {

	this->checkInstanceOfMap();

	jmethodID keySetId = this->env->GetMethodID(this->objClass,
			CppHibernateJMapObject::JAVA_UTIL_MAP_KEYSET_NAME,
			CppHibernateJMapObject::JAVA_UTIL_MAP_KEYSET_SIGNATURE);
	this->checkAndThrow();

	jobject result = this->env->CallObjectMethod(this->obj, keySetId);
	this->checkAndThrow();

	return new CppHibernateJCollectionObject(
			this->env,
			this->env->NewGlobalRef(result),
			(jclass) (((this->env->NewGlobalRef(
					this->env->GetObjectClass(result))))), this->classLoader);
}

/**
 * Puts all the key-value pair from the specified instance of java.util.Map to this object.
 * @param CppHibernateJObject *Object where the key-value pairs are copied.
 * @throw Throws exceptions when JNI encounters exceptions and this object is not instance of java.util.Map and the specified object is not java.util.Map.
 */
void CppHibernateJMapObject::putAll(CppHibernateJMapObject *map) {
	this->checkInstanceOfMap();
	jmethodID putAllId = this->env->GetMethodID(this->objClass,
			CppHibernateJMapObject::JAVA_UTIL_MAP_PUTALL_NAME,
			CppHibernateJMapObject::JAVA_UTIL_MAP_PUTALL_SIGNATURE);
	this->checkAndThrow();
	this->env->CallVoidMethod(this->obj, putAllId, map->getObj());
	this->checkAndThrow();
}

/**
 * Clears each key-value pair in this object as an instance of java.util.Map.
 */
void CppHibernateJMapObject::clear() {
	this->checkInstanceOfMap();
	jmethodID clearId = this->env->GetMethodID(this->objClass,
			CppHibernateJCollectionsObject::JAVA_UTIL_CLEAR_NAME,
			CppHibernateJCollectionsObject::JAVA_UTIL_CLEAR_SIGNATURE);
	this->checkAndThrow();
	this->env->CallVoidMethod(this->obj, clearId);
	this->checkAndThrow();
}

/**
 * Gets all the values in this object as an instance of java.util.Map.
 * @return CppHibernateJCollectionObject * Returns the values as CppHibernateJCollectionObject. The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateJCollectionObject *CppHibernateJMapObject::values() {
	this->checkInstanceOfMap();
	jmethodID valuesId = this->env->GetMethodID(this->objClass,
			CppHibernateJMapObject::JAVA_UTIL_MAP_VALUES_NAME,
			CppHibernateJMapObject::JAVA_UTIL_MAP_VALUES_SIGNATURE);
	this->checkAndThrow();
	jobject result = this->env->CallObjectMethod(this->obj, valuesId);
	this->checkAndThrow();
	return new CppHibernateJCollectionObject(
			this->env,
			this->env->NewGlobalRef(result),
			(jclass) (((this->env->NewGlobalRef(
					this->env->GetObjectClass(result))))), this->classLoader);
}

/**
 * Checks if this object is an instance of java.util.Map. If so,does nothing. If not, throws an exception.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
void CppHibernateJMapObject::checkInstanceOfMap() {
	if (!this->isInstanceOf(CppHibernateJCollectionsObject::JAVA_UTIL_MAP)
			&& (std::strncmp(
					this->getCanonicalName(),
					CppHibernateJMapObject::JAVA_UTIL_HASHMAP_ENTRY,
					std::strlen(
							CppHibernateJMapObject::JAVA_UTIL_HASHMAP_ENTRY))
					!= 0)) {

		throw CppHibernateException(
				this->createSimpleErrorMessage(
						CppHibernateJCollectionsObject::JAVA_UTIL_MAP).c_str());
	}
}

CppHibernateJMapObject::~CppHibernateJMapObject() {

}

} /* namespace cppHibernate */
