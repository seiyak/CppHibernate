/*
 * CppHibernateMatchMode.cpp
 *
 *  Created on: Jan 13, 2012
 *      Author: seiyak
 */

#include "CppHibernateMatchMode.h"

namespace cppHibernate {

const CppHibernateMatchMode CppHibernateMatchMode::START("START");
const CppHibernateMatchMode CppHibernateMatchMode::ANYWHERE("ANYWHERE");
const CppHibernateMatchMode CppHibernateMatchMode::END("END");
const CppHibernateMatchMode CppHibernateMatchMode::EXACT("EXACT");

CppHibernateMatchMode::CppHibernateMatchMode(const char *matchMode) :
		matchMode(matchMode) {
}

const char *CppHibernateMatchMode::getMatchMode() const {
	return this->matchMode;
}

CppHibernateMatchMode::~CppHibernateMatchMode() {

}

} /* namespace cppHibernate */
