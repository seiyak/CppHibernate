/*
 * CppHibernateArrayType.cpp
 *
 *  Created on: Jan 13, 2012
 *      Author: seiyak
 */

#include "CppHibernateArrayType.h"

namespace cppHibernate {

const CppHibernateArrayType CppHibernateArrayType::ARRAY_BOOL("bool", "[Z");
const CppHibernateArrayType CppHibernateArrayType::ARRAY_UNSIGNED_CHAR(
		"unsigned char", "[B");
const CppHibernateArrayType CppHibernateArrayType::ARRAY_CHAR("char", "[C");
const CppHibernateArrayType CppHibernateArrayType::ARRAY_SHORT("short", "[S");
const CppHibernateArrayType CppHibernateArrayType::ARRAY_INT("int", "[I");
const CppHibernateArrayType CppHibernateArrayType::ARRAY_LONG("long", "[J");
const CppHibernateArrayType CppHibernateArrayType::ARRAY_FLOAT("float", "[F");
const CppHibernateArrayType CppHibernateArrayType::ARRAY_DOUBLE("double", "[D");

CppHibernateArrayType::CppHibernateArrayType(const char *arrayType,
		const char *arrayPrefix) :
		arrayType(arrayType), arrayPrefix(arrayPrefix) {

}

const char *CppHibernateArrayType::getArrayType() const {
	return this->arrayType;
}

const char *CppHibernateArrayType::getArrayPrefix() const {
	return this->arrayPrefix;
}

CppHibernateArrayType::~CppHibernateArrayType() {

}

} /* namespace cppHibernate */
