/*
 * CppHibernateMethodInvoker.cpp
 *
 *  Created on: Dec 1, 2011
 *      Author: seiyak
 */

#include <cstring>
#include "CppHibernateMethodInvoker.h"
#include "CppHibernateCommons.h"

namespace cppHibernate {

const char *CppHibernateMethodInvoker::JAVA_METHOD_PARAMETER_PREFIX_SIGNATURE =
		"(";
const char *CppHibernateMethodInvoker::JAVA_METHOD_PARAMETER_SUFFIX_SIGNATURE =
		")";

CppHibernateMethodInvoker::CppHibernateMethodInvoker(JNIEnv *env,
		AbstractClassLoader *classLoader) :
		CppHibernateAccessor(env, classLoader), env(env), classLoader(
				classLoader) {
}

CppHibernateJavaObject CppHibernateMethodInvoker::invoke(jobject obj,
		jclass objClass, const char *methodName, int& numberOfParameters,
		va_list argList) {

	const char *methodSignature = this->getMethodSignature(obj, objClass,
			methodName);

	jmethodID methodId = this->env->GetMethodID(objClass, methodName,
			methodSignature);
	if (methodId == NULL) {
		this->throwException();
	}

	jclass objectClass = this->env->FindClass("java/lang/Object");
	jobjectArray parameters = this->env->NewObjectArray(numberOfParameters,
			objectClass, NULL);
	this->checkAndThrow();

	int i;
	for (i = 0; i < numberOfParameters; i++) {
		CppHibernateCommons *object = va_arg(argList,CppHibernateCommons *);

		this->env->SetObjectArrayElement(parameters, i, object->getObj());
		this->checkAndThrow();
	}

	jclass methodCls = (jclass) this->env->NewGlobalRef(
			this->env->FindClass(
					CppHibernateAccessor::JAVA_LANG_REFLECT_METHOD));
	if (methodCls == NULL) {
		this->throwException();
	}
	jobject method = this->getMethod(methodName, obj, objClass);
	jmethodID invokeId = this->env->GetMethodID(methodCls, "invoke",
			"(Ljava/lang/Object;[Ljava/lang/Object;)Ljava/lang/Object;");
	if (invokeId == NULL) {
		this->throwException();
	}

	jobject rtnObj = this->env->CallObjectMethod(method, invokeId, obj,
			parameters);

	//this->env->DeleteGlobalRef(methods);
	this->env->DeleteGlobalRef(method);
	this->env->DeleteGlobalRef(methodCls);

	this->checkAndThrow();

	if (rtnObj == NULL) {
		return CppHibernateJavaObject(NULL, NULL);
	}

	return CppHibernateJavaObject(this->env->NewGlobalRef(rtnObj),
			(jclass) this->env->NewGlobalRef(this->env->GetObjectClass(rtnObj)));
}

/**
 * Returns the return type of the specified method on the specified class.
 * @param jobject obj Object where the specified method is invoked.
 * @param jclass objClass Class where the specified method is declared.
 * @param const char *methodName Method name to be searched.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
const char *CppHibernateMethodInvoker::getMethodReturnSignature(jobject obj,
		jclass objClass, const char *methodName) {

	const char *methodSignature = this->searchTypeFrom(obj, objClass,
			methodName);

	std::string methodSig(methodSignature);
	size_t pos = methodSig.find_first_of(
			CppHibernateMethodInvoker::JAVA_METHOD_PARAMETER_SUFFIX_SIGNATURE);
	if (pos == std::string::npos) {
		std::string errorMessage(
				"the method signature is not formatted correctly, ");
		errorMessage += methodSignature;
		throw CppHibernateException(errorMessage.c_str());
	}

	return std::string(methodSig.substr(pos + 1, methodSig.size())).c_str();
}

/**
 * Gets the specified method parameters' signature.
 * @param jobject obj Object where the specified method is invoked.
 * @param jclass objClass Class where the specified method is declared.
 * @param const char *methodName Method name to be searched for.
 * @return const char * Returns the signature for the parameters.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
const char *CppHibernateMethodInvoker::getMethodParametersSignature(jobject obj,
		jclass objClass, const char *methodName) {
	const char *methodSignature = this->searchTypeFrom(obj, objClass,
			methodName);

	std::string methodSig(methodSignature);
	size_t pos = methodSig.find_first_of(
			CppHibernateMethodInvoker::JAVA_METHOD_PARAMETER_SUFFIX_SIGNATURE);
	if (pos == std::string::npos) {
		std::string errorMessage(
				"the method signature is not formatted correctly, ");
		errorMessage += methodSignature;
		throw CppHibernateException(errorMessage.c_str());
	}

	if (pos == 1) {
		return "";
	}

	return methodSig.substr(1, pos).c_str();
}

/**
 * Gets the method signature including the return type and the parameters.
 * @param jobject obj Object where the method is invoked.
 * @param jclass objClass Class where the method is declared.
 * @param const char *methodName Method name to be searched for.
 * @return const char * Returns the method signature.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
const char *CppHibernateMethodInvoker::getMethodSignature(jobject obj,
		jclass objClass, const char *methodName) {
	return this->searchTypeFrom(obj, objClass, methodName);
}

/**
 * Searches the specified method's signature including the return type and the parameters.
 * @param jobject obj Object where the specified method is invoked.
 * @param jclass objClass Class where the specified method is declared.
 * @param const char *methodName Method name to be searched for.
 * @return const char * Returns the method signature.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
const char *CppHibernateMethodInvoker::searchTypeFrom(jobject obj,
		jclass objClass, const char *methodName) {

	jobject method = this->getMethod(methodName, obj, objClass);

	jclass methodCls = (jclass) this->env->NewGlobalRef(
			this->env->FindClass(
					CppHibernateAccessor::JAVA_LANG_REFLECT_METHOD));
	std::string returnTypeSignature = this->getReturnType(method, methodCls);
	std::string parametersSignature = this->getParametersType(method,
			methodCls);

	this->env->DeleteGlobalRef(methodCls);
	this->env->DeleteGlobalRef(method);

	std::string methodSignature(parametersSignature);
	methodSignature += std::string(returnTypeSignature);

	return methodSignature.c_str();
}

/**
 * Searches declared methods on the specified class.
 * @param jobject obj Object where the methods are invoked.
 * @param jclass objClass Class where the methods are declared.
 * @return jobject Returns jobject object holding all the declared methods as java.lang.reflect.Method. The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
jobject CppHibernateMethodInvoker::searchDeclaredMethods(jobject obj,
		jclass objClass) {
	jobject classObj = this->callGetClass(obj, objClass);
	jclass classCls = this->env->GetObjectClass(classObj);
	this->checkAndThrow();
	jmethodID getDeclaredMethodsId = this->env->GetMethodID(classCls,
			CppHibernateAccessor::JAVA_LANG_CLASS_GETDECLAREDMETHODS_NAME,
			CppHibernateAccessor::JAVA_LANG_CLASS_GETDECLAREDMETHODS_SIGNATURE);
	if (getDeclaredMethodsId == NULL) {
		this->env->DeleteGlobalRef(classObj);
		this->throwException();
	}

	jobjectArray methods =
			(jobjectArray) (((((((((((this->env->CallObjectMethod(classObj,
					getDeclaredMethodsId))))))))))));
	this->checkAndThrow();
	return this->env->NewGlobalRef(methods);
}

/**
 * Gets the specified method from all the declared methods.
 * @param const char * methodName Method name to be searched for.
 * @param jobject obj java.lang.Class object.
 * @param jclass objClass java.lang.Class class.
 * @return jobject Returns java.lang.reflect.Method object matched with the specified method name. The returned object must be deleted when the job is done.
 * @throw Throws exceptions when JNI encounters exceptions and when the specified method is not found on the class.
 */
jobject CppHibernateMethodInvoker::getMethod(const char *methodName,
		jobject obj, jclass objClass) {

	jobject classObj = this->callGetClass(obj, objClass);
	jclass classCls = this->env->FindClass(
			CppHibernateAccessor::JAVA_LANG_CLASS);
	jmethodID getDeclaredMethodsId =
			this->env->GetMethodID(
					classCls,
					CppHibernateMethodInvoker::JAVA_LANG_CLASS_GETDECLAREDMETHODS_NAME,
					CppHibernateMethodInvoker::JAVA_LANG_CLASS_GETDECLAREDMETHODS_SIGNATURE);
	this->checkAndThrow();
	jobject method = this->getTarget(methodName, classObj, classCls,
			this->env->NewGlobalRef((jobject) getDeclaredMethodsId));
	this->env->DeleteGlobalRef(classObj);
	this->env->DeleteGlobalRef(classCls);
	this->checkAndThrow();

	return method;
}

/**
 * Gets the return type of the specified java.lang.reflect.Method object.
 * @param jobject method java.lang.reflect.Method object.
 * @param jclass methodCls java.lang.reflect.Method class.
 * @return std::string Returns a signature for the return type.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
std::string CppHibernateMethodInvoker::getReturnType(jobject method,
		jclass methodCls) {
	jmethodID getReturnTypeId =
			this->env->GetMethodID(
					methodCls,
					CppHibernateAccessor::JAVA_LANG_REFLECT_METHOD_GETRETURNTYPE_NAME,
					CppHibernateAccessor::JAVA_LANG_REFLECT_METHOD_GETRETURNTYPE_SIGNATURE);
	if (getReturnTypeId == NULL) {
		this->throwException();
	}

	jobject returnType = this->env->CallObjectMethod(method, getReturnTypeId);
	this->checkAndThrow();
	returnType = this->env->NewGlobalRef(returnType);
	std::string returnSignature(
			this->createCorrespondingSignature(
					CppHibernateAccessor::toString(this->env, returnType,
							this->env->GetObjectClass(returnType))));

	this->env->DeleteGlobalRef(returnType);
	return returnSignature;
}

/**
 * Gets the parameter types of the specified java.lang.reflect.Method object.
 * @param jobject method java.lang.reflect.Method object.
 * @param jclass methodCls java.lang.reflect.Method class.
 * @return std::string Returns a signature for the parameter types.
 * @throw Throws exceptions when JNI encounters exceptions.
 */
std::string CppHibernateMethodInvoker::getParametersType(jobject method,
		jclass methodCls) {

	jmethodID getParameterTypesId =
			this->env->GetMethodID(
					methodCls,
					CppHibernateAccessor::JAVA_LANG_REFLECT_METHOD_GETPARAMETERTYPES_NAME,
					CppHibernateAccessor::JAVA_LANG_REFLECT_METHOD_GETPARAMETERTYPES_SIGNATURE);
	if (getParameterTypesId == NULL) {
		this->throwException();
	}

	jobjectArray parameters = (jobjectArray) this->env->CallObjectMethod(method,
			getParameterTypesId);
	this->checkAndThrow();

	int numberOfParameters = this->env->GetArrayLength(parameters);

	std::string parameterStr(
			CppHibernateMethodInvoker::JAVA_METHOD_PARAMETER_PREFIX_SIGNATURE);
	int i;
	for (i = 0; i < numberOfParameters; i++) {
		jobject parameter = this->env->GetObjectArrayElement(parameters, i);
		this->checkAndThrow();
		parameter = this->env->NewGlobalRef(parameter);
		const char *parameterSignature = this->createCorrespondingSignature(
				CppHibernateAccessor::toString(this->env, parameter,
						this->env->GetObjectClass(parameter)));

		parameterStr += std::string(parameterSignature);
		this->env->DeleteGlobalRef(parameter);
	}

	parameterStr +=
			CppHibernateMethodInvoker::JAVA_METHOD_PARAMETER_SUFFIX_SIGNATURE;

	return parameterStr;
}

CppHibernateMethodInvoker::~CppHibernateMethodInvoker() {

}

} /* namespace cppHibernate */
