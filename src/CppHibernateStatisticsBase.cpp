/*
 * CppHibernateStatisticsBase.cpp
 *
 *  Created on: Dec 12, 2011
 *      Author: seiyak
 */

#include "CppHibernateStatisticsBase.h"
#include "CppHibernateAccessor.h"

namespace cppHibernate {

const char *CppHibernateStatisticsBase::LONGRETURN_VOIDPARAM_SIGNATURE = "()J";

CppHibernateStatisticsBase::CppHibernateStatisticsBase(JNIEnv *env, jobject obj,
		jclass objClass, AbstractClassLoader *classLoader) :
		CppHibernateCommons(env, obj, objClass, classLoader) {

}

long CppHibernateStatisticsBase::getCount(const char *methodName) {

	jmethodID methodId = this->env->GetMethodID(this->objClass, methodName,
			CppHibernateStatisticsBase::LONGRETURN_VOIDPARAM_SIGNATURE);
	if (methodId == NULL) {
		this->throwException();
	}

	jlong count = this->env->CallLongMethod(this->obj, methodId);
	this->checkAndThrow();
	return count;
}

const char *CppHibernateStatisticsBase::toString() {
	return CppHibernateAccessor::toString(this->env, this->obj, this->objClass);
}

CppHibernateStatisticsBase::~CppHibernateStatisticsBase() {
}

} /* namespace cppHibernate */
