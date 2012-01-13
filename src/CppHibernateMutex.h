/*
 * CppHibernateMutex.h
 *
 *  Created on: Dec 9, 2011
 *      Author: seiyak
 */

#ifndef CPPHIBERNATEMUTEX_H_
#define CPPHIBERNATEMUTEX_H_

#include <pthread.h>

namespace cppHibernate {

class CppHibernateMutex {

private:
	pthread_mutex_t cppHibernateMutex;
	void setHibernateMutex();
	void checkError(int);
	std::string createErrorMessage(int);

public:
	CppHibernateMutex();
	virtual ~CppHibernateMutex();
};

} /* namespace cppHibernate */
#endif /* CPPHIBERNATEMUTEX_H_ */
