/*
 * CppHibernateArrayType.h
 *
 *  Created on: Jan 13, 2012
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEARRAYTYPE_H_
#define CPPHIBERNATEARRAYTYPE_H_

namespace cppHibernate {

class CppHibernateArrayType {

private:
	const char *arrayType;
	const char *arrayPrefix;

public:
	CppHibernateArrayType(const char *, const char *);
	static const CppHibernateArrayType ARRAY_BOOL;
	static const CppHibernateArrayType ARRAY_UNSIGNED_CHAR;
	static const CppHibernateArrayType ARRAY_CHAR;
	static const CppHibernateArrayType ARRAY_SHORT;
	static const CppHibernateArrayType ARRAY_INT;
	static const CppHibernateArrayType ARRAY_LONG;
	static const CppHibernateArrayType ARRAY_FLOAT;
	static const CppHibernateArrayType ARRAY_DOUBLE;

	const char *getArrayType() const;
	const char *getArrayPrefix() const;
	virtual ~CppHibernateArrayType();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEARRAYTYPE_H_ */
