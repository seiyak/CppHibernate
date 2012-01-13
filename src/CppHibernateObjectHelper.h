/*
 * CppHibernateObjectHelper.h
 *
 *  Created on: Nov 14, 2011
 *      Author: apple
 */

#ifndef CPPHIBERNATEOBJECTHELPER_H_
#define CPPHIBERNATEOBJECTHELPER_H_

#include <map>
#include <iostream>
#include "CppHibernateJObject.h"
#include "CppHibernateJBooleanObject.h"
#include "CppHibernateJStringObject.h"
#include "CppHibernateJIntegerObject.h"
#include "CppHibernateJFloatObject.h"
#include "CppHibernateJDoubleObject.h"
#include "CppHibernateJLongObject.h"
#include "CppHibernateJArray.h"
#include "CppHibernateArrayType.h"

namespace cppHibernate {

class CppHibernateObjectHelper: CppHibernateCommonExceptionChecks,
		CppHibernateCommonProperties {

private:
	const char *DOT_CLASS_SEPARATOR;
	const char *SLASH_CLASS_SEPARATOR;
	static const char *ARRAY_TYPE_OBJECT;

	JNIEnv *env;
	AbstractClassLoader *classLoader;
	static std::map<const char*, const char*> constructorMap;

	bool isClassNameFormatValid(const char *);
	const char *formatClassName(const char *);
	const char *createClassName(const char *);
	static jobject findDefaultConstructorFor(JNIEnv *, jclass);
	template<class T> jobject createWrapperObjectFor(jclass, const char *, T&);
	void initializeMap();
	jobject findClassWith(const char *);
	template<class T> CppHibernateJArray<T> createJBooleanArray(const char*,
			unsigned int&, T*);
	template<class T> CppHibernateJArray<T> createJUnsignedCharArray(
			const char *, unsigned int&, T*);
	template<class T> CppHibernateJArray<T> createJCharArray(const char *,
			unsigned int&, T*);
	template<class T> CppHibernateJArray<T> createJShortArray(const char *,
			unsigned int&, T*);
	template<class T> CppHibernateJArray<T> createJIntArray(const char *,
			unsigned int&, T*);
	template<class T> CppHibernateJArray<T> createJLongArray(const char *,
			unsigned int&, T*);
	template<class T> CppHibernateJArray<T> createJFloatArray(const char *,
			unsigned int&, T*);
	template<class T> CppHibernateJArray<T> createJDoubleArray(const char *,
			unsigned int&, T*);
	template<class T> CppHibernateJArray<T> createJBooleanObjectArray(
			const char *, unsigned int&, T*);
	template<class T> CppHibernateJArray<T> createJArrayReturnObj(unsigned int&,
			const char *, T*, jobject, jclass);
	static std::string extractStringFrom(const char *, size_t start = 0,
			size_t end = 1);
	static CppHibernateJIntegerObject *newJIntegerInstance(JNIEnv *, jobject,
			AbstractClassLoader*);
	static CppHibernateJStringObject *newJStringInstance(JNIEnv *, jobject,
			AbstractClassLoader *);
	static CppHibernateJFloatObject *newJFloatInstance(JNIEnv *, jobject,
			AbstractClassLoader *);
	static CppHibernateJBooleanObject *newJBooleanInstance(JNIEnv *, jobject,
			AbstractClassLoader *);
	static CppHibernateJDoubleObject *newJDoubleInstance(JNIEnv *, jobject,
			AbstractClassLoader *);
	static CppHibernateJLongObject *newJLongInstance(JNIEnv *, jobject,
			AbstractClassLoader *);
	static CppHibernateJObject *newJObjectInstance(JNIEnv *, jobject,
			AbstractClassLoader *, const char*);
	static CppHibernateJObject *newJArray(JNIEnv *, jobject,
			AbstractClassLoader *, std::string&);
	static CppHibernateJObject *newJBooleanPrimitiveArray(JNIEnv *, jobject,
			AbstractClassLoader *);
	static CppHibernateJObject *newJBytePrimitiveArray(JNIEnv *, jobject,
			AbstractClassLoader *);
	static CppHibernateJObject *newJCharPrimitiveArray(JNIEnv *, jobject,
			AbstractClassLoader *);
	static CppHibernateJObject *newJShortPrimitiveArray(JNIEnv *, jobject,
			AbstractClassLoader *);
	static CppHibernateJObject *newJIntPrimitiveArray(JNIEnv *, jobject,
			AbstractClassLoader *);
	static CppHibernateJObject *newJLongPrimitiveArray(JNIEnv *, jobject,
			AbstractClassLoader *);
	static CppHibernateJObject *newJFloatPrimitiveArray(JNIEnv *, jobject,
			AbstractClassLoader *);
	static CppHibernateJObject *newJDoublePrimitiveArray(JNIEnv *, jobject,
			AbstractClassLoader *);
	static jobject findClassWith(JNIEnv *, const char*);
	static bool isValidRange(size_t &, size_t&, int);
	static void checkRequiredProperties(JNIEnv *, AbstractClassLoader*,
			const char *, jobject);
	static void checkAndThrow(JNIEnv *);

protected:
	template<class T> std::string convertStringFrom(T&);

public:

	CppHibernateObjectHelper(JNIEnv*, AbstractClassLoader*);
	static CppHibernateJObject *newInstance(JNIEnv*, AbstractClassLoader*,
			std::string, jobject);
	CppHibernateJObject *createJObjectWith(const char *);
	CppHibernateJBooleanObject *createJBooleanObjectWith(bool val = false);
	template<class T> CppHibernateJStringObject *createJStringObjectWith(T);
	CppHibernateJIntegerObject *createJIntegerObjectWith(int val = 0);
	CppHibernateJFloatObject *createJFloatObjectWith(float val = 0.0);
	CppHibernateJDoubleObject *createJDoubleObjectWith(double val = 0);
	CppHibernateJLongObject *createJLongObjectWith(long val = 0);
	template<class T> CppHibernateJArray<T> createJArrayWith(
			CppHibernateArrayType, unsigned int, T *);
	static bool isStartedWith(const char *, const char*);
	virtual void throwException();
	virtual void checkAndThrow();
	virtual void checkCommonProperties(JNIEnv*, jobject, jclass,
			AbstractClassLoader*);
	virtual ~CppHibernateObjectHelper();
};

/**
 * Creates a primitive wrapper object.
 * @param jclass jClass Representing the class to be created.
 * @param const char * typeName Type name for the primitive type.
 * @param T& Value to be wrapped by the object.
 * @return jobject Returns the primitive wrapper object. The returned object must be released when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
template<class T> inline jobject CppHibernateObjectHelper::createWrapperObjectFor(
		jclass jClass, const char *typeName, T & val) {

	jobject jObject = NULL;
	if (jClass != NULL) {
		jmethodID jMethodId = this->env->GetMethodID(jClass,
				CppHibernateJObject::JAVA_CONSTRUCTOR_NAME,
				CppHibernateJObject::PRIMITIVE_CLASS_CONSTRUCTOR_SIGNATURE);

		if (jMethodId != NULL) {
			jstring str = NULL;

			if (std::strncmp(typeName, "bool", std::strlen(typeName)) == 0) {
				if (val) {
					str = this->env->NewStringUTF(
							CppHibernateJBooleanObject::JAVA_BOOLEAN_TRUE);
				} else {
					str = this->env->NewStringUTF(
							CppHibernateJBooleanObject::JAVA_BOOLEAN_FALSE);
				}
			} else {
				str = this->env->NewStringUTF(
						this->convertStringFrom(val).c_str());
			}

			this->throwException();

			jobject jObjVal = this->env->NewObject(jClass, jMethodId, str);
			this->env->DeleteLocalRef(str);

			if (jObjVal != NULL) {
				jObject = this->env->NewGlobalRef(jObjVal);
				this->throwException();

			} else {
				this->throwException();
			}
		} else {
			this->throwException();
		}

	} else {
		throw CppHibernateException(
				"The parameter 'jClass' can not be NULL. Please specify it correctly.");
	}
	return jObject;
}

/**
 * Converts the specified value to const char pointer.
 * @param T& val Value to be converted to const char pointer.
 * @return const char pointer Returns const char pointer representing the specified value.
 */
template<class T> inline std::string CppHibernateObjectHelper::convertStringFrom(
		T & val) {

	std::stringstream str;
	str << val;
	return str.str();
}

/**
 * Creates a new CppHibernateJObject object representing a Java class which can be a domain class. This method requires the
 * input class have the default constructor, no argument constructor. This is also a requirement by Java Hibernate.
 * @return CppHibernateJObject * Returns an object representing a Java class.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
template<class T> CppHibernateJStringObject *CppHibernateObjectHelper::createJStringObjectWith(
		T val) {

	jclass strClass = (jclass) this->findClassWith(
			CppHibernateJStringObject::JAVA_LANG_STRING);
	jobject strObj = this->createWrapperObjectFor(strClass, "string", val);

	CppHibernateJStringObject *obj = new CppHibernateJStringObject(this->env,
			strObj, strClass, this->classLoader);

	return obj;
}

/**
 * Creates a new CppHibernateJArray holding the specified array.
 * @param CppHibernateArrayType arrayType Type of the specified array.
 * @param unsigned int arraySize Size of the specified array.
 * @param T *array Array to be converted to Java array.
 * @return CppHibernateJArray<T> Returns CppHibernateJArray<T> holding the converted Java array.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
template<class T> CppHibernateJArray<T> CppHibernateObjectHelper::createJArrayWith(
		CppHibernateArrayType arrayType, unsigned int arraySize, T *array) {

	if (array == NULL) {
		throw CppHibernateException(
				"invalid array is specified for CppHibernateObjectHelper::createJArray.");
	}

	if (std::strncmp(CppHibernateArrayType::ARRAY_BOOL.getArrayType(),
			arrayType.getArrayType(),
			std::strlen(CppHibernateArrayType::ARRAY_BOOL.getArrayType()))
			== 0) {

		return this->createJBooleanArray(arrayType.getArrayType(), arraySize,
				array);

	} else if (std::strncmp(
			CppHibernateArrayType::ARRAY_UNSIGNED_CHAR.getArrayType(),
			arrayType.getArrayType(),
			std::strlen(
					CppHibernateArrayType::ARRAY_UNSIGNED_CHAR.getArrayType()))
			== 0) {

		return this->createJUnsignedCharArray(arrayType.getArrayType(),
				arraySize, array);

	} else if (std::strncmp(CppHibernateArrayType::ARRAY_CHAR.getArrayType(),
			arrayType.getArrayType(),
			std::strlen(CppHibernateArrayType::ARRAY_CHAR.getArrayType()))
			== 0) {

		return this->createJCharArray(arrayType.getArrayType(), arraySize,
				array);

	} else if (std::strncmp(CppHibernateArrayType::ARRAY_SHORT.getArrayType(),
			arrayType.getArrayType(),
			std::strlen(CppHibernateArrayType::ARRAY_SHORT.getArrayType()))
			== 0) {

		return this->createJShortArray(arrayType.getArrayType(), arraySize,
				array);

	} else if (std::strncmp(CppHibernateArrayType::ARRAY_INT.getArrayType(),
			arrayType.getArrayType(),
			std::strlen(CppHibernateArrayType::ARRAY_INT.getArrayType()))
			== 0) {

		return this->createJIntArray(arrayType.getArrayType(), arraySize, array);

	} else if (std::strncmp(CppHibernateArrayType::ARRAY_LONG.getArrayType(),
			arrayType.getArrayType(),
			std::strlen(CppHibernateArrayType::ARRAY_LONG.getArrayType()))
			== 0) {

		return this->createJLongArray(arrayType.getArrayType(), arraySize,
				array);

	} else if (std::strncmp(CppHibernateArrayType::ARRAY_FLOAT.getArrayType(),
			arrayType.getArrayType(),
			std::strlen(CppHibernateArrayType::ARRAY_FLOAT.getArrayType()))
			== 0) {

		return this->createJFloatArray(arrayType.getArrayType(), arraySize,
				array);

	} else if (std::strncmp(CppHibernateArrayType::ARRAY_DOUBLE.getArrayType(),
			arrayType.getArrayType(),
			std::strlen(CppHibernateArrayType::ARRAY_DOUBLE.getArrayType()))
			== 0) {

		return this->createJDoubleArray(arrayType.getArrayType(), arraySize,
				array);

	}

	throw CppHibernateException(
			"invalid array type specified for CppHibernateObjectHelper::createJArrayWith().");
}

template<class T> inline CppHibernateJArray<T> CppHibernateObjectHelper::createJBooleanArray(
		const char *arrayType, unsigned int & arraySize, T *array) {

	jarray jArray = this->env->NewBooleanArray(arraySize);
	this->checkAndThrow();
	this->env->SetBooleanArrayRegion((jbooleanArray) jArray, 0, arraySize,
			(jboolean *) array);
	this->checkAndThrow();
	T *nativeArray = (T *) this->env->GetBooleanArrayElements(
			(jbooleanArray) jArray, JNI_FALSE);
	this->checkAndThrow();
	jobject wrapperObjClass = this->findClassWith(
			CppHibernateJBooleanObject::JAVA_LANG_BOOLEAN);

	return this->createJArrayReturnObj(arraySize, arrayType, nativeArray,
			this->env->NewGlobalRef(jArray), (jclass) wrapperObjClass);
}

template<class T> inline CppHibernateJArray<T> cppHibernate::CppHibernateObjectHelper::createJUnsignedCharArray(
		const char *arrayType, unsigned int & arraySize, T *array) {
	jarray jArray = this->env->NewByteArray(arraySize);
	this->checkAndThrow();
	this->env->SetByteArrayRegion((jbyteArray) jArray, 0, arraySize,
			(jbyte *) array);
	this->checkAndThrow();
	T *nativeArray = (T *) this->env->GetByteArrayElements((jbyteArray) jArray,
			JNI_FALSE);
	this->checkAndThrow();
	//// TODO add Byte class
	jobject wrapperObjClass = this->findClassWith("java/lang/Byte");

	return this->createJArrayReturnObj(arraySize, arrayType, nativeArray,
			this->env->NewGlobalRef(jArray), (jclass) wrapperObjClass);
}

template<class T> inline CppHibernateJArray<T> cppHibernate::CppHibernateObjectHelper::createJCharArray(
		const char *arrayType, unsigned int & arraySize, T *array) {

	jarray jArray = this->env->NewCharArray(arraySize);
	this->checkAndThrow();
	this->env->SetCharArrayRegion((jcharArray) jArray, 0, arraySize,
			(jchar *) &(*array));
	this->checkAndThrow();
	T *nativeArray = (T *) this->env->GetCharArrayElements((jcharArray) jArray,
			JNI_FALSE);
	this->checkAndThrow();
	//// TODO add Char class
	jobject wrapperObjClass = this->findClassWith("java/lang/Character");

	return this->createJArrayReturnObj(arraySize, arrayType, nativeArray,
			this->env->NewGlobalRef(jArray), (jclass) wrapperObjClass);
}

template<class T> inline CppHibernateJArray<T> cppHibernate::CppHibernateObjectHelper::createJShortArray(
		const char *arrayType, unsigned int & arraySize, T *array) {

	jarray jArray = this->env->NewShortArray(arraySize);
	this->checkAndThrow();
	this->env->SetShortArrayRegion((jshortArray) jArray, 0, arraySize,
			(jshort *) &(*array));
	this->checkAndThrow();
	T *nativeArray = (T *) this->env->GetShortArrayElements(
			(jshortArray) jArray, JNI_FALSE);
	this->checkAndThrow();
	//// TODO add Short class
	jobject wrapperObjClass = this->findClassWith("java/lang/Short");

	return this->createJArrayReturnObj(arraySize, arrayType, nativeArray,
			this->env->NewGlobalRef(jArray), (jclass) wrapperObjClass);
}

template<class T> inline CppHibernateJArray<T> cppHibernate::CppHibernateObjectHelper::createJLongArray(
		const char *arrayType, unsigned int & arraySize, T *array) {

	jarray jArray = this->env->NewLongArray(arraySize);
	this->checkAndThrow();
	this->env->SetLongArrayRegion((jlongArray) jArray, 0, arraySize,
			(jlong *) &(*array));
	this->checkAndThrow();
	T *nativeArray = (T *) this->env->GetLongArrayElements((jlongArray) jArray,
			JNI_FALSE);
	this->checkAndThrow();
	jobject wrapperObjClass = this->findClassWith(
			CppHibernateJLongObject::JAVA_LANG_LONG);

	return this->createJArrayReturnObj(arraySize, arrayType, nativeArray,
			this->env->NewGlobalRef(jArray), (jclass) wrapperObjClass);
}

template<class T> inline CppHibernateJArray<T> cppHibernate::CppHibernateObjectHelper::createJIntArray(
		const char *arrayType, unsigned int & arraySize, T *array) {

	jarray jArray = this->env->NewIntArray(arraySize);
	this->checkAndThrow();
	this->env->SetIntArrayRegion((jintArray) jArray, 0, arraySize,
			(jint *) &(*array));
	this->checkAndThrow();
	T *nativeArray = (T *) this->env->GetIntArrayElements((jintArray) jArray,
			JNI_FALSE);
	this->checkAndThrow();
	jobject wrapperObjClass = this->findClassWith(
			CppHibernateJIntegerObject::JAVA_LANG_INTEGER);

	return this->createJArrayReturnObj(arraySize, arrayType, nativeArray,
			this->env->NewGlobalRef(jArray), (jclass) wrapperObjClass);
}

template<class T> inline CppHibernateJArray<T> cppHibernate::CppHibernateObjectHelper::createJFloatArray(
		const char *arrayType, unsigned int & arraySize, T *array) {

	jarray jArray = this->env->NewFloatArray(arraySize);
	this->checkAndThrow();
	this->env->SetFloatArrayRegion((jfloatArray) jArray, 0, arraySize,
			(jfloat *) &(*array));
	this->checkAndThrow();
	T *nativeArray = (T *) this->env->GetFloatArrayElements(
			(jfloatArray) jArray, JNI_FALSE);
	this->checkAndThrow();
	jobject wrapperObjClass = this->findClassWith(
			CppHibernateJFloatObject::JAVA_LANG_FLOAT);

	return this->createJArrayReturnObj(arraySize, arrayType, nativeArray,
			this->env->NewGlobalRef(jArray), (jclass) wrapperObjClass);
}

template<class T> inline CppHibernateJArray<T> cppHibernate::CppHibernateObjectHelper::createJDoubleArray(
		const char *arrayType, unsigned int & arraySize, T *array) {

	jarray jArray = this->env->NewDoubleArray(arraySize);
	this->checkAndThrow();
	this->env->SetDoubleArrayRegion((jdoubleArray) jArray, 0, arraySize,
			(jdouble *) &(*array));
	this->checkAndThrow();
	T *nativeArray = (T *) this->env->GetDoubleArrayElements(
			(jdoubleArray) jArray, JNI_FALSE);
	this->checkAndThrow();
	jobject wrapperObjClass = this->findClassWith(
			CppHibernateJDoubleObject::JAVA_LANG_DOUBLE);

	return this->createJArrayReturnObj(arraySize, arrayType, nativeArray,
			this->env->NewGlobalRef(jArray), (jclass) wrapperObjClass);
}

template<class T> inline CppHibernateJArray<T> cppHibernate::CppHibernateObjectHelper::createJArrayReturnObj(
		unsigned int & arraySize, const char *arrayType, T *nativeArray,
		jobject jArray, jclass wrapperObjClass) {

	return CppHibernateJArray<T>(this->env, arraySize, arrayType, nativeArray,
			jArray, wrapperObjClass, this->classLoader);
}

}

/* namespace cppHibernate */
#endif /* CPPHIBERNATEOBJECTHELPER_H_ */
