/*
 * CppHibernateMatchMode.h
 *
 *  Created on: Jan 13, 2012
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEMATCHMODE_H_
#define CPPHIBERNATEMATCHMODE_H_

namespace cppHibernate {

class CppHibernateMatchMode {

private:
	const char *matchMode;

public:
	static const CppHibernateMatchMode START;
	static const CppHibernateMatchMode ANYWHERE;
	static const CppHibernateMatchMode END;
	static const CppHibernateMatchMode EXACT;
	CppHibernateMatchMode(const char *);
	const char *getMatchMode() const;
	virtual ~CppHibernateMatchMode();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEMATCHMODE_H_ */
