/*
 * CppHibernateObjectHelper.cpp
 *
 *  Created on: Nov 14, 2011
 *      Author: apple
 */

#include <cstdlib>
#include <memory>
#include <cstring>
#include <sstream>
#include <stdexcept>
#include "CppHibernateObjectHelper.h"
#include "CppHibernateMutex.h"
#include "CppHibernateJCollectionObject.h"
#include "CppHibernateJMapObject.h"

namespace cppHibernate {

std::map<const char*, const char*> CppHibernateObjectHelper::constructorMap;

CppHibernateObjectHelper::CppHibernateObjectHelper(JNIEnv *env,
		AbstractClassLoader *classLoader) :
		env(env), classLoader(classLoader), DOT_CLASS_SEPARATOR("."), SLASH_CLASS_SEPARATOR(
				"/") {

	this->checkCommonProperties(env, NULL, NULL, classLoader);
	this->initializeMap();
}

/**
 * Initializes CppHibernateObjectHelper::constructorMap storing the primitive wrapper class constructor names for the types.
 */
void CppHibernateObjectHelper::initializeMap() {
	CppHibernateObjectHelper::constructorMap["bool"] =
			CppHibernateJBooleanObject::JAVA_LANG_BOOLEAN;
	CppHibernateObjectHelper::constructorMap["string"] =
			CppHibernateJStringObject::JAVA_LANG_STRING;
	CppHibernateObjectHelper::constructorMap["float"] =
			CppHibernateJFloatObject::JAVA_LANG_FLOAT;
	CppHibernateObjectHelper::constructorMap["double"] =
			CppHibernateJDoubleObject::JAVA_LANG_DOUBLE;
	CppHibernateObjectHelper::constructorMap["long"] =
			CppHibernateJLongObject::JAVA_LANG_LONG;
}

/**
 * Creates a new CppHibernateJObject object representing a Java class which can be a domain class. This method requires the
 * input class have the default constructor, no argument constructor. This is also a requirement by Java Hibernate.
 * @return CppHibernateJObject * Returns an object representing a Java class.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateJObject *CppHibernateObjectHelper::createJObjectWith(
		const char *className) {

	CppHibernateJObject *jObject = NULL;

	const char *targetClassName = this->createClassName(className);
	jobject targetClass = this->classLoader->loadClass(targetClassName);

	if (targetClass != NULL) {
		jobject defaultConstructorId =
				CppHibernateObjectHelper::findDefaultConstructorFor(this->env,
						(jclass) targetClass);
		jobject obj = this->env->NewObject((jclass) targetClass,
				(jmethodID) defaultConstructorId);

		if (this->env->ExceptionCheck()) {
			this->env->DeleteGlobalRef(targetClass);
			this->env->DeleteGlobalRef(defaultConstructorId);
			this->throwException();
		}

		this->env->DeleteGlobalRef(defaultConstructorId);

		if (this->env->IsInstanceOf(
				obj,
				this->env->FindClass(
						CppHibernateJCollectionsObject::JAVA_UTIL_COLLECTION))) {
			jObject = new CppHibernateJCollectionObject(this->env,
					this->env->NewGlobalRef(obj),
					(jclass) this->env->NewGlobalRef(targetClass),
					this->classLoader);
		} else if (this->env->IsInstanceOf(
				obj,
				this->env->FindClass(
						CppHibernateJCollectionsObject::JAVA_UTIL_MAP))) {
			jObject = new CppHibernateJMapObject(this->env,
					this->env->NewGlobalRef(obj),
					(jclass) this->env->NewGlobalRef(targetClass),
					this->classLoader);
		} else {
			jObject = new CppHibernateJObject(this->env,
					this->env->NewGlobalRef(obj),
					(jclass) this->env->NewGlobalRef(targetClass),
					this->classLoader);
		}
	} else {
		this->throwException();
	}
	return jObject;
}

/**
 * finds primitive wrapper classes using the system class loader. The classes are loaded by the loader.
 * @param const char * typeName Name to be looked up. This parameter is required to be a primitive type name.
 * @return jobject Returns an object storing the class information. The returned object must be released when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
jobject CppHibernateObjectHelper::findClassWith(const char *typeName) {
	jobject cls = NULL;
	jclass jClass = this->env->FindClass(typeName);
	if (jClass != NULL) {
		cls = this->env->NewGlobalRef(jClass);
	} else {
		this->throwException();
	}
	return cls;
}

/**
 * Creates java.lang.Boolean object.
 * @param bool val Initial value of the object.
 * @return CppHibernateJBooleanObject * An object representing java.lang.Boolean class. The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateJBooleanObject *CppHibernateObjectHelper::createJBooleanObjectWith(
		bool val) {
	jclass booleanClass = (jclass) ((((((((((((((((((((this->findClassWith(
			CppHibernateJBooleanObject::JAVA_LANG_BOOLEAN)))))))))))))))))))));
	jobject booleanObj = this->createWrapperObjectFor(booleanClass, "bool",
			val);
	CppHibernateJBooleanObject *booleanObject = new CppHibernateJBooleanObject(
			this->env, booleanObj, booleanClass, this->classLoader);
	return booleanObject;
}

/**
 * Creates java.lang.Integer object.
 * @param int val Initial value of the object.
 * @return CppHibernateJIntegerObject * An object representing java.lang.Integer class. The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateJIntegerObject *CppHibernateObjectHelper::createJIntegerObjectWith(
		int val) {
	jclass integerClass = (jclass) ((((((((((((((((((this->findClassWith(
			CppHibernateJIntegerObject::JAVA_LANG_INTEGER)))))))))))))))))));
	jobject integerObj = this->createWrapperObjectFor(integerClass, "int", val);
	return new CppHibernateJIntegerObject(this->env, integerObj, integerClass,
			this->classLoader);
}

/**
 * Creates java.lang.Float object.
 * @param int val Initial value of the object.
 * @return CppHibernateJFloatObject * An object representing java.lang.Float class. The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateJFloatObject *CppHibernateObjectHelper::createJFloatObjectWith(
		float val) {
	jclass floatClass = (jclass) (((((((((((((((this->findClassWith(
			CppHibernateJFloatObject::JAVA_LANG_FLOAT))))))))))))))));
	jobject floatObj = this->createWrapperObjectFor(floatClass, "float", val);
	return new CppHibernateJFloatObject(this->env, floatObj, floatClass,
			this->classLoader);
}

/**
 * Creates java.lang.Double object.
 * @param int val Initial value of the object.
 * @return CppHibernateJDoubleObject * An object representing java.lang.Double class. The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateJDoubleObject *CppHibernateObjectHelper::createJDoubleObjectWith(
		double val) {
	jclass doubleClass = (jclass) ((((((((((((((this->findClassWith(
			CppHibernateJDoubleObject::JAVA_LANG_DOUBLE)))))))))))))));
	jobject doubleObj = this->createWrapperObjectFor(doubleClass, "double",
			val);
	return new CppHibernateJDoubleObject(this->env, doubleObj, doubleClass,
			this->classLoader);
}

/**
 * Creates java.lang.Long object.
 * @param int val Initial value of the object.
 * @return CppHibernateJDoubleObject * An object representing java.lang.Long class. The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
CppHibernateJLongObject *CppHibernateObjectHelper::createJLongObjectWith(
		long val) {
	jclass longClass = (jclass) ((((((((((((this->findClassWith(
			CppHibernateJLongObject::JAVA_LANG_LONG)))))))))))));
	jobject longObj = this->createWrapperObjectFor(longClass, "long", val);
	return new CppHibernateJLongObject(this->env, longObj, longClass,
			this->classLoader);
}

/**
 * Finds the default constructor for the input class.
 * @param jclass objClass Class representation of the input class name.
 * @return jobject Returns the method id for the default constructor. The returned id must be released when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
jobject CppHibernateObjectHelper::findDefaultConstructorFor(JNIEnv *env,
		jclass objClass) {

	std::auto_ptr<CppHibernateMutex> cppHibernateMutex(new CppHibernateMutex);

	jobject constructorId = NULL;
	jmethodID defaultConstructorId = env->GetMethodID(objClass,
			CppHibernateJObject::JAVA_CONSTRUCTOR_NAME,
			CppHibernateJObject::JAVA_DEFAULT_CONSTRUCTOR_SIGNATURE);
	if (defaultConstructorId != NULL) {
		constructorId = env->NewGlobalRef((jobject) defaultConstructorId);
	} else {
		env->DeleteGlobalRef(objClass);
		env->Throw(env->ExceptionOccurred());
	}
	return constructorId;
}

/**
 * Creates a class name based on the input class name.
 * @param const char * Class name used to create an actual Java class name.
 * @return const char * Returns an actual Java class name.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
const char *CppHibernateObjectHelper::createClassName(const char *className) {
	const char *targetClassName = NULL;
	if (this->isClassNameFormatValid(className)) {
		targetClassName = className;
	} else {
		targetClassName = this->formatClassName(className);
	}
	return targetClassName;
}

/**
 * Checks if the input class name has a valid format or not. The input class name is used to load the class with the class loader.
 * The class loader requires a dot separated class name such as 'java.lang.String'. If the input class name follows the naming, returns
 * true, false otherwise.
 * @param const char * className Examined if it has the required class naming format.
 * @return bool Returns true if the input class name follows the format or the input class name is the default package, false otherwise.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
bool CppHibernateObjectHelper::isClassNameFormatValid(const char *className) {
	std::string classNameStr(className);
	size_t dotPos = classNameStr.find(this->DOT_CLASS_SEPARATOR);
	if (dotPos == std::string::npos) {
		size_t slashPos = classNameStr.find(this->SLASH_CLASS_SEPARATOR);
		if (slashPos == std::string::npos) {
			return true;
		} else {
			return false;
		}
	}

	return true;
}

/**
 * Reformats the input class name when it doesn't follow the required class name format which is such as 'java.lang.String'.
 * @param const char * className Class name to be reformatted to the required class name format.
 * @return const char * Returns reformatted class name.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
const char *CppHibernateObjectHelper::formatClassName(const char *className) {
	std::string classNameStr(className);
	if (classNameStr.compare("") == 0) {
		throw CppHibernateException(
				"the input class name can not be NULL, but specified NULL.");
	}
	size_t slashPos = classNameStr.find_first_of(this->SLASH_CLASS_SEPARATOR);
	if (slashPos == std::string::npos) {
		return className;
	}
	while (slashPos != std::string::npos) {
		classNameStr.replace(slashPos, 1, this->DOT_CLASS_SEPARATOR);
		slashPos = classNameStr.find_first_of(this->SLASH_CLASS_SEPARATOR,
				slashPos + 1);
	}
	return classNameStr.c_str();
}

/**
 * Instantiates a new object based on the given criteria as the parameters. This method is called by CppHibernateJObject::getVal(const char *) method.
 * @param JNIEnv * JNI pointer.
 * @param AbstractClassLoader * classLoader Class loader to load the class.
 * @param std::string signature  Signature to define which object it is.
 * @param jobject fieldVal Store the field value.
 * @return CppHibernateJObject * Depending on the signature, the returned object is a concrete object rather than
 * CppHibernateJObject. Also the returned value must be deleted then the job is done.
 * @throw Throws exceptions when JNI encounters exceptions and there is no corresponding object, CppXXXObject available for the specified signature.
 */
CppHibernateJObject *CppHibernateObjectHelper::newInstance(JNIEnv *env,
		AbstractClassLoader *classLoader, std::string signature,
		jobject fieldVal) {
	std::auto_ptr<CppHibernateMutex> cppHibernateMutex(new CppHibernateMutex);

	CppHibernateObjectHelper::checkRequiredProperties(env, classLoader,
			signature.c_str(), fieldVal);

	if (std::strncmp(signature.c_str(),
			CppHibernateJIntegerObject::JAVA_LANG_INTEGER_PRIMITIVE_SIGNATURE,
			signature.size()) == 0
			|| std::strncmp(signature.c_str(),
					CppHibernateJIntegerObject::JAVA_LANG_INTEGER_SIGNATURE,
					signature.size()) == 0) {
		return CppHibernateObjectHelper::newJIntegerInstance(env, fieldVal,
				classLoader);
	} else if (std::strncmp(signature.c_str(),
			CppHibernateJStringObject::JAVA_LANG_STRING_SIGNATURE,
			signature.size()) == 0) {
		return CppHibernateObjectHelper::newJStringInstance(env, fieldVal,
				classLoader);
	} else if (std::strncmp(signature.c_str(),
			CppHibernateJFloatObject::JAVA_LANG_FLOAT_PRIMITIVE_SIGNATURE,
			signature.size()) == 0
			|| std::strncmp(signature.c_str(),
					CppHibernateJFloatObject::JAVA_LANG_FLOAT_SIGNATURE,
					signature.size()) == 0) {
		return CppHibernateObjectHelper::newJFloatInstance(env, fieldVal,
				classLoader);
	} else if (std::strncmp(signature.c_str(),
			CppHibernateJBooleanObject::JAVA_LANG_BOOLEAN_PRIMITIVE_SIGNATURE,
			signature.size()) == 0
			|| std::strncmp(signature.c_str(),
					CppHibernateJBooleanObject::JAVA_LANG_BOOLEAN_SIGNATURE,
					signature.size()) == 0) {
		return CppHibernateObjectHelper::newJBooleanInstance(env, fieldVal,
				classLoader);
	} else if (std::strncmp(signature.c_str(),
			CppHibernateJDoubleObject::JAVA_LANG_DOUBLE_PRIMITIVE_SIGNATURE,
			signature.size()) == 0
			|| std::strncmp(signature.c_str(),
					CppHibernateJDoubleObject::JAVA_LANG_DOUBLE_SIGNATURE,
					signature.size()) == 0) {
		return CppHibernateObjectHelper::newJDoubleInstance(env, fieldVal,
				classLoader);
	} else if (std::strncmp(signature.c_str(),
			CppHibernateJLongObject::JAVA_LANG_LONG_PRIMITIVE_SIGNATURE,
			signature.size()) == 0
			|| std::strncmp(signature.c_str(),
					CppHibernateJLongObject::JAVA_LANG_LONG_SIGNATURE,
					signature.size()) == 0) {
		return CppHibernateObjectHelper::newJLongInstance(env, fieldVal,
				classLoader);
	} else if (!CppHibernateObjectHelper::isStartedWith(signature.c_str(),
			CppHibernateJObject::JAVA_ARRAY_SIGNATURE)) {

		return CppHibernateObjectHelper::newJObjectInstance(env, fieldVal,
				classLoader, signature.c_str());
	} else if (CppHibernateObjectHelper::isStartedWith(signature.c_str(),
			CppHibernateJObject::JAVA_ARRAY_SIGNATURE)) {
		return CppHibernateObjectHelper::newJArray(env, fieldVal, classLoader,
				signature);
	}

	throw CppHibernateException(
			"could not find the corresponding CppXXXObject");
}

CppHibernateJIntegerObject *CppHibernateObjectHelper::newJIntegerInstance(
		JNIEnv *env, jobject fieldVal, AbstractClassLoader *classLoader) {
	jobject intClass = env->NewGlobalRef(
			env->FindClass(CppHibernateJIntegerObject::JAVA_LANG_INTEGER));
	CppHibernateObjectHelper::checkAndThrow(env);
	return new CppHibernateJIntegerObject(env, fieldVal,
			(jclass) (((((((((((intClass))))))))))), classLoader);
}

CppHibernateJStringObject *CppHibernateObjectHelper::newJStringInstance(
		JNIEnv *env, jobject fieldVal, AbstractClassLoader *classLoader) {
	jobject stringClass = env->NewGlobalRef(
			env->FindClass(CppHibernateJStringObject::JAVA_LANG_STRING));
	CppHibernateObjectHelper::checkAndThrow(env);
	return new CppHibernateJStringObject(env, fieldVal,
			(jclass) ((((((((((stringClass)))))))))), classLoader);
}

CppHibernateJFloatObject *CppHibernateObjectHelper::newJFloatInstance(
		JNIEnv *env, jobject fieldVal, AbstractClassLoader *classLoader) {
	jobject floatClass = env->NewGlobalRef(
			env->FindClass(CppHibernateJFloatObject::JAVA_LANG_FLOAT));
	CppHibernateObjectHelper::checkAndThrow(env);
	return new CppHibernateJFloatObject(env, fieldVal,
			(jclass) ((((((((floatClass)))))))), classLoader);
}

CppHibernateJBooleanObject *CppHibernateObjectHelper::newJBooleanInstance(
		JNIEnv *env, jobject fieldVal, AbstractClassLoader *classLoader) {
	jobject booleanClass = env->NewGlobalRef(
			env->FindClass(CppHibernateJBooleanObject::JAVA_LANG_BOOLEAN));
	CppHibernateObjectHelper::checkAndThrow(env);
	return new CppHibernateJBooleanObject(env, fieldVal,
			(jclass) (((((((booleanClass))))))), classLoader);
}

CppHibernateJDoubleObject *CppHibernateObjectHelper::newJDoubleInstance(
		JNIEnv *env, jobject fieldVal, AbstractClassLoader *classLoader) {
	jobject doubleClass = env->NewGlobalRef(
			env->FindClass(CppHibernateJDoubleObject::JAVA_LANG_DOUBLE));
	CppHibernateObjectHelper::checkAndThrow(env);
	return new CppHibernateJDoubleObject(env, fieldVal,
			(jclass) (((((doubleClass))))), classLoader);
}

CppHibernateJLongObject *CppHibernateObjectHelper::newJLongInstance(JNIEnv *env,
		jobject fieldVal, AbstractClassLoader *classLoader) {
	jobject longClass = env->NewGlobalRef(
			env->FindClass(CppHibernateJLongObject::JAVA_LANG_LONG));
	CppHibernateObjectHelper::checkAndThrow(env);
	return new CppHibernateJLongObject(env, fieldVal, (jclass) (((longClass))),
			classLoader);
}

CppHibernateJObject *CppHibernateObjectHelper::newJObjectInstance(JNIEnv *env,
		jobject fieldVal, AbstractClassLoader *classLoader,
		const char *signature) {

	jobject javaClass = NULL;
	int siz = std::strlen(signature);
	std::string targetClass = CppHibernateObjectHelper::extractStringFrom(
			signature, 1, siz - 2);
	javaClass = env->FindClass(targetClass.c_str());
	if (env->ExceptionCheck() || javaClass == NULL) {
		env->ExceptionClear();

		CppHibernateAccessor::replaceAll(targetClass, "/", ".", 1);

		javaClass = classLoader->loadClass(targetClass.c_str());
		CppHibernateObjectHelper::checkAndThrow(env);
	}
	CppHibernateObjectHelper::checkAndThrow(env);

	if (env->IsInstanceOf(
			fieldVal,
			env->FindClass(
					CppHibernateJCollectionsObject::JAVA_UTIL_COLLECTION))) {
		return new CppHibernateJCollectionObject(env, fieldVal,
				(jclass) (env->NewGlobalRef(javaClass)), classLoader);
	} else if (env->IsInstanceOf(fieldVal,
			env->FindClass(CppHibernateJCollectionsObject::JAVA_UTIL_MAP))) {
		return new CppHibernateJMapObject(env, fieldVal,
				(jclass) (env->NewGlobalRef(javaClass)), classLoader);
	}
	return new CppHibernateJObject(env, fieldVal,
			(jclass) (env->NewGlobalRef(javaClass)), classLoader);
}

CppHibernateJObject *CppHibernateObjectHelper::newJArray(JNIEnv *env,
		jobject fieldVal, AbstractClassLoader *classLoader,
		std::string &signature) {

	if (signature.compare(CppHibernateArrayType::ARRAY_BOOL.getArrayPrefix())
			== 0) {
		//// boolean array
		return CppHibernateObjectHelper::newJBooleanPrimitiveArray(env,
				fieldVal, classLoader);

	} else if (signature.compare(
			CppHibernateArrayType::ARRAY_UNSIGNED_CHAR.getArrayPrefix()) == 0) {
		//// byte array
		return CppHibernateObjectHelper::newJBytePrimitiveArray(env, fieldVal,
				classLoader);

	} else if (signature.compare(
			CppHibernateArrayType::ARRAY_CHAR.getArrayPrefix()) == 0) {
		//// char array
		return CppHibernateObjectHelper::newJCharPrimitiveArray(env, fieldVal,
				classLoader);

	} else if (signature.compare(
			CppHibernateArrayType::ARRAY_SHORT.getArrayPrefix()) == 0) {
		//// short array
		return CppHibernateObjectHelper::newJShortPrimitiveArray(env, fieldVal,
				classLoader);

	} else if (signature.compare(
			CppHibernateArrayType::ARRAY_INT.getArrayPrefix()) == 0) {
		//// int array
		return CppHibernateObjectHelper::newJIntPrimitiveArray(env, fieldVal,
				classLoader);

	} else if (signature.compare(
			CppHibernateArrayType::ARRAY_LONG.getArrayPrefix()) == 0) {
		//// long array
		return CppHibernateObjectHelper::newJLongPrimitiveArray(env, fieldVal,
				classLoader);

	} else if (signature.compare(
			CppHibernateArrayType::ARRAY_FLOAT.getArrayPrefix()) == 0) {
		//// float array
		return CppHibernateObjectHelper::newJFloatPrimitiveArray(env, fieldVal,
				classLoader);

	} else if (signature.compare(
			CppHibernateArrayType::ARRAY_DOUBLE.getArrayPrefix()) == 0) {
		//// double array
		return CppHibernateObjectHelper::newJDoublePrimitiveArray(env, fieldVal,
				classLoader);

	}

	return NULL;
}

CppHibernateJObject *CppHibernateObjectHelper::newJBooleanPrimitiveArray(
		JNIEnv *env, jobject fieldVal, AbstractClassLoader *classLoader) {

	jsize arraySize = env->GetArrayLength((jbooleanArray) fieldVal);
	bool *nativeArray = (bool *) env->GetBooleanArrayElements(
			(jbooleanArray) fieldVal, JNI_FALSE);
	CppHibernateObjectHelper::checkAndThrow(env);

	return new CppHibernateJArray<bool>(
			env,
			(unsigned int&) arraySize,
			CppHibernateArrayType::ARRAY_BOOL.getArrayType(),
			nativeArray,
			fieldVal,
			(jclass) CppHibernateObjectHelper::findClassWith(env,
					CppHibernateJBooleanObject::JAVA_LANG_BOOLEAN), classLoader);
}

CppHibernateJObject *CppHibernateObjectHelper::newJBytePrimitiveArray(
		JNIEnv *env, jobject fieldVal, AbstractClassLoader *classLoader) {

	jsize arraySize = env->GetArrayLength((jbyteArray) fieldVal);
	unsigned char *nativeArray = (unsigned char *) env->GetByteArrayElements(
			(jbyteArray) fieldVal, JNI_FALSE);
	CppHibernateObjectHelper::checkAndThrow(env);

	//// TODO add Byte class
	return new CppHibernateJArray<unsigned char>(
			env,
			(unsigned int&) arraySize,
			CppHibernateArrayType::ARRAY_UNSIGNED_CHAR.getArrayType(),
			nativeArray,
			fieldVal,
			(jclass) CppHibernateObjectHelper::findClassWith(env,
					"java/lang/Byte"), classLoader);
}

CppHibernateJObject *CppHibernateObjectHelper::newJCharPrimitiveArray(
		JNIEnv *env, jobject fieldVal, AbstractClassLoader *classLoader) {

	jsize arraySize = env->GetArrayLength((jcharArray) fieldVal);
	char *nativeArray = (char *) env->GetCharArrayElements(
			(jcharArray) fieldVal, JNI_FALSE);
	CppHibernateObjectHelper::checkAndThrow(env);

	//// TODO add Character class
	return new CppHibernateJArray<char>(
			env,
			(unsigned int &) arraySize,
			CppHibernateArrayType::ARRAY_CHAR.getArrayType(),
			nativeArray,
			fieldVal,
			(jclass) CppHibernateObjectHelper::findClassWith(env,
					"java/lang/Character"), classLoader);
}

CppHibernateJObject *CppHibernateObjectHelper::newJShortPrimitiveArray(
		JNIEnv *env, jobject fieldVal, AbstractClassLoader *classLoader) {

	jsize arraySize = env->GetArrayLength((jshortArray) fieldVal);
	short *nativeArray = (short *) env->GetShortArrayElements(
			(jshortArray) fieldVal, JNI_FALSE);
	CppHibernateObjectHelper::checkAndThrow(env);

	//// TODO add Short class
	return new CppHibernateJArray<short>(
			env,
			(unsigned int &) arraySize,
			CppHibernateArrayType::ARRAY_SHORT.getArrayType(),
			nativeArray,
			fieldVal,
			(jclass) CppHibernateObjectHelper::findClassWith(env,
					"java/lang/Short"), classLoader);
}

CppHibernateJObject *CppHibernateObjectHelper::newJIntPrimitiveArray(
		JNIEnv *env, jobject fieldVal, AbstractClassLoader *classLoader) {

	jsize arraySize = env->GetArrayLength((jintArray) fieldVal);
	int *nativeArray = (int *) env->GetIntArrayElements((jintArray) fieldVal,
			JNI_FALSE);
	CppHibernateObjectHelper::checkAndThrow(env);

	return new CppHibernateJArray<int>(
			env,
			(unsigned int &) arraySize,
			CppHibernateArrayType::ARRAY_INT.getArrayType(),
			nativeArray,
			fieldVal,
			(jclass) CppHibernateObjectHelper::findClassWith(env,
					CppHibernateJIntegerObject::JAVA_LANG_INTEGER), classLoader);
}

CppHibernateJObject *CppHibernateObjectHelper::newJLongPrimitiveArray(
		JNIEnv *env, jobject fieldVal, AbstractClassLoader *classLoader) {

	jsize arraySize = env->GetArrayLength((jlongArray) fieldVal);
	long *nativeArray = (long *) env->GetLongArrayElements(
			(jlongArray) fieldVal, JNI_FALSE);
	CppHibernateObjectHelper::checkAndThrow(env);

	return new CppHibernateJArray<long>(
			env,
			(unsigned int &) arraySize,
			CppHibernateArrayType::ARRAY_LONG.getArrayType(),
			nativeArray,
			fieldVal,
			(jclass) CppHibernateObjectHelper::findClassWith(env,
					CppHibernateJLongObject::JAVA_LANG_LONG), classLoader);

}

CppHibernateJObject *CppHibernateObjectHelper::newJFloatPrimitiveArray(
		JNIEnv *env, jobject fieldVal, AbstractClassLoader *classLoader) {

	jsize arraySize = env->GetArrayLength((jfloatArray) fieldVal);
	float *nativeArray = (float *) env->GetFloatArrayElements(
			(jfloatArray) fieldVal, JNI_FALSE);

	CppHibernateObjectHelper::checkAndThrow(env);

	return new CppHibernateJArray<float>(
			env,
			(unsigned int &) arraySize,
			CppHibernateArrayType::ARRAY_FLOAT.getArrayType(),
			nativeArray,
			fieldVal,
			(jclass) CppHibernateObjectHelper::findClassWith(env,
					CppHibernateJFloatObject::JAVA_LANG_FLOAT), classLoader);
}

CppHibernateJObject *CppHibernateObjectHelper::newJDoublePrimitiveArray(
		JNIEnv *env, jobject fieldVal, AbstractClassLoader *classLoader) {

	jsize arraySize = env->GetArrayLength((jdoubleArray) fieldVal);
	double *nativeArray = (double *) env->GetDoubleArrayElements(
			(jdoubleArray) fieldVal, JNI_FALSE);

	CppHibernateObjectHelper::checkAndThrow(env);

	return new CppHibernateJArray<double>(
			env,
			(unsigned int &) arraySize,
			CppHibernateArrayType::ARRAY_DOUBLE.getArrayType(),
			nativeArray,
			fieldVal,
			(jclass) CppHibernateObjectHelper::findClassWith(env,
					CppHibernateJDoubleObject::JAVA_LANG_DOUBLE), classLoader);
}

jobject CppHibernateObjectHelper::findClassWith(JNIEnv *env,
		const char *typeName) {

	jclass jClass = env->FindClass(typeName);
	CppHibernateObjectHelper::checkAndThrow(env);
	jobject cls = env->NewGlobalRef(jClass);
	CppHibernateObjectHelper::checkAndThrow(env);

	return cls;
}

/**
 * Checks if the signature is for array or not. The signature for arrays starts with '['.
 * @param const char *signature Signature to be evaluated.
 * @return bool Returns true if the signature is for an array, false otherwise.
 */
bool CppHibernateObjectHelper::isStartedWith(const char *signature,
		const char *target) {

	std::string extractedPart = CppHibernateObjectHelper::extractStringFrom(
			signature);
	if (std::strncmp(extractedPart.c_str(), target,
			std::strlen(extractedPart.c_str())) == 0) {

		return true;
	}

	return false;
}

/**
 * Extracts a part of string from the specified string.
 * @param const char * Base const char pointer where the extraction is taken place.
 * @param size_t start Starting index of the extraction.
 * @param size_t end Ending index of the extraction.
 * @return const char * Returns the extracted portion of the string.
 * @throw Throws exceptions when the start and/or end parameters are invalid.
 */
std::string CppHibernateObjectHelper::extractStringFrom(const char *name,
		size_t start, size_t end) {

	int len = std::strlen(name);

	if (CppHibernateObjectHelper::isValidRange(start, end, len)) {
		return std::string(name).substr(start, end);
	}
	std::string errorMessage("invalid indices are specified. start: ");
	std::stringstream strStart;
	strStart << start;
	std::stringstream strEnd;
	strEnd << end;
	errorMessage += strStart.str() + " end: ";
	errorMessage += strEnd.str() + ".";
	throw std::out_of_range(errorMessage.c_str());
}

/**
 * Checks if the specified start and end parameters are valid indices or not using the length of the target string.
 * @param size_t start Starting index.
 * @param size_t end  Ending index.
 * @param int len Length of the target string.
 * @return bool Returns true if they are valid indices, false otherwise.
 */
bool CppHibernateObjectHelper::isValidRange(size_t & start, size_t & end,
		int len) {

	if (start < 0) {
		return false;
	}
	if (end > static_cast<unsigned int>(len)) {
		return false;
	}

	return true;
}

/**
 * Throws exceptions when JNI encounters exceptions.
 */
void CppHibernateObjectHelper::throwException() {
	this->env->ExceptionDescribe();
	this->env->Throw(this->env->ExceptionOccurred());
}

/**
 * Checks if the required properties are set correctly or not. Each of the properties can be NULL depending on the object that implements
 * this method.
 * @param JNIEnv* env JNI pointer.
 * @param jobject obj An object representing a Java object.
 * @param jclass objClass An object representing a Java class.
 * @param AbstractClassLoader* classLoader Class loader used to load the class and other classes.
 */
void CppHibernateObjectHelper::checkCommonProperties(JNIEnv *env, jobject obj,
		jclass objClass, AbstractClassLoader *classLoader) {
	if (env == NULL) {
		throw CppHibernateException(
				"env property is NULL. Please set it correctly to call methods on Java objects");
	}
	if (classLoader == NULL) {
		throw CppHibernateException(
				"classLoader property is NULL. Please set it correctly");
	}
}

/**
 * Checks if the required properties are set correctly. This method is used in CppHibernateObjectHelper::newJObjectInstance().
 * @param JNIEnv * env JNI pointer.
 * @param AbstractClassLoader * Class loader.
 * @param const char * className Class name.
 * @throw Throws a exception when all the required properties are not set correctly.
 */
void CppHibernateObjectHelper::checkRequiredProperties(JNIEnv *env,
		AbstractClassLoader *classLoader, const char *signature,
		jobject fieldVal) {
	if (env == NULL || classLoader == NULL
			|| std::strlen(signature) == 0 || fieldVal == NULL) {
		throw CppHibernateException(
				"Please specify the required parameters correctly. All the parameters must not be NULL.");
	}
}

/**
 * Checks if there is a pending exception or not. If so, throws the exception.
 * @param JNIEnv * env JNI pointer.
 */
void CppHibernateObjectHelper::checkAndThrow(JNIEnv *env) {
	if (env->ExceptionCheck()) {
		env->ExceptionDescribe();
		env->Throw(env->ExceptionOccurred());
	}
}

/**
 * Checks if there is an appending exception or not. If so, throws the exception and do nothing otherwise.
 */
void CppHibernateObjectHelper::checkAndThrow() {
	if (this->env->ExceptionCheck()) {
		this->throwException();
	}
}

CppHibernateObjectHelper::~CppHibernateObjectHelper() {

}

}

/* namespace cppHibernate */
