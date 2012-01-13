/*
 * CppHibernateMutex.cpp
 *
 *  Created on: Dec 9, 2011
 *      Author: seiyak
 */

#include <iostream>
#include <errno.h>
#include <string>
#include <cstring>
#include "CppHibernateMutex.h"
#include "CppHibernateException.h"

namespace cppHibernate {

CppHibernateMutex::CppHibernateMutex() {
	this->setHibernateMutex();
}

void CppHibernateMutex::setHibernateMutex() {

	pthread_mutexattr_t cppHibernateMutexAttr;
	this->checkError(pthread_mutexattr_init(&cppHibernateMutexAttr));
	this->checkError(
			pthread_mutexattr_settype(&cppHibernateMutexAttr,
					PTHREAD_MUTEX_ERRORCHECK));
	this->checkError(
			pthread_mutex_init(&(this->cppHibernateMutex),
					&cppHibernateMutexAttr));
	this->checkError(pthread_mutexattr_destroy(&cppHibernateMutexAttr));
	this->checkError(pthread_mutex_lock(&(this->cppHibernateMutex)));

	//std::cout << "locked successfully" << std::endl;

}

void CppHibernateMutex::checkError(int errorNumber) {

	if (errorNumber != 0) {
		throw CppHibernateException(
				this->createErrorMessage(errorNumber).c_str());
	}
}

std::string CppHibernateMutex::createErrorMessage(int errorNumber) {

	//std::cout << "error occurred for: " << std::strerror(errno) << std::endl;
	return std::string(static_cast<const char *>(std::strerror(errno)));

}

CppHibernateMutex::~CppHibernateMutex() {

	int rtn = pthread_mutex_unlock(&(this->cppHibernateMutex));
	//std::cout << "return value should be 0: " << rtn << std::endl;
	pthread_mutex_destroy(&(this->cppHibernateMutex));

	//std::cout << "destroyed successfully" << std::endl;
}

} /* namespace cppHibernate */
