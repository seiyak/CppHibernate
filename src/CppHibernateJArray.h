/*
 * CppHibernateJArray.h
 *
 *  Created on: Jan 10, 2012
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEJARRAY_H_
#define CPPHIBERNATEJARRAY_H_

#include "CppHibernateJObject.h"

namespace cppHibernate {

template<class T>
class CppHibernateJArray: public CppHibernateJObject {

private:
	T *array;
	unsigned int arraySize;
	const char *arrayType;

	void deleteJArray();
	void checkException();
	void releaseBooleanArray();
	void releaseUnsignedCharArray();
	void releaseCharArray();
	void releaseShortArray();
	void releaseIntArray();
	void releaseLongArray();
	void releaseFloatArray();
	void releaseDoubleArray();

public:
	CppHibernateJArray(JNIEnv *, unsigned int&, const char*, T*, jobject,
			jclass, AbstractClassLoader *);
	unsigned int length();
	T& operator[](unsigned int);
	virtual ~CppHibernateJArray();
};

template<class T> CppHibernateJArray<T>::CppHibernateJArray(JNIEnv *env,
		unsigned int& arraySize, const char *arrayType, T *array,
		jobject jArray, jclass wrapperObjClass,
		AbstractClassLoader *classLoader) :
		CppHibernateJObject(env, jArray, wrapperObjClass, classLoader), array(
				NULL) {
	this->arraySize = arraySize;
	this->arrayType = arrayType;
	this->array = array;
}

template<class T> inline unsigned int CppHibernateJArray<T>::length() {
	return this->arraySize;
}

template<class T> inline T & cppHibernate::CppHibernateJArray<T>::operator [](
		unsigned int index) {

	return this->array[index];
}

template<class T> CppHibernateJArray<T>::~CppHibernateJArray() {
	if (std::strncmp("bool", this->arrayType, std::strlen("bool")) == 0) {
		this->releaseBooleanArray();
	} else if (std::strncmp("unsigned char", this->arrayType,
			std::strlen("unsigned char")) == 0) {
		this->releaseUnsignedCharArray();
	} else if (std::strncmp("char", this->arrayType, std::strlen("char"))
			== 0) {
		this->releaseCharArray();
	} else if (std::strncmp("short", this->arrayType, std::strlen("short"))
			== 0) {
		this->releaseShortArray();
	} else if (std::strncmp("int", this->arrayType, std::strlen("int")) == 0) {
		this->releaseIntArray();
	} else if (std::strncmp("long", this->arrayType, std::strlen("long"))
			== 0) {
		this->releaseLongArray();
	} else if (std::strncmp("double", this->arrayType, std::strlen("double"))
			== 0) {
		this->releaseDoubleArray();
	}
}

template<class T> inline void CppHibernateJArray<T>::releaseBooleanArray() {
	this->env->ReleaseBooleanArrayElements((jbooleanArray) (((this->obj))),
			(jboolean*) (((this->array))), 0);
}

template<class T> inline void CppHibernateJArray<T>::releaseUnsignedCharArray() {
	this->env->ReleaseByteArrayElements((jbyteArray) ((this->obj)),
			(jbyte*) ((this->array)), 0);
}

template<class T> inline void CppHibernateJArray<T>::releaseCharArray() {
	this->env->ReleaseCharArrayElements((jcharArray) (this->obj),
			(jchar*) (this->array), 0);
}

template<class T> inline void CppHibernateJArray<T>::releaseShortArray() {
	this->env->ReleaseShortArrayElements((jshortArray) (this->obj),
			(jshort*) (this->array), 0);
}

template<class T> inline void CppHibernateJArray<T>::releaseIntArray() {
	this->env->ReleaseIntArrayElements((jintArray) (this->obj),
			(jint*) (this->array), 0);
}

template<class T> inline void CppHibernateJArray<T>::releaseLongArray() {
	this->env->ReleaseLongArrayElements((jlongArray) (this->obj),
			(jlong*) (this->array), 0);
}

template<class T> inline void CppHibernateJArray<T>::releaseFloatArray() {
	this->env->ReleaseFloatArrayElements((jfloatArray) (this->obj),
			(jfloat*) (this->array), 0);
}

template<class T> inline void CppHibernateJArray<T>::releaseDoubleArray() {
	this->env->ReleaseDoubleArrayElements((jdoubleArray) (this->obj),
			(jdouble*) (this->array), 0);
}

/* namespace cppHibernate */
}

#endif /* CPPHIBERNATEJARRAY_H_ */
