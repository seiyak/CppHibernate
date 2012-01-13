/*
 * CppHibernateAccessor.cpp
 *
 *  Created on: Nov 18, 2011
 *      Author: seiyak
 */

#include <memory>
#include <cstring>
#include "CppHibernateAccessor.h"
#include "CppHibernateObjectHelper.h"
#include "CppHibernateMutex.h"

namespace cppHibernate {

const char *CppHibernateAccessor::JAVA_LANG_CLASS_GETCLASS_NAME = "getClass";
const char *CppHibernateAccessor::JAVA_LANG_CLASS_GETCLASS_SIGNATURE =
		"()Ljava/lang/Class;";
const char *CppHibernateAccessor::JAVA_LANG_CLASS = "java/lang/Class";
const char *CppHibernateAccessor::JAVA_LANG_CLASS_GETDECLAREDMETHODS_NAME =
		"getDeclaredMethods";
const char *CppHibernateAccessor::JAVA_LANG_CLASS_GETDECLAREDMETHODS_SIGNATURE =
		"()[Ljava/lang/reflect/Method;";
const char *CppHibernateAccessor::JAVA_LANG_CLASS_GETSUPERCLASS_NAME =
		"getSuperclass";
const char *CppHibernateAccessor::JAVA_LANG_CLASS_GETSUPERCLASS_SIGNATURE =
		"()Ljava/lang/Class;";
const char *CppHibernateAccessor::JAVA_LANG_REFLECT_METHOD =
		"java/lang/reflect/Method";
const char *CppHibernateAccessor::JAVA_LANG_REFLECT_METHOD_GETNAME_NAME =
		"getName";
const char *CppHibernateAccessor::JAVA_LANG_REFLECT_METHOD_GETNAME_SIGNATURE =
		"()Ljava/lang/String;";
const char *CppHibernateAccessor::JAVA_LANG_REFLECT_METHOD_GETRETURNTYPE_NAME =
		"getReturnType";
const char *CppHibernateAccessor::JAVA_LANG_REFLECT_METHOD_GETRETURNTYPE_SIGNATURE =
		"()Ljava/lang/Class;";
const char *CppHibernateAccessor::JAVA_LANG_REFLECT_METHOD_GETPARAMETERTYPES_NAME =
		"getParameterTypes";
const char *CppHibernateAccessor::JAVA_LANG_REFLECT_METHOD_GETPARAMETERTYPES_SIGNATURE =
		"()[Ljava/lang/Class;";
const char *CppHibernateAccessor::JAVA_LANG_REFLECT_ACCESSIBLEOBJECT_SETACCESSIBLE_NAME =
		"setAccessible";
const char *CppHibernateAccessor::JAVA_LANG_REFLECT_ACCESSIBLEOBJECT_SET_ACCESSIBLE_SIGNATURE =
		"(Z)V";
const char *CppHibernateAccessor::JAVA_LANG_GETNAME_NAME = "getName";
const char *CppHibernateAccessor::JAVA_LANG_GETNAME_SIGNATURE =
		"()Ljava/lang/String;";

CppHibernateAccessor::CppHibernateAccessor(JNIEnv *env,
		AbstractClassLoader *classLoader) :
		env(env), classLoader(classLoader) {

	this->checkCommonProperties(env, NULL, NULL, classLoader);
}

/**
 * Gets the corresponding signature by the specified primitive type using CppHibernateJObject::signatureMap map.
 * @param const char * A key to the corresponding primitive signature.
 * @return const char * Signature.
 */
const char *CppHibernateAccessor::getPrimitiveSignature(
		const char *primitiveType) {

	if (std::strncmp(primitiveType, "boolean", std::strlen(primitiveType))
			== 0) {
		return "Z";
	} else if (std::strncmp(primitiveType, "int", std::strlen(primitiveType))
			== 0) {
		return "I";
	} else if (std::strncmp(primitiveType, "byte", std::strlen(primitiveType))
			== 0) {
		return "B";
	} else if (std::strncmp(primitiveType, "char", std::strlen(primitiveType))
			== 0) {
		return "C";
	} else if (std::strncmp(primitiveType, "short", std::strlen(primitiveType))
			== 0) {
		return "S";
	} else if (std::strncmp(primitiveType, "long", std::strlen(primitiveType))
			== 0) {
		return "J";
	} else if (std::strncmp(primitiveType, "float", std::strlen(primitiveType))
			== 0) {
		return "F";
	} else if (std::strncmp(primitiveType, "double", std::strlen(primitiveType))
			== 0) {
		return "D";
	}

	return primitiveType;
}

/**
 * Creates a signature for the specified type. The signature format is defined on Java specification.
 * @param const char * type Used to create the signature.
 * @return const char * Returns the signature.
 */
const char *CppHibernateAccessor::createObjectSignature(const char *type) {

	std::string signature(type);
	size_t spacePos = signature.find(" ");
	if (spacePos == std::string::npos) {
		return type;
	}

	signature = signature.substr(spacePos + 1, signature.size());
	return this->constructObjectSignature(signature).c_str();
}

/**
 * Constructs a signature for java object followed by the JVM specification.
 * @param std::string & className Used to construct the corresponding signature.
 */
std::string CppHibernateAccessor::constructObjectSignature(
		std::string & className) {
	this->replaceAll(className, ".", "/", 1);

	std::string finalSignature("L");
	finalSignature += className + std::string(";");

	return finalSignature;
}

/**
 * Replaces all the occurrences by another one on a string object.
 * @param std::string& A Reference of string object where the replacement is taken place.
 * @param const char * oldOne An occurrence to be replaced.
 * @param const char * newOne An occurrence to be put.
 * @param size_t howMany The number of characters to be replaced.
 */
void CppHibernateAccessor::replaceAll(std::string& str, const char *oldOne,
		const char *newOne, size_t howMany) {

	std::auto_ptr<CppHibernateMutex> cppHibernateMutex(new CppHibernateMutex);

	size_t pos = str.find_first_of(oldOne);

	while (pos != std::string::npos) {
		str.replace(pos, howMany, newOne);
		pos = str.find_first_of(oldOne, pos + 1);
	}
}

/**
 * Finds the method id for getClass() on a Java class.
 * @param jclass A class where the look up is taken place.
 * @return jobject An object representing the method id. The returned object must be deleted when the job is done.
 */
jobject CppHibernateAccessor::getGetClassId(jclass objClass) {

	jobject methodId = NULL;
	jmethodID getClassId = this->env->GetMethodID(objClass,
			CppHibernateAccessor::JAVA_LANG_CLASS_GETCLASS_NAME,
			CppHibernateAccessor::JAVA_LANG_CLASS_GETCLASS_SIGNATURE);
	if (getClassId != NULL) {

		methodId = this->env->NewGlobalRef((jobject) getClassId);
		if (this->env->ExceptionCheck()) {
			this->throwException();
		}
	} else {
		this->throwException();
	}

	return methodId;
}

/**
 * Calls getClass() method on the specified object.
 * @param jobject obj An object representing a Java object.
 * @param jclass objClass An object representing a Java class.
 * @return jobject Returns an object representing the java.lang.Class class as the result of the method call. The returned object must be deleted
 * when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
jobject CppHibernateAccessor::callGetClass(jobject obj, jclass objClass) {

	jobject getClassId = this->getGetClassId(objClass);
	jobject classObj = NULL;

	if (getClassId != NULL) {
		classObj = this->env->NewGlobalRef(
				this->env->CallObjectMethod(obj, (jmethodID) getClassId));
		this->env->DeleteGlobalRef(getClassId);
		this->checkAndThrow();
	} else {
		this->env->DeleteGlobalRef(getClassId);
		this->throwException();
	}

	return classObj;
}

/**
 * Calls toString() method on the specified Java object and Java class.
 * @param jobject obj An object representing a Java object.
 * @param jclass objClass An object representing a Java class.
 * @return const char * String representation of the specified object and class.
 * @throw Throws exceptions when JNI encounters excepetions.
 */
const char *CppHibernateAccessor::toString(JNIEnv *env, jobject obj,
		jclass objClass) {

	std::auto_ptr<CppHibernateMutex> cppHibernateMutex(new CppHibernateMutex);

	jobject str = NULL;

	if (obj == NULL || objClass == NULL) {
		throw CppHibernateException(
				"invalid parameters, obj and/or objClass are NULL, are passed to CppHibernateAccessor::toString() method");
	}

	jmethodID toStringId = env->GetMethodID(objClass, "toString",
			"()Ljava/lang/String;");

	if (toStringId != NULL) {
		str = env->CallObjectMethod(obj, toStringId);
		if (str == NULL) {
			env->Throw(env->ExceptionOccurred());
		}
	} else {
		env->Throw(env->ExceptionOccurred());
	}

	return CppHibernateAccessor::copyStringFrom(env,
			(jstring) (((((((str))))))));
}

/**
 * Copies a string representation from the specified jstring object.
 * @param JNIEnv* env JNI pointer.
 * @param jstring str A string object to be copied.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
const char *CppHibernateAccessor::copyStringFrom(JNIEnv *env, jstring str) {

	std::auto_ptr<CppHibernateMutex> cppHibernateMutex(new CppHibernateMutex);

	if (str == NULL) {
		return "";
	}
	const char *strVal = env->GetStringUTFChars(str, JNI_FALSE);
	if (env->ExceptionCheck()) {
		env->ExceptionDescribe();
		env->Throw(env->ExceptionOccurred());
	}
	size_t len = std::strlen(strVal);
	char *dest = new char[len + 1];
	std::strncpy(dest, strVal, len);
	dest[len] = '\0';
	const char *val = dest;
	env->ReleaseStringUTFChars(str, strVal);

	return val;
}

/**
 * Wrapper method of CppHibernateObjectHelper::isStartedWith() method.
 */
bool CppHibernateAccessor::isStartedWith(const char *signature,
		const char *target) {
	std::auto_ptr<CppHibernateMutex> cppHibernateMutex(new CppHibernateMutex);
	return CppHibernateObjectHelper::isStartedWith(signature, target);
}

/**
 * Creates a corresponding signature for the specified typeName following Java Specification.
 * @param const char *typeName Type name to be used to create the corresponding signature.
 * @return const char * Returns the corresponding signature.
 * @throw Throws an exception when the specified type name is an array. Currently the type of array is not supported on CppHibernate.
 */
const char *CppHibernateAccessor::createCorrespondingSignature(
		const char *typeName) {
	const char *primitiveSignature = this->getPrimitiveSignature(typeName);

	if (this->containArrayPrefix(typeName)) {
		return this->createArraySignature(typeName);
	}

	if (std::strlen(primitiveSignature) == 0) {
		return "";
	}
	if (std::strncmp("void", primitiveSignature, std::strlen("void")) == 0) {
		return "V";
	}
	if (std::strlen(primitiveSignature) > 1) {
		return this->createObjectSignature(typeName);
	}

	return this->getPrimitiveSignature(typeName);
}

/**
 * Checks if the specified type contains the array prefix, '[' or not.
 * @param const char *type Type to be examined.
 * @return bool Returns true if the specified type contains the array prefix, false otherwise.
 */
bool CppHibernateAccessor::containArrayPrefix(const char *type) {

	std::string strType(type);
	if (strType.find("[") == std::string::npos) {
		return false;
	}

	return true;
}

/**
 * Creates a signature for the specified array type.
 * @param const char *type Type to be used to create an array type signature.
 * @return const char * Returns the array type signature.
 */
const char *CppHibernateAccessor::createArraySignature(const char *type) {

	size_t pos = std::string(type).find("[");
	std::string strType = std::string(type).substr(pos,
			(std::strlen(type) - pos));
	if (strType.size() == 2) {
		return strType.c_str();
	}

	this->replaceAll(strType, ".", "/", 1);
	return strType.c_str();
}

/**
 * Searches the target field or method up to the top class which is java.lang.Object.
 * @param const char *targetName Field name or method name to be searched.
 * @param jobject classObj java.lang.Class object,
 * @param jclass classObjClass java.lang.Class class.
 * @param jobject methodId Method id for java.lang.Class.getDeclaredFields or java.lang.Class.getDeclaredMethods.
 * @return Returns the target field object or method object. The return ed object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions and the target field or method is not found.
 */
jobject CppHibernateAccessor::getTarget(const char *targetName,
		jobject classObj, jclass classObjClass, jobject methodId) {

	jobject targetObj = classObj;
	jmethodID getSuperclassId = this->env->GetMethodID(classObjClass,
			CppHibernateAccessor::JAVA_LANG_CLASS_GETSUPERCLASS_NAME,
			CppHibernateAccessor::JAVA_LANG_CLASS_GETSUPERCLASS_SIGNATURE);
	this->checkAndThrow();
	int i;
	while (1) {

		jobjectArray candidates = (jobjectArray) this->env->CallObjectMethod(
				targetObj, (jmethodID) methodId);
		this->checkAndThrow();
		int size = this->env->GetArrayLength(candidates);

		for (i = 0; i < size; i++) {
			jobject candidate = this->env->GetObjectArrayElement(candidates, i);
			this->checkAndThrow();

			jmethodID getNameId = this->env->GetMethodID(
					this->env->GetObjectClass(candidate),
					CppHibernateAccessor::JAVA_LANG_GETNAME_NAME,
					CppHibernateAccessor::JAVA_LANG_GETNAME_SIGNATURE);
			jstring name = (jstring) this->env->CallObjectMethod(candidate,
					getNameId);
			this->checkAndThrow();
			const char *nameStr = this->env->GetStringUTFChars(name, JNI_FALSE);

			if (std::strncmp(targetName, nameStr, std::strlen(targetName))
					== 0) {

				this->env->ReleaseStringUTFChars(name, nameStr);
				this->env->DeleteGlobalRef(methodId);

				jmethodID setAccessibleId =
						this->env->GetMethodID(
								this->env->GetObjectClass(candidate),
								CppHibernateAccessor::JAVA_LANG_REFLECT_ACCESSIBLEOBJECT_SETACCESSIBLE_NAME,
								CppHibernateAccessor::JAVA_LANG_REFLECT_ACCESSIBLEOBJECT_SET_ACCESSIBLE_SIGNATURE);
				this->checkAndThrow();
				this->env->CallVoidMethod(candidate, setAccessibleId, JNI_TRUE);

				return this->env->NewGlobalRef(candidate);
			}

			this->env->ReleaseStringUTFChars(name, nameStr);
			this->env->DeleteLocalRef(candidate);
		}

		this->env->DeleteLocalRef(candidates);

		targetObj = this->env->CallObjectMethod(targetObj, getSuperclassId);
		this->checkAndThrow();
		if (targetObj == NULL) {

			this->env->DeleteGlobalRef(classObj);
			this->env->DeleteGlobalRef(classObjClass);
			this->env->DeleteGlobalRef(methodId);

			std::string errorMessage(
					"could not find the specified field/method, ");
			errorMessage += targetName;
			errorMessage += " in the class hierarchy.";
			throw CppHibernateException(errorMessage.c_str());
		}
	}

	return NULL;
}

/**
 * Checks if the required properties are set.
 * @param JNIEnv * JNI pointer. This property must be set to use this class.
 * @param jobject obj An object representing a Java class. In this class, it's NULL.
 * @param jclass objClass A class representing a Java class. In this class, it's NULL.
 * @param AbstractClassLoader * classLoader Class loader used to load classes. This property must be set to use this class.
 * @throw Throws exception when JNI encounters exceptions.
 */
void CppHibernateAccessor::checkCommonProperties(JNIEnv *env, jobject obj,
		jclass objClass, AbstractClassLoader *classLoader) {
	if (env == NULL || classLoader == NULL) {
		throw CppHibernateException(
				"Please set the required properties to use CppHibernateAccessor class");
	}
}

/**
 * Throws exceptions when JNI encounters exceptions.
 */
void CppHibernateAccessor::throwException() {
	this->env->ExceptionDescribe();
	this->env->Throw(this->env->ExceptionOccurred());
}

/**
 * Checks if there is an appending exception or not. If so, throws the exception and do nothing otherwise.
 */
void CppHibernateAccessor::checkAndThrow() {
	if (this->env->ExceptionCheck()) {
		this->throwException();
	}
}

CppHibernateAccessor::~CppHibernateAccessor() {

}

}

/* namespace cppHibernate */
