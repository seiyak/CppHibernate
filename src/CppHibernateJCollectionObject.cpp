/*
 * CppHibernateJCollectionObject.cpp
 *
 *  Created on: Jan 6, 2012
 *      Author: seiyak
 */

#include <sstream>
#include "CppHibernateJCollectionObject.h"

namespace cppHibernate {

const char *CppHibernateJCollectionObject::JAVA_UTIL_COLLECTION_TOARRAY_NAME =
		"toArray";
const char *CppHibernateJCollectionObject::JAVA_UTIL_COLLECTION_TOARRAY_SIGNATURE =
		"([Ljava/lang/Object;)[Ljava/lang/Object;";
const char *CppHibernateJCollectionObject::JAVA_UTIL_COLLECTION_ADD_NAME = "add";
const char *CppHibernateJCollectionObject::JAVA_UTIL_COLLECTION_ADD_SIGNATURE =
		"(Ljava/lang/Object;)Z";
const char *CppHibernateJCollectionObject::JAVA_UTIL_COLLECTION_REMOVE_NAME =
		"remove";
const char *CppHibernateJCollectionObject::JAVA_UTIL_COLLECTION_REMOVE_SIGNATURE =
		"(Ljava/lang/Object;)Z";
const char *CppHibernateJCollectionObject::JAVA_UTIL_COLLECTION_ITERATOR_NAME =
		"iterator";
const char *CppHibernateJCollectionObject::JAVA_UTIL_COLLECTION_ITERATOR_SIGNATURE =
		"()Ljava/util/Iterator;";

CppHibernateJCollectionObject::CppHibernateJCollectionObject(JNIEnv *env,
		jobject obj, jclass objClass, AbstractClassLoader *classLoader) :
		objArray(NULL), CppHibernateJCollectionsObject(env, obj, objClass,
				classLoader) {

	this->checkInstanceOfCollection();
	if (this->isInstanceOf(
			CppHibernateJCollectionObject::JAVA_UTIL_COLLECTION)) {
		this->fillObjArray();
	}
}

/**
 * Clears all the elements on this object as an instance of java.util.Collection or java.util.Map.
 * @throw Throws exceptions when JNI encounters exceptions and also when this method is called with objects that are neither instance of java,.util.Collection nor java.util.Map.
 */
void CppHibernateJCollectionObject::clear() {

	this->checkInstanceOfCollectionOrMap();

	jmethodID clearId = this->env->GetMethodID(this->objClass,
			CppHibernateJCollectionsObject::JAVA_UTIL_CLEAR_NAME,
			CppHibernateJCollectionsObject::JAVA_UTIL_CLEAR_SIGNATURE);

	if (clearId != NULL) {

		this->env->CallVoidMethod(this->obj, clearId);

		this->env->DeleteGlobalRef(this->objArray);
		this->objArray = NULL;
		this->checkAndThrow();
	} else {
		this->env->DeleteGlobalRef(this->objArray);
		this->objArray = NULL;
		this->throwException();
	}
}

/**
 * Gets an object by the specified index on this object as an instance of java.util.Collection.
 * @param int index Index for a specified object.
 * @return CppHibernateJObject * Returns CppHibernateJObject pointer having the object by the specified index. The returned object must be released when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions and also when this method is called with objects that are not instance of java,.util.Collection.
 * Also throws an exception when an invalid index is specified.
 */
CppHibernateJObject *CppHibernateJCollectionObject::get(int index) {
	this->checkInstanceOfCollection();
	this->checkValidIndex(index);
	jobject element = this->env->GetObjectArrayElement(this->objArray, index);
	this->checkAndThrow();

	return this->createReturnObj(this->env->NewGlobalRef(element));
}

/**
 * Checks if the specified index is valid or not based on the size of this object as an instance of java.util.Collection.
 * If so, does nothing. If not, throws an exception.
 * @param int & index Index to be examined.
 * @throw Throws an exception when the specified index is invalid.
 */
void CppHibernateJCollectionObject::checkValidIndex(int & index) {
	if (index < 0 || index >= this->size()) {
		std::string errorMessage(
				"The specified index is invalid for the size, ");
		std::stringstream strSize;
		strSize << this->size();
		errorMessage += strSize.str() + " ,but specified ";
		std::stringstream strIndex;
		strIndex << index;
		errorMessage += strIndex.str();
		throw CppHibernateException(errorMessage.c_str());
	}
}

/**
 * Adds the specified element to this object as an instance of java.util.Collection.
 * @param CppHibernateJObject *element Element to be added to this object.
 * @return bool Returns true if successfully adds the element, false otherwise.
 * @throw Throws exceptions when JNI encounters exceptions and also when this method is called with objects that are not instance of java,.util.Collection.
 */
bool CppHibernateJCollectionObject::add(CppHibernateJObject *element) {
	this->checkInstanceOfCollection();
	this->checkNull(element);
	bool added = false;
	jmethodID addId = this->env->GetMethodID(this->objClass,
			CppHibernateJCollectionObject::JAVA_UTIL_COLLECTION_ADD_NAME,
			CppHibernateJCollectionObject::JAVA_UTIL_COLLECTION_ADD_SIGNATURE);
	if (addId != NULL) {

		if (this->env->CallBooleanMethod(this->obj, addId,
				element->getObj()) == JNI_TRUE) {
			this->checkAndThrow();

			added = true;
			this->fillObjArray();
		} else if (this->env->CallBooleanMethod(this->obj, addId,
				element->getObj()) == JNI_FALSE) {
			this->checkAndThrow();

			added = false;
		}
	} else {
		this->throwException();
	}
	return added;
}

/**
 * Removes the specified element from this object as an instance of java.util.Collection.
 * @param CppHibernateJObject * element Element to be removed from this object.
 * @return bool Returns true if the object is removed, false otherwise.
 * @throw Throws exceptions when JNI encounters exceptions and also when this method is called with objects that are not instance of java,.util.Collection.
 */
bool CppHibernateJCollectionObject::remove(CppHibernateJObject *element) {
	this->checkInstanceOfCollection();
	this->checkNull(element);
	bool removed = false;
	jmethodID removeId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateJCollectionObject::JAVA_UTIL_COLLECTION_REMOVE_NAME,
					CppHibernateJCollectionObject::JAVA_UTIL_COLLECTION_REMOVE_SIGNATURE);
	if (removeId != NULL) {

		if (this->env->CallBooleanMethod(this->obj, removeId,
				element->getObj()) == JNI_TRUE) {
			this->checkAndThrow();

			removed = true;
			this->fillObjArray();
		} else if (this->env->CallBooleanMethod(this->obj, removeId,
				element->getObj()) == JNI_FALSE) {
			this->checkAndThrow();

			removed = false;
		}
	} else {
		this->throwException();
	}
	return removed;
}

/**
 * Creates a java.util.Iterator object for this object.
 * @return CppHibernateJIteratorObject Returns CppHibernateJIteratorObject object.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateJIteratorObject CppHibernateJCollectionObject::iterator() {

	jmethodID iteratorId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateJCollectionObject::JAVA_UTIL_COLLECTION_ITERATOR_NAME,
					CppHibernateJCollectionObject::JAVA_UTIL_COLLECTION_ITERATOR_SIGNATURE);
	this->checkAndThrow();

	jobject result = this->env->CallObjectMethod(this->obj, iteratorId);
	this->checkAndThrow();

	return CppHibernateJIteratorObject(this->env,
			this->env->NewGlobalRef(result),
			(jclass) this->env->NewGlobalRef(this->env->GetObjectClass(result)),
			this->classLoader);
}

/**
 * Fills the objArray property in this constructor. This method is only called when this object is an instance of java.util.Collection.
 * if not, the objArray property remains NULL.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
void CppHibernateJCollectionObject::fillObjArray() {
	if (this->objArray != NULL) {

		this->env->DeleteGlobalRef(this->objArray);
		this->objArray = NULL;
	}
	jmethodID toArrayId =
			this->env->GetMethodID(
					this->objClass,
					CppHibernateJCollectionObject::JAVA_UTIL_COLLECTION_TOARRAY_NAME,
					CppHibernateJCollectionObject::JAVA_UTIL_COLLECTION_TOARRAY_SIGNATURE);
	if (toArrayId != NULL) {
		jobjectArray array = this->env->NewObjectArray(this->size(),
				this->env->FindClass("java/lang/Object"), NULL);
		this->checkAndThrow();

		if (array != NULL) {

			array = (jobjectArray) this->env->CallObjectMethod(this->obj,
					toArrayId, array);
			this->checkAndThrow();

			if (array != NULL) {

				this->objArray = (jobjectArray) this->env->NewGlobalRef(array);
				this->checkAndThrow();

			} else {
				this->throwException();
			}

		} else {

			this->throwException();
		}
	} else {

		this->throwException();
	}
}

/**
 * Checks if this object is an instance of java.util.Collection. If so, does nothing. If not, throws an exception.
 */
void CppHibernateJCollectionObject::checkInstanceOfCollection() {
	if (!this->isInstanceOf(
			CppHibernateJCollectionsObject::JAVA_UTIL_COLLECTION)) {
		throw CppHibernateException(
				this->createSimpleErrorMessage(
						CppHibernateJCollectionsObject::JAVA_UTIL_COLLECTION).c_str());
	}
}

CppHibernateJCollectionObject::~CppHibernateJCollectionObject() {
	if (this->objArray != NULL) {
		this->env->DeleteGlobalRef(this->objArray);
		this->objArray = NULL;
	}
}

} /* namespace cppHibernate */
