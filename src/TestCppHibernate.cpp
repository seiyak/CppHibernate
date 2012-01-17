/*
 * TestCppHibernate.cpp
 *
 *  Created on: Nov 3, 2011
 *      Author: apple
 */

#define BOOST_TEST_MODULE TestCppHibernate

#include <new>

#include <boost/test/included/unit_test.hpp>
#include "CppHibernate.h"
#include "AbstractClassLoader.h"
#include "URLClassLoader.h"
#include "CppHibernateJVMConfiguration.h"
#include "CppHibernateJVMException.h"
#include "CppHibernateSessionFactory.h"
#include "CppHibernateSession.h"
#include "CppHibernateConnection.h"
#include "CppHibernateObjectHelper.h"
#include "CppHibernateJObject.h"
#include "CppHibernateJBooleanObject.h"
#include "CppHibernateJStringObject.h"
#include "CppHibernateJFloatObject.h"
#include "CppHibernateJDoubleObject.h"
#include "CppHibernateJLongObject.h"
#include "CppHibernateJCollectionObject.h"
#include "CppHibernateJArray.h"
#include "CppHibernateJMapObject.h"
#include "CppHibernateJIteratorObject.h"
#include "CppHibernateMethodInvoker.h"
#include "CppHibernateCriteria.h"
#include "CppHibernateQuery.h"
#include "CppHibernateSessionStatistics.h"
#include "CppHibernateStatistics.h"
#include "CppHibernateCollectionStatistics.h"
#include "CppHibernateEntityStatistics.h"
#include "CppHibernateQueryStatistics.h"
#include "CppHibernateSecondLevelCacheStatistics.h"

using namespace cppHibernate;

const char *ROOT_CLASS_PATH = "/home/seiyak/Videos/C++Hibernate/src";
const char *HIBERNATE_LIB_LOCATION = "/home/seiyak/Desktop/HibernateLibs/";

struct FixtureCppHibernate {
	AbstractClassLoader *abstractClassLoader;

	FixtureCppHibernate() {
		abstractClassLoader = new AbstractClassLoader();
	}

	~FixtureCppHibernate() {
		delete abstractClassLoader;
	}
};

BOOST_FIXTURE_TEST_SUITE(cppHibernate,FixtureCppHibernate)

//BOOST_AUTO_TEST_CASE(testFindJars) {
//	std::string jarPath1("/home/google");
//	BOOST_REQUIRE_THROW(abstractClassLoader->findJars(jarPath1),CppHibernateIOException);
//
//	std::string jarPath2("/home/seiyak/Desktop/HibernateLibs");
//	int len = abstractClassLoader->findJars(jarPath2);
//	BOOST_TEST_MESSAGE("size is: " << len);
//
//	BOOST_REQUIRE_EQUAL(12,len);
//}
//
//BOOST_AUTO_TEST_CASE(testGet) {
//
//	std::string jarPath("/home/seiyak/Desktop/HibernateLibs");
//	int len = abstractClassLoader->findJars(jarPath);
//
//	BOOST_REQUIRE_NO_THROW(abstractClassLoader->get(0));
//	BOOST_REQUIRE_NO_THROW(abstractClassLoader->get(len - 1));
//	BOOST_REQUIRE_THROW(abstractClassLoader->get(-1),CppHibernateIndexException);
//	BOOST_REQUIRE_THROW(abstractClassLoader->get(len),CppHibernateIndexException);
//}

////TODO need to think how to keep unit tests related to JNI alive here.
////Right now, need to pick one test case but not all of them.

BOOST_AUTO_TEST_CASE(testAbstractClassLoader) {
//	JavaVMOption options[2];
//	JNIEnv *env;
//	JavaVM *jvm;
//	JavaVMInitArgs vm_args;
//	long status;
//	jclass cls;
//	jmethodID mid;
//
//	options[0].optionString = "-Djava.class.path=/home/seiyak/Videos/C++Hibernate/src";
//	options[1].optionString = "-verbose:class";
//	std::memset(&vm_args,0,sizeof(vm_args));
//
//	vm_args.version = JNI_VERSION_1_6;
//	vm_args.nOptions = 2;
//	vm_args.options = options;
//	status = JNI_CreateJavaVM(&jvm,(void**)&env,&vm_args);
//
//	if(status != JNI_ERR) {
//		std::cout << "successfully created javaVM" << std::endl;
//
//		AbstractClassLoader *classLoader = new AbstractClassLoader(env);
//
//		//// createFileFrom()
//		BOOST_TEST_MESSAGE("about to call createFileFrom() method");
//		jobject file = classLoader->createFileFrom("/home/seiyak/Desktop/HibernateLibs/hibernate3.jar");
//		BOOST_TEST_MESSAGE("got file object");
//		BOOST_REQUIRE(file != NULL);
//		env->DeleteGlobalRef(file);
//
//		jobject file2 = classLoader->createFileFrom("/invalid/path/sample");
//		BOOST_REQUIRE(file2 == NULL);
//		////
//
//		//// createURIFrom()
//		jobject file3 = classLoader->createFileFrom("/home/seiyak/Desktop/HibernateLibs/hibernate3.jar");
//		jobject uri1 = classLoader->createURIFrom(file3);
//		BOOST_REQUIRE(uri1 != NULL);
//		env->DeleteGlobalRef(file3);
//		env->DeleteGlobalRef(uri1);
//
//		jclass fileClass = env->FindClass("java/io/File");
//		jmethodID fileCtorId = env->GetMethodID(fileClass,"<init>","(Ljava/lang/String;)V");
//		jstring pathName = env->NewStringUTF("");
//		jobject fileObj = env->NewObject(fileClass,fileCtorId,pathName);
//		jobject uri2 = classLoader->createURIFrom(fileObj),CppHibernateClassLoaderException;
//		BOOST_REQUIRE(uri2 != NULL);
//		if(fileObj != NULL) {
//			env->DeleteGlobalRef(fileObj);
//		}
//		if(uri2 != NULL) {
//			env->DeleteGlobalRef(uri2);
//		}
//		env->DeleteLocalRef(pathName);
//		////
//
//		//// createURLFrom()
//		jobject file4 = classLoader->createFileFrom("/home/seiyak/Desktop/HibernateLibs/hibernate3.jar");
//		jobject uri4 = classLoader->createURIFrom(file4);
//		jobject url4 = classLoader->createURLFrom(uri4);
//		BOOST_REQUIRE(url4 != NULL);
//		env->DeleteGlobalRef(file4);
//		env->DeleteGlobalRef(uri4);
//		env->DeleteLocalRef(url4);
//		////
//
//		//// createURLsFrom()
//		jobject file5 = classLoader->createFileFrom("/home/seiyak/Desktop/HibernateLibs/hibernate3.jar");
//		jobject uri5 = classLoader->createURIFrom(file5);
//		jobject url5 = classLoader->createURLFrom(uri5);
//		jobject urls5 = classLoader->createURLsFrom(url5);
//		BOOST_REQUIRE(urls5 != NULL);
//		jsize s = env->GetArrayLength((jarray)urls5);
//		BOOST_TEST_MESSAGE("url array size is: " << s);
//		BOOST_REQUIRE_EQUAL(1,s);
//		jobject u1 = env->GetObjectArrayElement((jobjectArray)urls5,0);
//		BOOST_REQUIRE(u1 != NULL);
//		jclass urlClass = env->FindClass("java/net/URL");
//		jmethodID getPathId = env->GetMethodID(urlClass,"getPath","()Ljava/lang/String;");
//		jstring pathPart = (jstring)env->CallObjectMethod(u1,getPathId);
//		const char *pathChar = env->GetStringUTFChars(pathPart,JNI_FALSE);
//		BOOST_REQUIRE_EQUAL(pathChar,"/home/seiyak/Desktop/HibernateLibs/hibernate3.jar");
//		env->ReleaseStringUTFChars(pathPart,pathChar);
//		jmethodID getProtocolId = env->GetMethodID(urlClass,"getProtocol","()Ljava/lang/String;");
//		jstring protocolPart = (jstring)env->CallObjectMethod(u1,getProtocolId);
//		const char *protocolChar = env->GetStringUTFChars(protocolPart,JNI_FALSE);
//		BOOST_REQUIRE_EQUAL(protocolChar,"file");
//		env->ReleaseStringUTFChars(protocolPart,protocolChar);
//		env->DeleteGlobalRef(file5);
//		env->DeleteGlobalRef(uri5);
//		env->DeleteLocalRef(url5);
//		env->DeleteGlobalRef(urls5);
//
//		jobject urls6 = classLoader->createURLsFrom(NULL);
//		BOOST_REQUIRE(urls6 == NULL);
//
//		BOOST_REQUIRE_EQUAL(0,classLoader->size());
//
//		////TODO need to use CppHibernateClassLoaderException
//		jobject jobj6 = classLoader->createURLsFrom();
//		BOOST_REQUIRE(jobj6 == NULL);
//
//		std::string path7("/home/seiyak/Desktop/HibernateLibs");
//		int s7 = classLoader->findJars(path7);
//		BOOST_REQUIRE_EQUAL(13,s7);
//		jobject jobj7 = NULL;
//		BOOST_REQUIRE_NO_THROW(jobj7 = classLoader->createURLsFrom());
//		env->DeleteGlobalRef(jobj7);
//
//		URLClassLoader *urlLoader = new URLClassLoader(env,"/home/seiyak/Desktop/HibernateLibs");
//		BOOST_REQUIRE_EQUAL(urlLoader->size(),13);
//		BOOST_REQUIRE(urlLoader->getClassLoader() != NULL);
//		////
//
//		//// findClass()
//		jobject classObj8;
//		BOOST_REQUIRE_NO_THROW(classObj8 = urlLoader->findClass("org.hibernate.cfg.Configuration"));
//		BOOST_REQUIRE(classObj8 != NULL);
//		env->DeleteGlobalRef(classObj8);
//		////
//
//		BOOST_REQUIRE(urlLoader->getClassLoader() != NULL);
//		BOOST_REQUIRE(urlLoader->getClassLoaderClass() != NULL);
//		BOOST_TEST_MESSAGE("classLoader is: " << urlLoader->getClassLoader() << " classLoaderClass is: " << urlLoader->getClassLoaderClass());
//		BOOST_TEST_MESSAGE("again classLoader is: " << urlLoader->getClassLoader() << " classLoaderClass is: " << urlLoader->getClassLoaderClass());
//		delete urlLoader;
//		delete classLoader;
//	}
//
//	if(jvm != NULL) {
//		jvm->DestroyJavaVM();
//	}
}

BOOST_AUTO_TEST_CASE(testJVMConfiguration) {
//	CppHibernateJVMConfiguration *configuration;
//	BOOST_REQUIRE_NO_THROW(configuration = new CppHibernateJVMConfiguration("/home/seiyak/Videos/C++Hibernate/src"));
//	jclass cls;
//	BOOST_REQUIRE_NO_THROW(cls = configuration->getJNIEnv()->FindClass("java/lang/String"));
//	BOOST_REQUIRE(cls != NULL);
//
//	delete configuration;
}

BOOST_AUTO_TEST_CASE(testCppHibernateConfigurationWithDefaultPath) {
//	CppHibernateJVMConfiguration *configuration = new CppHibernateJVMConfiguration("/home/seiyak/Videos/C++Hibernate/src");
//	AbstractClassLoader *loader = new URLClassLoader(configuration->getJNIEnv(),"/home/seiyak/Desktop/HibernateLibs");
//	CppHibernate *hibernate;
//	BOOST_REQUIRE_NO_THROW(hibernate = new CppHibernate(configuration,loader));
//	BOOST_REQUIRE(hibernate->getConfiguration() == NULL);
//	BOOST_REQUIRE(hibernate->getSessionFactory() != NULL);
//
//	delete loader;
//	delete hibernate;
//	delete configuration;
}

BOOST_AUTO_TEST_CASE(testCppHiberanteConfigurationWithSpecifiedPath) {
//	CppHibernateJVMConfiguration *configuration = new CppHibernateJVMConfiguration("/home/seiyak/Videos/C++Hibernate/src");
//	AbstractClassLoader *loader = new URLClassLoader(configuration->getJNIEnv(),"/home/seiyak/Desktop/HibernateLibs");
//	CppHibernate *hibernate;
//	BOOST_REQUIRE_THROW(hibernate = new CppHibernate(NULL,NULL),CppHibernateException);
//	BOOST_REQUIRE_THROW(hibernate = new CppHibernate(configuration,NULL),CppHibernateException);
//	BOOST_REQUIRE_THROW(hibernate = new CppHibernate(NULL,loader),CppHibernateException);
//	BOOST_REQUIRE_THROW(hibernate = new CppHibernate(configuration,loader,"some/wrong/path"),CppHibernateException);
//	BOOST_REQUIRE_THROW(hibernate = new CppHibernate(configuration,loader,"/home/seiyak/Videos/C++Hibernate/src"),CppHibernateException);
//	hibernate = new CppHibernate(configuration,loader,"/home/seiyak/Videos/C++Hibernate/src/hibernate.cfg.xml");
//	BOOST_REQUIRE(hibernate->getConfiguration() == NULL);
//	BOOST_REQUIRE(hibernate->getSessionFactory() != NULL);
//
//	delete loader;
//	delete hibernate;
//	delete configuration;
}

BOOST_AUTO_TEST_CASE(testCreateClassName) {
//	CppHibernateJVMConfiguration *configuration = new CppHibernateJVMConfiguration("/home/seiyak/Videos/C++Hibernate/src");
//	AbstractClassLoader *loader = new URLClassLoader(configuration->getJNIEnv(),"/home/seiyak/Desktop/HibernateLibs");
//
//	CppHibernateObjectHelper *helper;
//	BOOST_REQUIRE_THROW(helper = new CppHibernateObjectHelper(NULL,loader),CppHibernateException);
//	BOOST_REQUIRE_THROW(helper = new CppHibernateObjectHelper(configuration->getJNIEnv(),NULL),CppHibernateException);
//	BOOST_REQUIRE_THROW(helper = new CppHibernateObjectHelper(NULL,NULL),CppHibernateException);
//	BOOST_REQUIRE_NO_THROW(helper = new CppHibernateObjectHelper(configuration->getJNIEnv(),loader));
//	CppHibernateJObject *jObject;
//	BOOST_REQUIRE_NO_THROW(jObject = helper->createJObjectWith("org/hibernateDomain/Event2"));
//	BOOST_REQUIRE(jObject != NULL);
//
//	delete jObject;
//	delete helper;
//	delete loader;
//	delete configuration;
}

BOOST_AUTO_TEST_CASE(testJBooleanObject) {
//	CppHibernateJVMConfiguration *configuration = new CppHibernateJVMConfiguration(ROOT_CLASS_PATH);
//	AbstractClassLoader *loader = new URLClassLoader(configuration->getJNIEnv(),HIBERNATE_LIB_LOCATION);
//
//	CppHibernateObjectHelper *helper = new CppHibernateObjectHelper(configuration->getJNIEnv(),loader);
//	CppHibernateJBooleanObject *bObject1 = NULL;
//	bObject1 = helper->createJBooleanObjectWith();
//	BOOST_REQUIRE(bObject1 != NULL);
//	BOOST_REQUIRE(std::strcmp(bObject1->toString(),"false") == 0);
//	BOOST_REQUIRE(std::strcmp(bObject1->toString(),"true") != 0);
//	BOOST_REQUIRE(bObject1->getVal() == false);
//	BOOST_REQUIRE_NO_THROW(bObject1->setVal(true));
//	BOOST_REQUIRE(bObject1->getVal() == true);
//	BOOST_REQUIRE(std::strcmp(bObject1->toString(),"true") == 0);
//	BOOST_REQUIRE(std::strcmp(bObject1->toString(),"false") != 0);
//
//	CppHibernateJBooleanObject *bObject2 = NULL;
//	BOOST_REQUIRE_NO_THROW(bObject2 = helper->createJBooleanObjectWith(false));
//	BOOST_REQUIRE(bObject2 != NULL);
//	BOOST_REQUIRE(std::strcmp(bObject2->toString(),"true") != 0);
//	BOOST_REQUIRE(std::strcmp(bObject2->toString(),"false") == 0);
//	BOOST_REQUIRE(bObject2->getVal() == false);
//	BOOST_REQUIRE_NO_THROW(bObject2->setVal(true));
//	BOOST_REQUIRE(bObject2->getVal() == true);
//	BOOST_REQUIRE(std::strcmp(bObject2->toString(),"true") == 0);
//	BOOST_REQUIRE(std::strcmp(bObject2->toString(),"false") != 0);
//
//	BOOST_REQUIRE(bObject1->equals(bObject2) == true);
//
//	CppHibernateJBooleanObject *bObject3 = NULL;
//	BOOST_REQUIRE_NO_THROW(bObject3 = helper->createJBooleanObjectWith(true));
//	BOOST_REQUIRE(bObject3 != NULL);
//	BOOST_REQUIRE(std::strcmp(bObject3->toString(),"true") == 0);
//	BOOST_REQUIRE(std::strcmp(bObject3->toString(),"false") != 0);
//	BOOST_REQUIRE(bObject3->getVal() == true);
//	BOOST_REQUIRE_NO_THROW(bObject3->setVal(false));
//	BOOST_REQUIRE(bObject3->getVal() == false);
//	BOOST_REQUIRE(std::strcmp(bObject3->toString(),"true") != 0);
//	BOOST_REQUIRE(std::strcmp(bObject3->toString(),"false") == 0);
//
//	BOOST_REQUIRE(bObject3->equals(bObject2) == false);
//	BOOST_REQUIRE(bObject3->equals(bObject1) == false);
//	BOOST_REQUIRE(bObject2->equals(bObject1) == true);
//	BOOST_REQUIRE(bObject3->equals(bObject3) == true);
//
//	delete bObject1;
//	delete bObject2;
//	delete bObject3;
//
//	delete helper;
//	delete loader;
//	delete configuration;
}

BOOST_AUTO_TEST_CASE(testJStringObject) {
//	CppHibernateJVMConfiguration *configuration = new CppHibernateJVMConfiguration(ROOT_CLASS_PATH);
//	AbstractClassLoader *loader = new URLClassLoader(configuration->getJNIEnv(),HIBERNATE_LIB_LOCATION);
//	CppHibernateObjectHelper *helper = new CppHibernateObjectHelper(configuration->getJNIEnv(),loader);
//	CppHibernateJStringObject *str1 = NULL;
//
//	bool b = 0;
//	BOOST_REQUIRE_NO_THROW(str1 = helper->createJStringObjectWith(b));
//	BOOST_REQUIRE(str1 != NULL);
//	const char *bVal = str1->getVal();
//	BOOST_REQUIRE(std::strncmp(bVal,"0",1) == 0);
//	BOOST_REQUIRE_NO_THROW(str1->getVal());
//	BOOST_REQUIRE_NO_THROW(str1->setVal("newValue1"));
//	const char *newVal1 = str1->getVal();
//	BOOST_REQUIRE(std::strncmp(newVal1,"newValue1",std::strlen("newValue1")) == 0);
//
//	CppHibernateJStringObject *str2 = NULL;
//	BOOST_REQUIRE_NO_THROW(str2 = helper->createJStringObjectWith("google"));
//	BOOST_REQUIRE(str2 != NULL);
//	const char *str2Val = str2->getVal();
//	BOOST_REQUIRE(std::strncmp("google",str2Val,std::strlen("google")) == 0);
//
//	CppHibernateJStringObject *str3 = NULL;
//	BOOST_REQUIRE_NO_THROW(str3 = helper->createJStringObjectWith("yahoo"));
//	const char *str3Val = str3->getVal();
//	BOOST_REQUIRE(std::strncmp(str3Val,"yahoo",std::strlen(str3Val)) == 0);
//	BOOST_REQUIRE_NO_THROW(str3->getVal());
//
//	CppHibernateJStringObject *str4 = helper->createJStringObjectWith("apple");
//	CppHibernateJStringObject *str5 = helper->createJStringObjectWith("ms");
//	CppHibernateJStringObject& str6 = str4->concat(str5);
//	const char *con1 = str6.getVal();
//	BOOST_REQUIRE(std::strncmp(con1,"applems",std::strlen("applems")) == 0);
//	BOOST_REQUIRE_NO_THROW(str6.setVal("another"));
//	str6.concat("Sample");
//	const char *str6Val = str6.getVal();
//	BOOST_REQUIRE(std::strncmp(str6Val,"anotherSample",std::strlen(str6Val)) == 0);
//
//	delete str1;
//	delete str2;
//	delete str3;
//	delete str4;
//	delete str5;
//	delete helper;
//	delete loader;
//	delete configuration;
}

BOOST_AUTO_TEST_CASE(testCppHibernateObjects) {
//	CppHibernateJVMConfiguration configuration(ROOT_CLASS_PATH);
//	AbstractClassLoader *loader = new URLClassLoader(configuration.getJNIEnv(),HIBERNATE_LIB_LOCATION);
//	CppHibernateObjectHelper *helper = new CppHibernateObjectHelper(configuration.getJNIEnv(),loader);
//
//	CppHibernateJObject *obj = helper->createJObjectWith("org.hibernateDomain.Event2");
//	BOOST_REQUIRE(std::strncmp("org.hibernateDomain.Event",obj->getCanonicalName(),std::strlen("org.hibernateDomain.Event")) == 0);
//	CppHibernateJStringObject *str = helper->createJStringObjectWith("google");
//	BOOST_REQUIRE(std::strncmp("java.lang.String",str->getCanonicalName(),std::strlen("java.lang.String")) == 0);
//	BOOST_REQUIRE_NO_THROW(obj->setVal("title",str));
//	CppHibernateJStringObject *rtnStr1 = NULL;
//	BOOST_REQUIRE_NO_THROW(rtnStr1 = dynamic_cast<CppHibernateJStringObject *>(obj->getVal("title")));
//	BOOST_REQUIRE(std::strncmp("google",rtnStr1->getVal(),std::strlen("google")) == 0);
//
//	CppHibernateJIntegerObject *intObjV = helper->createJIntegerObjectWith(100);
//	BOOST_REQUIRE_NO_THROW(obj->setVal("intObjV",intObjV));
//	delete intObjV;
//	CppHibernateJIntegerObject *intObjVRes = dynamic_cast<CppHibernateJIntegerObject *>(obj->getVal("intObjV"));
//	BOOST_REQUIRE(100 == intObjVRes->getVal());
//	delete intObjVRes;
//
//	CppHibernateJIntegerObject *intV = helper->createJIntegerObjectWith(300);
//	BOOST_REQUIRE_NO_THROW(obj->setVal("v",intV));
//	delete intV;
//	CppHibernateJIntegerObject *intVRes = dynamic_cast<CppHibernateJIntegerObject *>(obj->getVal("v"));
//	BOOST_REQUIRE(300 == intVRes->getVal());
//	delete intVRes;
//
//	CppHibernateJStringObject *strV = helper->createJStringObjectWith("parent");
//	BOOST_REQUIRE_NO_THROW(obj->setVal("strV",strV));
//	delete strV;
//	CppHibernateJStringObject *strVRes = dynamic_cast<CppHibernateJStringObject *>(obj->getVal("strV"));
//	BOOST_REQUIRE(std::strncmp("parent",strVRes->getVal(),std::strlen("parent")) == 0);
//	delete strVRes;
//
//	CppHibernateJStringObject *dummyVal = helper->createJStringObjectWith("dummy");
//	BOOST_REQUIRE_THROW(obj->setVal("dummyVal",dummyVal),CppHibernateException);
//	delete dummyVal;
//
//	CppHibernateJIntegerObject *intObj1 = helper->createJIntegerObjectWith(20);
//	BOOST_REQUIRE(std::strncmp("java.lang.Integer",intObj1->getCanonicalName(),std::strlen("java.lang.Integer")) == 0);
//	BOOST_REQUIRE_NO_THROW(intObj1->setVal(200));
//
//	BOOST_REQUIRE(obj->getVal("value") == NULL);
//	BOOST_REQUIRE_NO_THROW(obj->setVal("value",intObj1));
//
//	CppHibernateJIntegerObject *rtn1 = NULL;
//	BOOST_REQUIRE_NO_THROW(rtn1 = dynamic_cast<CppHibernateJIntegerObject *>(obj->getVal("value")));
//	BOOST_REQUIRE(rtn1->getVal() == 200);
//
//	CppHibernateJFloatObject *float1 = NULL;
//	BOOST_REQUIRE_NO_THROW(float1 = dynamic_cast<CppHibernateJFloatObject *>(obj->getVal("floatValue")));
//	BOOST_REQUIRE(float1 == NULL);
//
//	CppHibernateJFloatObject *floatVal = NULL;
//	BOOST_REQUIRE_NO_THROW(floatVal = helper->createJFloatObjectWith(20.22));
//	BOOST_REQUIRE(std::strncmp("java.lang.Float",floatVal->getCanonicalName(),std::strlen("java.lang.Float")) == 0);
//	BOOST_REQUIRE_NO_THROW(obj->setVal("floatValue",floatVal));
//	BOOST_REQUIRE_NO_THROW(float1 = dynamic_cast<CppHibernateJFloatObject *>(obj->getVal("floatValue")));
//	BOOST_REQUIRE(float1 != NULL);
//	BOOST_REQUIRE(floatVal->getVal() == float1->getVal());
//
//	CppHibernateJBooleanObject *boolean1 = NULL;
//	BOOST_REQUIRE_NO_THROW(boolean1 = dynamic_cast<CppHibernateJBooleanObject *>(obj->getVal("booleanValue")));
//	BOOST_REQUIRE(boolean1 == NULL);
//	CppHibernateJBooleanObject *booleanVal = NULL;
//	BOOST_REQUIRE_NO_THROW(booleanVal = helper->createJBooleanObjectWith(true));
//	BOOST_REQUIRE(std::strncmp("java.lang.Boolean",booleanVal->getCanonicalName(),std::strlen("java.lang.Boolean")) == 0);
//	BOOST_REQUIRE_NO_THROW(obj->setVal("booleanValue",booleanVal));
//	BOOST_REQUIRE_NO_THROW(boolean1 = dynamic_cast<CppHibernateJBooleanObject *>(obj->getVal("booleanValue")));
//	BOOST_REQUIRE(boolean1->getVal() == true);
//
//	CppHibernateJDoubleObject *double1 = NULL;
//	BOOST_REQUIRE_NO_THROW(double1 = dynamic_cast<CppHibernateJDoubleObject *>(obj->getVal("doubleValue")));
//	BOOST_REQUIRE(double1 == NULL);
//	CppHibernateJDoubleObject *doubleVal = helper->createJDoubleObjectWith(400.213);
//	BOOST_REQUIRE(std::strncmp("java.lang.Double",doubleVal->getCanonicalName(),std::strlen("java.lang.Double")) == 0);
//	BOOST_REQUIRE_NO_THROW(doubleVal->setVal(100));
//	BOOST_REQUIRE_NO_THROW(obj->setVal("doubleValue",doubleVal));
//	BOOST_REQUIRE_NO_THROW(double1 = dynamic_cast<CppHibernateJDoubleObject *>(obj->getVal("doubleValue")));
//	BOOST_REQUIRE(doubleVal->getVal() == double1->getVal());
//
//	CppHibernateJLongObject *long1 = NULL;
//	BOOST_REQUIRE_NO_THROW(long1 = dynamic_cast<CppHibernateJLongObject *>(obj->getVal("longValue")));
//	BOOST_REQUIRE(long1 == NULL);
//	CppHibernateJLongObject *longVal = helper->createJLongObjectWith(800);
//	BOOST_REQUIRE(std::strncmp("java.lang.Long",longVal->getCanonicalName(),std::strlen("java.lang.Long")) == 0);
//	BOOST_REQUIRE_NO_THROW(obj->setVal("longValue",longVal));
//	BOOST_REQUIRE_NO_THROW(long1 = dynamic_cast<CppHibernateJLongObject *>(obj->getVal("longValue")));
//	BOOST_REQUIRE(longVal->getVal() == long1->getVal());
//
//	CppHibernateJObject *date = NULL;
//
//	BOOST_REQUIRE_NO_THROW(date = helper->createJObjectWith("java.util.Date"));
//	BOOST_REQUIRE(std::strncmp("java.util.Date",date->getCanonicalName(),std::strlen("java.util.Date")) == 0);
//	const char *dateStr = date->toString();
//	BOOST_REQUIRE(std::strlen(dateStr) > 0);
//	BOOST_TEST_MESSAGE("current time is " << dateStr);
//	BOOST_REQUIRE_NO_THROW(obj->setVal("date",date));
//	CppHibernateJObject *rtnDate = NULL;
//	BOOST_REQUIRE_NO_THROW(rtnDate = obj->getVal("date"));
//	BOOST_REQUIRE(std::strncmp(dateStr,rtnDate->toString(),std::strlen(dateStr)) == 0);
//
//	CppHibernateJObject *event1 = helper->createJObjectWith("org.hibernateDomain.Event");
//	CppHibernateJStringObject *title = helper->createJStringObjectWith("title2");
//	BOOST_REQUIRE_NO_THROW(event1->setVal("title",title));
//	BOOST_REQUIRE_NO_THROW(obj->setVal("anotherEvent",event1));
//	CppHibernateJObject *rtnEvent = NULL;
//	BOOST_REQUIRE_NO_THROW(rtnEvent = obj->getVal("anotherEvent"));
//	BOOST_TEST_MESSAGE("rtnEvent is: " << rtnEvent->toString());
//	CppHibernateJStringObject *title2 = NULL;
//	BOOST_REQUIRE_NO_THROW(title2 = dynamic_cast<CppHibernateJStringObject *>(rtnEvent->getVal("title")));
//	BOOST_REQUIRE(std::strncmp(title2->getVal(),title->getVal(),std::strlen(title->getVal())) == 0);
//
//	CppHibernateJObject *list = NULL;
//	BOOST_REQUIRE_NO_THROW(list = obj->getVal("list"));
//	BOOST_REQUIRE(list != NULL);
//
//	BOOST_REQUIRE(list->isInstanceOf("org.hibernate.Session") == false);
//	BOOST_REQUIRE(list->isInstanceOf("org.hibernate.SessionFactory") == false);
//	BOOST_REQUIRE(list->isInstanceOf("java.util.Set") == false);
//	BOOST_REQUIRE(list->isInstanceOf("org.hibernateDomain.Event") == false);
//	BOOST_REQUIRE(list->isInstanceOf("java.util.Collection") == true);
//	BOOST_REQUIRE(list->isInstanceOf("java.util.ArrayList") == true);
//
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJCollectionObject *>(list))->size() == 0);
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJCollectionObject *>(list))->isEmpty() == true);
//
//	BOOST_REQUIRE_THROW((dynamic_cast<CppHibernateJCollectionObject *>(list))->add(NULL),CppHibernateException);
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJCollectionObject *>(list))->add(longVal));
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJCollectionObject *>(list))->size() == 1);
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJCollectionObject *>(list))->isEmpty() == false);
//
//	BOOST_REQUIRE_THROW((dynamic_cast<CppHibernateJCollectionObject *>(list))->remove(NULL),CppHibernateException);
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJCollectionObject *>(list))->remove(longVal) == true);
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJCollectionObject *>(list))->remove(title2) == false);
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJCollectionObject *>(list))->isEmpty() == true);
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJCollectionObject *>(list))->size() == 0);
//
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJCollectionObject *>(list))->add(date));
//	CppHibernateJObject *date2 = NULL;
//	BOOST_REQUIRE_NO_THROW(date2 = helper->createJObjectWith("java.util.Date"));
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJCollectionObject *>(list))->add(date2));
//	CppHibernateJObject *date3 = NULL;
//	BOOST_REQUIRE_NO_THROW(date3 = helper->createJObjectWith("java.util.Date"));
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJCollectionObject *>(list))->add(date3));
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJCollectionObject *>(list))->isEmpty() == false);
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJCollectionObject *>(list))->size() == 3);
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJCollectionObject *>(list))->clear());
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJCollectionObject *>(list))->isEmpty() == true);
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJCollectionObject *>(list))->size() == 0);
//
//	CppHibernateJBooleanObject *bb1 = helper->createJBooleanObjectWith(true);
//	CppHibernateJBooleanObject *bb2 = helper->createJBooleanObjectWith(false);
//	CppHibernateJBooleanObject *bb3 = helper->createJBooleanObjectWith(true);
//	CppHibernateJBooleanObject *bb4 = helper->createJBooleanObjectWith(true);
//
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJCollectionObject *>(list))->add(bb1));
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJCollectionObject *>(list))->add(bb2));
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJCollectionObject *>(list))->add(bb3));
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJCollectionObject *>(list))->add(bb4));
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJCollectionObject *>(list))->isEmpty() == false);
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJCollectionObject *>(list))->size() == 4);
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJCollectionObject *>(list))->remove(bb1));
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJCollectionObject *>(list))->remove(bb2));
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJCollectionObject *>(list))->remove(bb3));
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJCollectionObject *>(list))->remove(bb1));
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJCollectionObject *>(list))->isEmpty() == true);
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJCollectionObject *>(list))->size() == 0);
//
//	CppHibernateJStringObject *strObj1 = helper->createJStringObjectWith("a");
//	CppHibernateJStringObject *strObj2 = helper->createJStringObjectWith("b");
//	CppHibernateJStringObject *strObj3 = helper->createJStringObjectWith("c");
//
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJCollectionObject *>(list))->add(strObj1));
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJCollectionObject *>(list))->add(strObj2));
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJCollectionObject *>(list))->add(strObj3));
//	CppHibernateJStringObject *rtnStr11 = NULL;
//	BOOST_REQUIRE_NO_THROW(rtnStr11 = dynamic_cast<CppHibernateJStringObject *>((dynamic_cast<CppHibernateJCollectionObject *>(list))->get(0)));
//	BOOST_REQUIRE(std::strncmp("a",rtnStr11->getVal(),1) == 0);
//	CppHibernateJStringObject *rtnStr22 = NULL;
//	BOOST_REQUIRE_NO_THROW(rtnStr22 = dynamic_cast<CppHibernateJStringObject *>((dynamic_cast<CppHibernateJCollectionObject *>(list))->get(1)));
//	BOOST_REQUIRE(std::strncmp("b",rtnStr22->getVal(),1) == 0);
//	CppHibernateJStringObject *rtnStr33 = NULL;
//	BOOST_REQUIRE_NO_THROW(rtnStr33 = dynamic_cast<CppHibernateJStringObject *>((dynamic_cast<CppHibernateJCollectionObject *>(list))->get(2)));
//	BOOST_REQUIRE(std::strncmp("c",rtnStr33->getVal(),1) == 0);
//	BOOST_REQUIRE_THROW((dynamic_cast<CppHibernateJCollectionObject *>(list))->get(-1),CppHibernateException);
//	BOOST_REQUIRE_THROW((dynamic_cast<CppHibernateJCollectionObject *>(list))->get(3),CppHibernateException);
//
//	CppHibernateJObject *set = NULL;
//	BOOST_REQUIRE_NO_THROW(set = obj->getVal("set"));
//	BOOST_REQUIRE(set != NULL);
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJCollectionObject *>(set))->isEmpty() == true);
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJCollectionObject *>(set))->size() == 0);
//
//	CppHibernateJIntegerObject *objInt1 = helper->createJIntegerObjectWith(60);
//	CppHibernateJIntegerObject *objInt2 = helper->createJIntegerObjectWith(70);
//	CppHibernateJIntegerObject *objInt3 = helper->createJIntegerObjectWith(80);
//	CppHibernateJIntegerObject *objInt4 = helper->createJIntegerObjectWith(90);
//
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJCollectionObject *>(set))->add(objInt1));
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJCollectionObject *>(set))->add(objInt2));
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJCollectionObject *>(set))->add(objInt3));
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJCollectionObject *>(set))->add(objInt4));
//
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJCollectionObject *>(set))->size() == 4);
//	CppHibernateJObject *rtnSet = obj->getVal("set");
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJCollectionObject *>(rtnSet))->size() == 4);
//
//	CppHibernateJObject *m = helper->createJObjectWith("java.util.HashMap");
//	BOOST_REQUIRE(m->isInstanceOf("java.util.Map") == true);
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJMapObject *>(m))->clear());
//
//	CppHibernateJObject *s = helper->createJStringObjectWith("google");
//	bool b = false;
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJMapObject *>(m))->containsKey(s));
//	BOOST_REQUIRE(b == false);
//
//	CppHibernateJStringObject *key = helper->createJStringObjectWith("key");
//	CppHibernateJStringObject *val = helper->createJStringObjectWith("val");
//	CppHibernateJObject *rtnObj = NULL;
//
//	BOOST_REQUIRE_NO_THROW(rtnObj = (dynamic_cast<CppHibernateJMapObject *>(m))->put(key,val,true));
//	BOOST_REQUIRE_NO_THROW(b = (dynamic_cast<CppHibernateJMapObject *>(m))->containsKey(key));
//	BOOST_REQUIRE(b == true);
//	BOOST_REQUIRE(rtnObj == NULL);
//
//	CppHibernateJStringObject *val2 = helper->createJStringObjectWith("val2");
//	BOOST_REQUIRE_NO_THROW(rtnObj = (dynamic_cast<CppHibernateJMapObject *>(m))->put(key,val2,true));
//	BOOST_REQUIRE(rtnObj != NULL);
//	CppHibernateJStringObject *rStr = dynamic_cast<CppHibernateJStringObject *>(rtnObj);
//
//	BOOST_REQUIRE(rStr != NULL);
//	BOOST_REQUIRE(std::strncmp("val",rStr->getVal(),std::strlen("val")) == 0);
//
//	CppHibernateJObject *keyedVal = NULL;
//
//	CppHibernateJLongObject *lObj = helper->createJLongObjectWith(300);
//	BOOST_REQUIRE_NO_THROW(keyedVal = (dynamic_cast<CppHibernateJMapObject *>(m))->get(lObj));
//	BOOST_REQUIRE(keyedVal == NULL);
//	BOOST_REQUIRE_NO_THROW(keyedVal = (dynamic_cast<CppHibernateJMapObject *>(m))->get(key));
//	BOOST_REQUIRE(keyedVal != NULL);
//	CppHibernateJStringObject * keyedValStr = dynamic_cast<CppHibernateJStringObject *>(keyedVal);
//	BOOST_REQUIRE(keyedValStr != NULL);
//	BOOST_REQUIRE(std::strncmp("val",keyedValStr->getVal(),std::strlen("val")) == 0);
//
//	BOOST_REQUIRE_NO_THROW(b = (dynamic_cast<CppHibernateJMapObject *>(m))->containsValue(key));
//	BOOST_REQUIRE(b == false);
//	BOOST_REQUIRE_NO_THROW(b = (dynamic_cast<CppHibernateJMapObject *>(m))->containsValue(val2));
//	BOOST_REQUIRE(b == true);
//
//	CppHibernateJStringObject *key2 = helper->createJStringObjectWith("key2");
//	CppHibernateJStringObject *val3 = helper->createJStringObjectWith("value3");
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJMapObject *>(m))->put(key2,val3));
//
//	CppHibernateJCollectionObject *keySet = NULL;
//	BOOST_REQUIRE_NO_THROW(keySet = (dynamic_cast<CppHibernateJMapObject *>(m))->keySet());
//	BOOST_REQUIRE(keySet != NULL);
//	BOOST_REQUIRE(keySet->size() == 2);
//
//	CppHibernateJObject *m2 = helper->createJObjectWith("java.util.HashMap");
//	BOOST_REQUIRE_NO_THROW((dynamic_cast<CppHibernateJMapObject *>(m2))->putAll((dynamic_cast<CppHibernateJMapObject *>(m))));
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJMapObject *>(m2))->containsKey(key) == true);
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJMapObject *>(m2))->containsKey(key2) == true);
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJMapObject *>(m2))->containsValue(val2) == true);
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJMapObject *>(m2))->containsValue(val3) == true);
//	BOOST_REQUIRE((dynamic_cast<CppHibernateJMapObject *>(m2))->size() == 2);
//
//	CppHibernateJCollectionObject *clObj = NULL;
//	BOOST_REQUIRE_NO_THROW(clObj = (dynamic_cast<CppHibernateJMapObject *>(m2))->values());
//	BOOST_REQUIRE(clObj != NULL);
//	BOOST_REQUIRE(clObj->size() == 2);
//	BOOST_REQUIRE_NO_THROW(clObj->hashCode());
//
//	BOOST_REQUIRE_NO_THROW(b = clObj->equals((dynamic_cast<CppHibernateJMapObject *>(m2))));
//	BOOST_REQUIRE(b == false);
//	BOOST_REQUIRE_NO_THROW(b = (dynamic_cast<CppHibernateJMapObject *>(m2))->equals(m));
//	BOOST_REQUIRE(b == true);
//
//	CppHibernateJIteratorObject itr = clObj->iterator();
//	BOOST_REQUIRE(itr.hasNext() == true);
//
//	bool bArray[4];
//	bArray[0] = true;
//	bArray[1] = true;
//	bArray[2] = false;
//	bArray[3] = true;
//
//	CppHibernateJArray<bool> barr = helper->createJArrayWith(CppHibernateArrayType::ARRAY_BOOL,4,bArray);
//	BOOST_REQUIRE(barr.length() == 4);
//	int indx;
//	for(indx = 0;indx < 4;indx++) {
//		if(indx == 2) {
//			BOOST_REQUIRE(barr[indx] == false);
//		} else {
//			BOOST_REQUIRE(barr[indx] == true);
//		}
//	}
//	bool *bArray2 = new bool[4];
//	bArray2[0] = false;
//	bArray2[1] = false;
//	bArray2[2] = true;
//	bArray2[3] = false;
//	CppHibernateJArray<bool> barr2 = helper->createJArrayWith(CppHibernateArrayType::ARRAY_BOOL,4,bArray2);
//	BOOST_REQUIRE(barr2.length() == 4);
//	for(indx = 0;indx < 4;indx++) {
//		if(indx == 2) {
//			BOOST_REQUIRE(barr2[indx] == true);
//		} else {
//			BOOST_REQUIRE(barr2[indx] == false);
//		}
//	}
//	delete [] bArray2;
//
//	unsigned char ucArray[5];
//	for(indx = 0;indx < 5;indx++) {
//		ucArray[indx] = indx + 1;
//	}
//	CppHibernateJArray<unsigned char> ucArr = helper->createJArrayWith(CppHibernateArrayType::ARRAY_UNSIGNED_CHAR,5,ucArray);
//	BOOST_REQUIRE(ucArr.length() == 5);
//	for(indx = 0;indx < 5;indx++) {
//		BOOST_REQUIRE(ucArr[indx] == (indx + 1));
//	}
//	unsigned char *ucArray2 = new unsigned char[5];
//	ucArray2[0] = 1;
//	ucArray2[1] = 0;
//	ucArray2[2] = 0;
//	ucArray2[3] = 1;
//	ucArray2[4] = 1;
//	CppHibernateJArray<unsigned char> ucArr2 = helper->createJArrayWith(CppHibernateArrayType::ARRAY_UNSIGNED_CHAR,5,ucArray2);
//	BOOST_REQUIRE(ucArr2.length() == 5);
//	for(indx = 0;indx < 5;indx++) {
//		if(indx == 1 || indx == 2) {
//			BOOST_REQUIRE(ucArr2[indx] == 0);
//		} else {
//			BOOST_REQUIRE(ucArr2[indx] == 1);
//		}
//	}
//	delete [] ucArray2;
//
//	char cArray[5];
//	cArray[0] = 'h';
//	cArray[1] = 'e';
//	cArray[2] = 'l';
//	cArray[3] = 'l';
//	cArray[4] = 'o';
//	CppHibernateJArray<char> cArr = helper->createJArrayWith(CppHibernateArrayType::ARRAY_CHAR,5,cArray);
//	BOOST_REQUIRE(cArr.length() == 5);
//	BOOST_REQUIRE(cArr[0] == 'h');
//	BOOST_REQUIRE(cArr[1] == 'e');
//	BOOST_REQUIRE(cArr[2] == 'l');
//	BOOST_REQUIRE(cArr[3] == 'l');
//	BOOST_REQUIRE(cArr[4] == 'o');
//	char *cArray2 = new char[10];
//	cArray2[0] = 'h';
//	cArray2[1] = 'e';
//	cArray2[2] = 'l';
//	cArray2[3] = 'l';
//	cArray2[4] = 'o';
//	cArray2[5] = 'w';
//	cArray2[6] = 'o';
//	cArray2[7] = 'r';
//	cArray2[8] = 'l';
//	cArray2[9] = 'd';
//	CppHibernateJArray<char> cArr2 = helper->createJArrayWith(CppHibernateArrayType::ARRAY_CHAR,10,cArray2);
//	BOOST_REQUIRE(cArr2.length() == 10);
//	BOOST_REQUIRE(cArr2[0] == 'h');
//	BOOST_REQUIRE(cArr2[1] == 'e');
//	BOOST_REQUIRE(cArr2[2] == 'l');
//	BOOST_REQUIRE(cArr2[3] == 'l');
//	BOOST_REQUIRE(cArr2[4] == 'o');
//	BOOST_REQUIRE(cArr2[5] == 'w');
//	BOOST_REQUIRE(cArr2[6] == 'o');
//	BOOST_REQUIRE(cArr2[7] == 'r');
//	BOOST_REQUIRE(cArr2[8] == 'l');
//	BOOST_REQUIRE(cArr2[9] == 'd');
//	delete [] cArray2;
//
//	short sArray[6];
//	for(indx = 0;indx < 6;indx++) {
//		short ind = 6 - indx - 1;
//		sArray[indx] = ind;
//	}
//	CppHibernateJArray<short> sArr = helper->createJArrayWith(CppHibernateArrayType::ARRAY_SHORT,6,sArray);
//	BOOST_REQUIRE(sArr.length() == 6);
//	BOOST_REQUIRE(sArr[0] == 5);
//	BOOST_REQUIRE(sArr[1] == 4);
//	BOOST_REQUIRE(sArr[2] == 3);
//	BOOST_REQUIRE(sArr[3] == 2);
//	BOOST_REQUIRE(sArr[4] == 1);
//	BOOST_REQUIRE(sArr[5] == 0);
//	short *sArray2 = new short[9];
//	for(indx = 0;indx < 9;indx++) {
//		sArray2[indx] = indx + 10;
//	}
//	CppHibernateJArray<short> sArr2 = helper->createJArrayWith(CppHibernateArrayType::ARRAY_SHORT,9,sArray2);
//	BOOST_REQUIRE(sArr2.length() == 9);
//	for(indx = 10;indx < 19;indx++) {
//		BOOST_REQUIRE(sArr2[indx - 10] == indx);
//	}
//	delete [] sArray2;
//
//	int iArray[60000];
//	for(indx = 0;indx < 60000;indx++) {
//		iArray[indx] = indx;
//	}
//	CppHibernateJArray<int> iArr = helper->createJArrayWith(CppHibernateArrayType::ARRAY_INT,60000,iArray);
//	BOOST_REQUIRE(iArr.length() == 60000);
//	for(indx = 0;indx < 60000;indx++) {
//		BOOST_REQUIRE(iArr[indx] == indx);
//	}
//	int *iArray2 = new int[4];
//	for(indx = 0;indx < 4;indx++) {
//		iArray2[indx] = (indx + 1) * 10;
//	}
//	CppHibernateJArray<int> iArr2 = helper->createJArrayWith(CppHibernateArrayType::ARRAY_INT,4,iArray2);
//	BOOST_REQUIRE(iArr2.length() == 4);
//	BOOST_REQUIRE(iArr2[0] == 10);
//	BOOST_REQUIRE(iArr2[1] == 20);
//	BOOST_REQUIRE(iArr2[2] == 30);
//	BOOST_REQUIRE(iArr2[3] == 40);
//	delete [] iArray2;
//
//	long lArray[3];
//	for(indx = 0;indx < 3;indx++) {
//		lArray[indx] = indx * 100;
//	}
//	CppHibernateJArray<long> lArr = helper->createJArrayWith(CppHibernateArrayType::ARRAY_LONG,3,lArray);
//	BOOST_REQUIRE(lArr.length() == 3);
//	BOOST_REQUIRE(lArray[0] == 0);
//	BOOST_REQUIRE(lArray[1] == 100);
//	BOOST_REQUIRE(lArray[2] == 200);
//	long *lArray2 = new long[4];
//	for(indx = 0;indx < 4;indx++) {
//		lArray2[indx] = indx + 5;
//	}
//	CppHibernateJArray<long> lArr2 = helper->createJArrayWith(CppHibernateArrayType::ARRAY_LONG,4,lArray2);
//	BOOST_REQUIRE(lArr2.length() == 4);
//	BOOST_REQUIRE(lArr2[0] == 5);
//	BOOST_REQUIRE(lArr2[1] == 6);
//	BOOST_REQUIRE(lArr2[2] == 7);
//	BOOST_REQUIRE(lArr2[3] == 8);
//	delete [] lArray2;
//
//	float fArray[2];
//	fArray[0] = 0.01;
//	fArray[1] = 0.02;
//	CppHibernateJArray<float> fArr = helper->createJArrayWith(CppHibernateArrayType::ARRAY_FLOAT,2,fArray);
//	BOOST_REQUIRE(fArr.length() == 2);
//	BOOST_REQUIRE(fArr[0] == (float)0.01);
//	BOOST_REQUIRE(fArr[1] == (float)0.02);
//	float *fArray2 = new float[1];
//	fArray2[0] = 0.0002;
//	CppHibernateJArray<float> fArr2 = helper->createJArrayWith(CppHibernateArrayType::ARRAY_FLOAT,2,fArray2);
//	BOOST_REQUIRE(fArr2.length() == 2);
//	BOOST_REQUIRE(fArr2[0] == (float)0.0002);
//	delete [] fArray2;
//
//	double dArray[3];
//	dArray[0] = 2;
//	dArray[1] = 3;
//	dArray[2] = 4;
//	CppHibernateJArray<double> dArr = helper->createJArrayWith(CppHibernateArrayType::ARRAY_DOUBLE,3,dArray);
//	BOOST_REQUIRE(dArr.length() == 3);
//	BOOST_REQUIRE(dArr[0] == (double)2);
//	BOOST_REQUIRE(dArr[1] == (double)3);
//	BOOST_REQUIRE(dArr[2] == (double)4);
//	double *dArray2 = new double[2];
//	dArray2[0] = 5;
//	dArray2[1] = 3;
//	CppHibernateJArray<double> dArr2 = helper->createJArrayWith(CppHibernateArrayType::ARRAY_DOUBLE,2,dArray2);
//	BOOST_REQUIRE(dArr2.length() == 2);
//	BOOST_REQUIRE(dArr2[0] == (double)5);
//	BOOST_REQUIRE(dArr2[1] == (double)3);
//	delete [] dArray2;
//
//	int arrayInt[6];
//	arrayInt[0] = 6;
//	arrayInt[1] = 7;
//	arrayInt[2] = 8;
//	arrayInt[3] = 9;
//	arrayInt[4] = 10;
//	arrayInt[5] = 11;
//	CppHibernateJArray<int> intArray = helper->createJArrayWith(CppHibernateArrayType::ARRAY_INT,6,arrayInt);
//	BOOST_REQUIRE_NO_THROW(obj->setVal("ints",&intArray));
//	CppHibernateJArray<int> *rtnIntArray = NULL;
//	BOOST_REQUIRE_NO_THROW(rtnIntArray = dynamic_cast<CppHibernateJArray<int>* >(obj->getVal("ints")));
//	BOOST_REQUIRE(rtnIntArray != NULL);
//	BOOST_REQUIRE(rtnIntArray->length() == 6);
//	for(indx = 0;indx < 6;indx++) {
//		BOOST_REQUIRE((*rtnIntArray)[indx] == (indx + 6));
//	}
//	delete rtnIntArray;
//
//	bool arrayBool[4];
//	arrayBool[0] = false;
//	arrayBool[1] = true;
//	arrayBool[2] = true;
//	arrayBool[3] = false;
//	CppHibernateJArray<bool> boolArray = helper->createJArrayWith(CppHibernateArrayType::ARRAY_BOOL,4,arrayBool);
//	BOOST_REQUIRE_NO_THROW(obj->setVal("booleans",&boolArray));
//	CppHibernateJArray<bool> *rtnBoolArray = NULL;
//	BOOST_REQUIRE_NO_THROW(rtnBoolArray = dynamic_cast<CppHibernateJArray<bool> *>(obj->getVal("booleans")));
//	BOOST_REQUIRE(rtnBoolArray != NULL);
//	BOOST_REQUIRE(rtnBoolArray->length() == 4);
//	for(indx = 0;indx < 4;indx++) {
//		if(indx == 0 || indx == 3) {
//			BOOST_REQUIRE((*rtnBoolArray)[indx] == false);
//		} else {
//			BOOST_REQUIRE((*rtnBoolArray)[indx] == true);
//		}
//	}
//	delete rtnBoolArray;
//
//	unsigned char arrayUC[4];
//	arrayUC[0] = 'g';
//	arrayUC[1] = 'o';
//	arrayUC[2] = 'o';
//	arrayUC[3] = 'd';
//	CppHibernateJArray<unsigned char> arrayUnsignedChar = helper->createJArrayWith(CppHibernateArrayType::ARRAY_UNSIGNED_CHAR,4,arrayUC);
//	BOOST_REQUIRE_NO_THROW(obj->setVal("bytes",&arrayUnsignedChar));
//	CppHibernateJArray<unsigned char> *rtnUC = NULL;
//	BOOST_REQUIRE_NO_THROW(rtnUC = dynamic_cast<CppHibernateJArray<unsigned char> *>(obj->getVal("bytes")));
//	BOOST_REQUIRE(rtnUC != NULL);
//	BOOST_REQUIRE(rtnUC->length() == 4);
//	BOOST_REQUIRE((*rtnUC)[0] == 'g');
//	BOOST_REQUIRE((*rtnUC)[1] == 'o');
//	BOOST_REQUIRE((*rtnUC)[2] == 'o');
//	BOOST_REQUIRE((*rtnUC)[3] == 'd');
//	delete rtnUC;
//
//	char chars[3];
//	chars[0] = 'c';
//	chars[1] = 'p';
//	chars[2] = 'p';
//	CppHibernateJArray<char> arrayChar = helper->createJArrayWith(CppHibernateArrayType::ARRAY_CHAR,3,chars);
//	BOOST_REQUIRE_NO_THROW(obj->setVal("chars",&arrayChar));
//	CppHibernateJArray<char> *rtnChar = NULL;
//	BOOST_REQUIRE_NO_THROW(rtnChar = dynamic_cast<CppHibernateJArray<char> *>(obj->getVal("chars")));
//	BOOST_REQUIRE(rtnChar != NULL);
//	BOOST_REQUIRE(rtnChar->length() == 3);
//	BOOST_REQUIRE((*rtnChar)[0] == 'c');
//	BOOST_REQUIRE((*rtnChar)[1] == 'p');
//	BOOST_REQUIRE((*rtnChar)[2] == 'p');
//	delete rtnChar;
//
//	short shorts[10];
//	for(indx = 0;indx < 10;indx++) {
//		shorts[indx] = (short)indx;
//	}
//	CppHibernateJArray<short> arrayShort = helper->createJArrayWith(CppHibernateArrayType::ARRAY_SHORT,10,shorts);
//	BOOST_REQUIRE_NO_THROW(obj->setVal("shorts",&arrayShort));
//	CppHibernateJArray<short> *rtnShortArray = NULL;
//	BOOST_REQUIRE_NO_THROW(rtnShortArray = dynamic_cast<CppHibernateJArray<short> *>(obj->getVal("shorts")));
//	BOOST_REQUIRE(rtnShortArray != NULL);
//	BOOST_REQUIRE(rtnShortArray->length() == 10);
//	for(indx = 0;indx < 10;indx++) {
//		BOOST_REQUIRE((*rtnShortArray)[indx] == (short)indx);
//	}
//	delete rtnShortArray;
//
//	long longs[3];
//	longs[0] = (long)2;
//	longs[1] = (long)3;
//	longs[2] = (long)4;
//	CppHibernateJArray<long> arrayLong = helper->createJArrayWith(CppHibernateArrayType::ARRAY_LONG,3,longs);
//	BOOST_REQUIRE_NO_THROW(obj->setVal("longs",&arrayLong));
//	CppHibernateJArray<long> *rtnLongArray = NULL;
//	BOOST_REQUIRE_NO_THROW(rtnLongArray = dynamic_cast<CppHibernateJArray<long> *>(obj->getVal("longs")));
//	BOOST_REQUIRE(rtnLongArray != NULL);
//	BOOST_REQUIRE(rtnLongArray->length() == 3);
//	for(indx = 0;indx < 3;indx++) {
//		BOOST_REQUIRE((*rtnLongArray)[indx] == (long)(indx + 2));
//	}
//	delete rtnLongArray;
//
//	float floats[2];
//	floats[0] = (float)0.0002;
//	floats[1] = (float)0.0003;
//	CppHibernateJArray<float> arrayFloat = helper->createJArrayWith(CppHibernateArrayType::ARRAY_FLOAT,2,floats);
//	BOOST_REQUIRE_NO_THROW(obj->setVal("floats",&arrayFloat));
//	CppHibernateJArray<float> *rtnFloatArray = NULL;
//	BOOST_REQUIRE_NO_THROW(rtnFloatArray = dynamic_cast<CppHibernateJArray<float> *>(obj->getVal("floats")));
//	BOOST_REQUIRE(rtnFloatArray != NULL);
//	BOOST_REQUIRE(rtnFloatArray->length() == 2);
//	BOOST_REQUIRE((*rtnFloatArray)[0] == (float)0.0002);
//	BOOST_REQUIRE((*rtnFloatArray)[1] == (float)0.0003);
//	delete rtnFloatArray;
//
//	double doubles[2];
//	doubles[0] = (double)12;
//	doubles[1] = (double)13;
//	CppHibernateJArray<double> arrayDouble = helper->createJArrayWith(CppHibernateArrayType::ARRAY_DOUBLE,2,doubles);
//	BOOST_REQUIRE_NO_THROW(obj->setVal("doubles",&arrayDouble));
//	CppHibernateJArray<double> *rtnDoubleArray = NULL;
//	BOOST_REQUIRE_NO_THROW(rtnDoubleArray = dynamic_cast<CppHibernateJArray<double> *>(obj->getVal("doubles")));
//	BOOST_REQUIRE(rtnDoubleArray->length() == 2);
//	BOOST_REQUIRE((*rtnDoubleArray)[0] == (double)12);
//	BOOST_REQUIRE((*rtnDoubleArray)[1] == (double)13);
//	delete rtnDoubleArray;
//
//	delete clObj;
//	delete m2;
//	delete keySet;
//	delete key2;
//	delete val3;
//	delete val2;
//	delete lObj;
//	delete keyedValStr;
//	delete rStr;
//	delete key;
//	delete val;
//	delete m;
//	delete s;
//
//	delete rtnSet;
//	delete objInt4;
//	delete objInt3;
//	delete objInt2;
//	delete objInt1;
//	delete set;
//	delete rtnStr33;
//	delete rtnStr22;
//	delete rtnStr11;
//	delete strObj3;
//	delete strObj2;
//	delete strObj1;
//	delete bb4;
//	delete bb3;
//	delete bb2;
//	delete bb1;
//	delete date3;
//	delete date2;
//	delete list;
//	delete title2;
//	delete rtnDate;
//	delete date;
//	delete event1;
//	delete title;
//	delete longVal;
//	delete long1;
//	delete double1;
//	delete doubleVal;
//	delete boolean1;
//	delete booleanVal;
//	delete floatVal;
//	delete rtnStr1;
//	delete str;
//	delete intObj1;
//	delete rtn1;
//	delete obj;
//	delete helper;
//	delete loader;
}

BOOST_AUTO_TEST_CASE(testCppHibernateMethodInvoker) {
//	CppHibernateJVMConfiguration *configuration = new CppHibernateJVMConfiguration(ROOT_CLASS_PATH);
//	AbstractClassLoader *loader = new URLClassLoader(configuration->getJNIEnv(),HIBERNATE_LIB_LOCATION);
//	CppHibernateObjectHelper *helper = new CppHibernateObjectHelper(configuration->getJNIEnv(),loader);
//
//	CppHibernateMethodInvoker *methodInvoker = new CppHibernateMethodInvoker(configuration->getJNIEnv(),loader);
//	CppHibernateJObject *event1 = helper->createJObjectWith("org/hibernateDomain/Event2");
//
//	BOOST_REQUIRE_NO_THROW(methodInvoker->getMethodReturnSignature(event1->getObj(),event1->getObjClass(),"getDate"));
//	BOOST_REQUIRE(std::strncmp("Ljava/util/Date;",methodInvoker->getMethodReturnSignature(event1->getObj(),event1->getObjClass(),"getDate"),std::strlen("Ljava/util/Date;")) == 0);
//	BOOST_REQUIRE_NO_THROW(methodInvoker->getMethodParametersSignature(event1->getObj(),event1->getObjClass(),"getDate"));
//	BOOST_REQUIRE(std::strlen(methodInvoker->getMethodParametersSignature(event1->getObj(),event1->getObjClass(),"getDate")) == 0);
//	BOOST_REQUIRE(std::strncmp("()Ljava/util/Date;",methodInvoker->getMethodSignature(event1->getObj(),event1->getObjClass(),"getDate"),std::strlen("()Ljava/util/Date;")) == 0);
//
//	BOOST_REQUIRE_NO_THROW(methodInvoker->getMethodReturnSignature(event1->getObj(),event1->getObjClass(),"getId"));
//	BOOST_REQUIRE(std::strncmp("Ljava/lang/Long;",methodInvoker->getMethodReturnSignature(event1->getObj(),event1->getObjClass(),"getId"),std::strlen("Ljava/lang/Long;")) == 0);
//	BOOST_REQUIRE_NO_THROW(methodInvoker->getMethodParametersSignature(event1->getObj(),event1->getObjClass(),"getId"));
//	BOOST_REQUIRE(std::strlen(methodInvoker->getMethodParametersSignature(event1->getObj(),event1->getObjClass(),"getId")) == 0);
//	BOOST_REQUIRE(std::strncmp("()Ljava/lang/Long;",methodInvoker->getMethodSignature(event1->getObj(),event1->getObjClass(),"getId"),std::strlen("()Ljjava/lang/Long;")) == 0);
//
//	BOOST_REQUIRE_NO_THROW(methodInvoker->getMethodReturnSignature(event1->getObj(),event1->getObjClass(),"getTitle"));
//	BOOST_REQUIRE(std::strncmp("Ljava/lang/String;",methodInvoker->getMethodReturnSignature(event1->getObj(),event1->getObjClass(),"getTitle"),std::strlen("Ljava/lang/String;")) == 0);
//	BOOST_REQUIRE_NO_THROW(methodInvoker->getMethodParametersSignature(event1->getObj(),event1->getObjClass(),"getTitle"));
//	BOOST_REQUIRE(std::strlen(methodInvoker->getMethodParametersSignature(event1->getObj(),event1->getObjClass(),"getTitle")) == 0);
//	BOOST_REQUIRE(std::strncmp("()Ljava/lang/String;",methodInvoker->getMethodSignature(event1->getObj(),event1->getObjClass(),"getTitle"),std::strlen("()Ljava/lang/String;")) == 0);
//
//	BOOST_REQUIRE_NO_THROW(methodInvoker->getMethodReturnSignature(event1->getObj(),event1->getObjClass(),"setId"));
//	BOOST_REQUIRE(std::strncmp("V",methodInvoker->getMethodReturnSignature(event1->getObj(),event1->getObjClass(),"setId"),std::strlen("V")) == 0);
//	BOOST_REQUIRE_NO_THROW(methodInvoker->getMethodParametersSignature(event1->getObj(),event1->getObjClass(),"setId"));
//	BOOST_REQUIRE(std::strncmp("Ljava/lang/Long;",methodInvoker->getMethodParametersSignature(event1->getObj(),event1->getObjClass(),"setId"),std::strlen("Ljava/lang/Long;")) == 0);
//	BOOST_REQUIRE(std::strncmp("(Ljava/lang/Long;)V",methodInvoker->getMethodSignature(event1->getObj(),event1->getObjClass(),"setId"),std::strlen("(Ljava/lang/Long;)V")) == 0);
//
//	BOOST_REQUIRE_NO_THROW(methodInvoker->getMethodReturnSignature(event1->getObj(),event1->getObjClass(),"getValue"));
//	BOOST_REQUIRE(std::strncmp("I",methodInvoker->getMethodReturnSignature(event1->getObj(),event1->getObjClass(),"getValue"),std::strlen("I")) == 0);
//	BOOST_REQUIRE_NO_THROW(methodInvoker->getMethodParametersSignature(event1->getObj(),event1->getObjClass(),"getValue"));
//	BOOST_REQUIRE(std::strlen(methodInvoker->getMethodParametersSignature(event1->getObj(),event1->getObjClass(),"getValue")) == 0);
//	BOOST_REQUIRE(std::strncmp("()I",methodInvoker->getMethodSignature(event1->getObj(),event1->getObjClass(),"getValue"),std::strlen("()I")) == 0);
//
//	BOOST_REQUIRE_NO_THROW(methodInvoker->getMethodReturnSignature(event1->getObj(),event1->getObjClass(),"sampleMethod"));
//	BOOST_REQUIRE(std::strncmp("Ljava/lang/Long;",methodInvoker->getMethodReturnSignature(event1->getObj(),event1->getObjClass(),"sampleMethod"),std::strlen("Ljava/lang/Long;")) == 0);
//	BOOST_REQUIRE_NO_THROW(methodInvoker->getMethodParametersSignature(event1->getObj(),event1->getObjClass(),"sampleMethod"));
//	BOOST_REQUIRE(std::strncmp("IZLjava/lang/String;Ljava/lang/Double;",methodInvoker->getMethodParametersSignature(event1->getObj(),event1->getObjClass(),"sampleMethod"),std::strlen("IZLjava/lang/String;Ljava/lang/Double;")) == 0);
//	BOOST_REQUIRE_NO_THROW(methodInvoker->getMethodSignature(event1->getObj(),event1->getObjClass(),"sampleMethod"));
//	BOOST_REQUIRE(std::strncmp("(IZLjava/lang/String;Ljava/lang/Double;)Ljava/lang/Long;",methodInvoker->getMethodSignature(event1->getObj(),event1->getObjClass(),"sampleMethod"),std::strlen("(IZLjava/lang/String;Ljava/lang/Double;)Ljava/lang/Long;")) == 0);
//
//	CppHibernateJStringObject *title = helper->createJStringObjectWith("title1");
//	event1->setVal("title",title);
//	BOOST_REQUIRE_NO_THROW(event1->invoke("setTitle",1,title));
//	CppHibernateJStringObject *rtn = NULL;
//	BOOST_REQUIRE_NO_THROW(rtn = dynamic_cast<CppHibernateJStringObject *>(event1->getVal("title")));
//	BOOST_REQUIRE(rtn != NULL);
//	BOOST_REQUIRE(std::strncmp("title1",rtn->getVal(),std::strlen("title1")) == 0);
//	CppHibernateJStringObject *rtn2 = NULL;
//	BOOST_REQUIRE_NO_THROW(rtn2 = dynamic_cast<CppHibernateJStringObject *>(event1->invoke("getTitle",0)));
//	BOOST_REQUIRE(rtn2 != NULL);
//	BOOST_REQUIRE(std::strncmp("title1",rtn2->getVal(),std::strlen("title1")) == 0);
//	CppHibernateJStringObject *title2 = helper->createJStringObjectWith("title2");
//	BOOST_REQUIRE_NO_THROW(event1->invoke("setTitle",1,title2));
//	CppHibernateJStringObject *rtn3 = NULL;
//	BOOST_REQUIRE_NO_THROW(rtn3 = dynamic_cast<CppHibernateJStringObject *>(event1->invoke("getTitle",0)));
//	BOOST_REQUIRE(rtn3 != NULL);
//	BOOST_REQUIRE(std::strncmp("title2",rtn3->getVal(),std::strlen("title2")) == 0);
//
//	CppHibernateJLongObject *l1 = helper->createJLongObjectWith(400);
//	BOOST_REQUIRE_NO_THROW(event1->invoke("setId",1,l1));
//	CppHibernateJLongObject *rtnL1 = NULL;
//	BOOST_REQUIRE_NO_THROW(rtnL1 = dynamic_cast<CppHibernateJLongObject *>(event1->invoke("getId",0)));
//	BOOST_REQUIRE(rtnL1 != NULL);
//	long lVal1 = 400;
//	BOOST_REQUIRE(lVal1 == rtnL1->getVal());
//
//	CppHibernateJObject *date1 = helper->createJObjectWith("java/util/Date");
//	BOOST_REQUIRE_NO_THROW(event1->invoke("setDate",1,date1));
//	CppHibernateJObject *rtnDate1 = NULL;
//	BOOST_REQUIRE_NO_THROW(rtnDate1 = event1->invoke("getDate",0));
//	BOOST_REQUIRE(rtnDate1 != NULL);
//	BOOST_REQUIRE(std::strncmp(date1->toString(),rtnDate1->toString(),std::strlen(date1->toString())) == 0);
//
//	CppHibernateJIntegerObject *i1 = helper->createJIntegerObjectWith(50);
//	BOOST_REQUIRE_NO_THROW(event1->invoke("setValue",1,i1));
//	CppHibernateJIntegerObject *rtnI1 = NULL;
//	BOOST_REQUIRE_NO_THROW(rtnI1 = dynamic_cast<CppHibernateJIntegerObject *>(event1->invoke("getValue",0)));
//	BOOST_REQUIRE(rtnI1 != NULL);
//	int rtnVal1 = 50;
//	BOOST_REQUIRE(rtnVal1 == rtnI1->getVal());
//
//	CppHibernateJIntegerObject *i2 = helper->createJIntegerObjectWith(20);
//	CppHibernateJBooleanObject *b1 = helper->createJBooleanObjectWith(true);
//	CppHibernateJStringObject *str1 = helper->createJStringObjectWith("check");
//	CppHibernateJDoubleObject *d1 = helper->createJDoubleObjectWith(5000);
//	CppHibernateJLongObject *rtnL2 = NULL;
//	BOOST_REQUIRE_NO_THROW(rtnL2 = dynamic_cast<CppHibernateJLongObject *>(event1->invoke("sampleMethod",4,i2,b1,str1,d1)));
//	BOOST_REQUIRE(rtnL2 != NULL);
//	long rtnVal2 = 10;
//	BOOST_REQUIRE(rtnVal2 == rtnL2->getVal());
//
//	CppHibernateJStringObject *str2 = helper->createJStringObjectWith("check2");
//	CppHibernateJBooleanObject *b2 = helper->createJBooleanObjectWith(false);
//	CppHibernateJDoubleObject* d2 = helper->createJDoubleObjectWith(60);
//	CppHibernateJLongObject *l2 = helper->createJLongObjectWith(6);
//	CppHibernateJIntegerObject *rtnL3 = NULL;
//	BOOST_REQUIRE_NO_THROW(rtnL3 = dynamic_cast<CppHibernateJIntegerObject *>(event1->invoke("sampleMethod2",4,str2,b2,d2,l2)));
//	BOOST_REQUIRE(rtnL3 != NULL);
//	int rtnVal3 = 10;
//	BOOST_REQUIRE(rtnVal3 == rtnL3->getVal());
//
//	CppHibernateJStringObject *privateRes = NULL;
//	BOOST_REQUIRE_NO_THROW(privateRes = dynamic_cast<CppHibernateJStringObject *>(event1->invoke("getPrivate",0)));
//	BOOST_REQUIRE(std::strncmp("private",privateRes->getVal(),std::strlen("private")) == 0);
//
//	CppHibernateJIntegerObject *intV = NULL;
//	BOOST_REQUIRE_NO_THROW(intV = dynamic_cast<CppHibernateJIntegerObject *>(event1->invoke("getIntV",0)));
//	BOOST_REQUIRE(20 == intV->getVal());
//
//	CppHibernateJStringObject *strV = NULL;
//	BOOST_REQUIRE_NO_THROW(strV = dynamic_cast<CppHibernateJStringObject *>(event1->invoke("getStrV",0)));
//	BOOST_REQUIRE(std::strncmp("Hello",strV->getVal(),std::strlen("Hello")) == 0);
//
//	CppHibernateJIntegerObject *intObjV = helper->createJIntegerObjectWith(200);
//	BOOST_REQUIRE_NO_THROW(event1->invoke("setIntObjV",1,intObjV));
//
//	CppHibernateJStringObject *dummyStr = helper->createJStringObjectWith("dummy");
//	BOOST_REQUIRE_THROW(event1->invoke("dummyMethod",1,dummyStr),CppHibernateException);
//	delete dummyStr;
//
//	delete intObjV;
//	delete strV;
//	delete intV;
//	delete privateRes;
//	delete l2;
//	delete rtnL3;
//	delete d2;
//	delete b2;
//	delete str2;
//	delete rtnL2;
//	delete d1;
//	delete str1;
//	delete b1;
//	delete i2;
//	delete rtnI1;
//	delete i1;
//	delete rtnDate1;
//	delete date1;
//	delete rtnL1;
//	delete l1;
//	delete rtn3;
//	delete title2;
//	delete rtn2;
//	delete rtn;
//	delete title;
//	delete event1;
//	delete methodInvoker;
//	delete helper;
//	delete loader;
//	delete configuration;
}

BOOST_AUTO_TEST_CASE(testCppHibernateSessionFactoryOpenSession) {
//	CppHibernateJVMConfiguration *configuration = new CppHibernateJVMConfiguration(ROOT_CLASS_PATH);
//	AbstractClassLoader *loader = new URLClassLoader(configuration->getJNIEnv(),HIBERNATE_LIB_LOCATION);
//	CppHibernate *hibernate = new CppHibernate(configuration,loader);
//	CppHibernateSession *session = NULL;
//	CppHibernateConnection *connection = NULL;
//
//	BOOST_REQUIRE_NO_THROW(session = hibernate->getSessionFactory()->openSession());
//	BOOST_REQUIRE(session != NULL);
//	BOOST_REQUIRE_NO_THROW(connection = session->close(false));
//	BOOST_REQUIRE(connection == NULL);
//	BOOST_REQUIRE(hibernate->getSessionFactory()->isClosed() == false);
//
//	CppHibernateSession *session2 = NULL;
//	CppHibernateConnection *connection2 = NULL;
//
//	BOOST_REQUIRE_NO_THROW(session2 = hibernate->getSessionFactory()->openSession());
//	BOOST_REQUIRE(session2 != NULL);
//	BOOST_REQUIRE_NO_THROW(connection2 = session2->close(true));
//	BOOST_REQUIRE(hibernate->getSessionFactory()->isClosed() == false);
//
//	delete session;
//	delete session2;
//	delete connection2;
//	delete loader;
//	delete hibernate;
//	delete configuration;
}

BOOST_AUTO_TEST_CASE(testBeginTransaction) {
//	CppHibernateJVMConfiguration configuration(ROOT_CLASS_PATH);
//	AbstractClassLoader *loader = new URLClassLoader(configuration.getJNIEnv(),HIBERNATE_LIB_LOCATION);
//	CppHibernateObjectHelper *helper = new CppHibernateObjectHelper(configuration.getJNIEnv(),loader);
//	CppHibernate *hibernate = new CppHibernate(&configuration,loader);
//	CppHibernateSession *session = NULL;
//	CppHibernateTransaction *transaction;
//
//	session = hibernate->getSessionFactory()->openSession();
//	BOOST_REQUIRE_NO_THROW(transaction = session->beginTransaction());
//
//	//// creates domain objects
//	CppHibernateJObject *obj = helper->createJObjectWith("org.hibernateDomain.Event");
//	CppHibernateJStringObject *title = helper->createJStringObjectWith("hibernateTitle1");
//	obj->setVal("title",title);
//
//	CppHibernateJObject *obj2 = helper->createJObjectWith("org.hibernateDomain.Event");
//	CppHibernateJStringObject *title2 = helper->createJStringObjectWith("hibernateTitle2");
//	obj2->setVal("title",title2);
//
//	CppHibernateJObject *obj3 = helper->createJObjectWith("org.hibernateDomain.Event");
//	CppHibernateJStringObject *title3 = helper->createJStringObjectWith("hibernateTitle3");
//	obj3->setVal("title",title3);
//
//	//// save domain objects
//	BOOST_REQUIRE_NO_THROW(session->saveObj(obj));
//	BOOST_REQUIRE_THROW(session->saveObj(NULL),CppHibernateException);
//	BOOST_REQUIRE_NO_THROW(session->saveObj(obj2));
//	BOOST_REQUIRE_NO_THROW(session->saveObj(obj3));
//
//	//// do some work here
//	CppHibernateCriteria criteria = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res1 = NULL;
//	BOOST_REQUIRE_NO_THROW(res1 = criteria.list());
//	BOOST_REQUIRE(res1->isEmpty() == false);
//	BOOST_REQUIRE(res1->size() == 3);
//	CppHibernateJObject *firstVal = NULL;
//	BOOST_REQUIRE_NO_THROW(firstVal = res1->get(0));
//	CppHibernateJStringObject *strVal = dynamic_cast<CppHibernateJStringObject *>(firstVal->getVal("title"));
//	BOOST_REQUIRE(std::strncmp("hibernateTitle1",strVal->getVal(),std::strlen("hibernateTitle1")) == 0);
//
//	delete strVal;
//	delete firstVal;
//	delete res1;
//
//	CppHibernateJObject *date = helper->createJObjectWith("java.util.Date");
//	obj->setVal("date",date);
//	BOOST_REQUIRE_NO_THROW(session->setFlushMode("COMMIT"));
//	BOOST_REQUIRE_THROW(session->setFlushMode("flush"),CppHibernateException);
//	BOOST_REQUIRE_NO_THROW(session->updateObj(obj));
//	BOOST_REQUIRE_NO_THROW(session->flush());
//
//	CppHibernateJCollectionObject *res2 = NULL;
//	BOOST_REQUIRE_NO_THROW(res2 = criteria.addOrderAsc("title",false).list());
//	BOOST_REQUIRE(res2->size() == 3);
//
//	//// ascending order with ignore case is false
//	int i;
//	CppHibernateJObject *element = NULL;
//	CppHibernateJStringObject *elementTitle = NULL;
//	for(i = 0; i < res2->size();i++) {
//		BOOST_REQUIRE_NO_THROW(element = res2->get(i));
//
//		elementTitle = dynamic_cast<CppHibernateJStringObject *>(element->getVal("title"));
//		std::string strTitle("hibernateTitle");
//		std::stringstream ss;
//		ss << (i + 1);
//		strTitle += ss.str();
//		std::cout << "strTitle is: " << strTitle.c_str() << " " << elementTitle->getVal() << std::endl;
//		BOOST_REQUIRE(std::strncmp(strTitle.c_str(),elementTitle->getVal(),std::strlen(strTitle.c_str())) == 0);
//
//		delete elementTitle;
//		elementTitle = NULL;
//		delete element;
//		element = NULL;
//	}
//
//	delete res2;
//
//	//// descending order with ignore case is false
//	CppHibernateJCollectionObject *res3 = NULL;
//	CppHibernateCriteria criteria2 = session->createCriteria(obj);
//	BOOST_REQUIRE_NO_THROW(res3 = criteria2.addOrderDesc("title",false).list());
//
//	CppHibernateJObject *element2 = NULL;
//	CppHibernateJStringObject *elementTitle2 = NULL;
//	for(i = 0; i < res3->size();i++) {
//		BOOST_REQUIRE_NO_THROW(element2 = res3->get(i));
//		BOOST_REQUIRE_NO_THROW(elementTitle2 = dynamic_cast<CppHibernateJStringObject *>(element2->getVal("title")));
//
//		std::string strTitle2("hibernateTitle");
//		std::stringstream ss;
//		ss << (res3->size() - i);
//		strTitle2 += ss.str();
//		std::cout << "strTitle2 " << strTitle2.c_str() << " " << elementTitle2->getVal() << std::endl;
//		BOOST_REQUIRE(std::strncmp(strTitle2.c_str(),elementTitle2->getVal(),std::strlen(strTitle2.c_str())) == 0);
//
//		delete elementTitle2;
//		elementTitle = NULL;
//		delete element2;
//		element2 = NULL;
//	}
//
//	delete res3;
//
//	//// delete domain objects
//	BOOST_REQUIRE_NO_THROW(session->deleteObj(obj));
//	BOOST_REQUIRE_NO_THROW(session->deleteObj(obj2));
//	BOOST_REQUIRE_NO_THROW(session->deleteObj(obj3));
//	BOOST_REQUIRE_THROW(session->deleteObj(NULL),CppHibernateException);
//
//	//// commit the transaction
//	BOOST_REQUIRE_NO_THROW(transaction->commit());
//	BOOST_REQUIRE(transaction != NULL);
//
//	delete date;
//	delete obj;
//	delete obj2;
//	delete obj3;
//	delete title;
//	delete title2;
//	delete title3;
//	delete helper;
//	delete transaction;
//	delete session;
//	delete loader;
//	delete hibernate;
//	//delete configuration;
}

BOOST_AUTO_TEST_CASE(testCppHibernateRestrictions) {
//	CppHibernateJVMConfiguration configuration(ROOT_CLASS_PATH);
//	AbstractClassLoader *loader = new URLClassLoader(configuration.getJNIEnv(),HIBERNATE_LIB_LOCATION);
//	CppHibernateObjectHelper *helper = new CppHibernateObjectHelper(configuration.getJNIEnv(),loader);
//	CppHibernate *hibernate = new CppHibernate(&configuration,loader);
//	CppHibernateSession *session = NULL;
//	CppHibernateTransaction *transaction = NULL;
//
//	session = hibernate->getSessionFactory()->openSession();
//	BOOST_REQUIRE_NO_THROW(transaction = session->beginTransaction());
//
//	//// creates domain objects
//	CppHibernateJObject *obj = helper->createJObjectWith("org.hibernateDomain.Event");
//	CppHibernateJStringObject *title = helper->createJStringObjectWith("hibernateTitle1");
//	obj->setVal("title",title);
//
//	CppHibernateJObject *obj2 = helper->createJObjectWith("org.hibernateDomain.Event");
//	CppHibernateJStringObject *title2 = helper->createJStringObjectWith("hibernateTitle2");
//	obj2->setVal("title",title2);
//
//	CppHibernateJObject *obj3 = helper->createJObjectWith("org.hibernateDomain.Event");
//	CppHibernateJStringObject *title3 = helper->createJStringObjectWith("hibernateTitle3");
//	obj3->setVal("title",title3);
//
//	//// save domain objects
//	session->saveObj(obj);
//	session->saveObj(obj2);
//	session->saveObj(obj3);
//
//	CppHibernateJCollectionObject *res1 = NULL;
//	CppHibernateCriteria criteria = session->createCriteria(obj);
//	criteria.addEq("title",helper->createJStringObjectWith("hibernateTitle2"));
//	res1 = criteria.list();
//	BOOST_REQUIRE(res1->size() == 1);
//	CppHibernateJObject *element = res1->get(0);
//	CppHibernateJStringObject *hibernateTitle2 = dynamic_cast<CppHibernateJStringObject *>(element->getVal("title"));
//	BOOST_REQUIRE(std::strncmp("hibernateTitle2",hibernateTitle2->getVal(),std::strlen("hibernateTitle2")) == 0);
//
//	CppHibernateCriteria criteria2 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res2 = criteria2.addGe("id",helper->createJLongObjectWith(2)).list();
//	CppHibernateJObject *element2 = NULL;
//	for(int i = 0;i < res2->size();i++) {
//		element2 = res2->get(i);
//		CppHibernateJLongObject *id = dynamic_cast<CppHibernateJLongObject *>(element2->getVal("id"));
//		long val = i + 2;
//		BOOST_REQUIRE(val == id->getVal());
//		std::stringstream ss;
//		ss << val;
//		std::string t("hibernateTitle");
//		t += ss.str();
//
//		CppHibernateJStringObject *sObj = dynamic_cast<CppHibernateJStringObject *>(element2->getVal("title"));
//		BOOST_REQUIRE(std::strncmp(t.c_str(),sObj->getVal(),std::strlen(t.c_str())) == 0);
//		delete sObj;
//		sObj = NULL;
//		delete id;
//		id = NULL;
//		delete element2;
//		element2 = NULL;
//	}
//
//	delete res2;
//	delete element;
//	delete hibernateTitle2;
//	delete res1;
//
//	CppHibernateCriteria criteria3 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res3 = criteria3.addGe("id",helper->createJLongObjectWith(2)).addOrderDesc("id").list();
//	BOOST_REQUIRE(res3->size() == 2);
//	CppHibernateJObject *element3 = NULL;
//	for(int i = 0; i < res3->size();i++) {
//		element3 = res3->get(i);
//		CppHibernateJLongObject *id = dynamic_cast<CppHibernateJLongObject *>(element3->getVal("id"));
//		long idVal = res3->size() - i + 1;
//		BOOST_REQUIRE(idVal == id->getVal());
//		std::stringstream ss;
//		ss << idVal;
//		std::string st("hibernateTitle");
//		st += ss.str();
//
//		CppHibernateJStringObject *sv = dynamic_cast<CppHibernateJStringObject *>(element3->getVal("title"));
//		BOOST_REQUIRE(std::strncmp(st.c_str(),sv->getVal(),std::strlen(st.c_str())) == 0);
//
//		delete sv;
//		sv = NULL;
//		delete id;
//		id = NULL;
//	}
//
//	delete res3;
//
//	CppHibernateCriteria criteria4 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res4 = criteria4.addBetween("id",helper->createJLongObjectWith(2),helper->createJLongObjectWith(3)).list();
//	BOOST_REQUIRE(res4->size() == 2);
//	delete res4;
//
//	CppHibernateCriteria criteria5 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res5 = criteria5.addGt("id",helper->createJLongObjectWith(2)).list();
//	BOOST_REQUIRE(res5->size() == 1);
//	delete res5;
//
//	CppHibernateCriteria criteria6 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res6 = criteria6.addIdEq(helper->createJLongObjectWith(3)).list();
//	BOOST_REQUIRE(res6->size() == 1);
//	CppHibernateJObject *el = res6->get(0);
//	CppHibernateJStringObject *elStr = dynamic_cast<CppHibernateJStringObject *>(el->getVal("title"));
//	BOOST_REQUIRE(std::strncmp("hibernateTitle3",elStr->getVal(),std::strlen("hibernateTitle3")) == 0);
//	delete elStr;
//	delete el;
//	delete res6;
//
//	CppHibernateCriteria criteria7 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res7 = criteria7.addIdEq(helper->createJLongObjectWith(6)).list();
//	BOOST_REQUIRE(res7->size() == 0);
//	BOOST_REQUIRE(res7->isEmpty() == true);
//	delete res7;
//
//	CppHibernateCriteria criteria8 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res8 = criteria8.addIlike("title",helper->createJStringObjectWith("title"),CppHibernateMatchMode::ANYWHERE).list();
//	BOOST_REQUIRE(res8->size() == 3);
//	delete res8;
//
//	CppHibernateCriteria criteria9 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res9 = criteria9.addIlike("title",helper->createJStringObjectWith("2"),CppHibernateMatchMode::END).list();
//	BOOST_REQUIRE(res9->size() == 1);
//	CppHibernateJObject *el2 = res9->get(0);
//	CppHibernateJStringObject *s2 = dynamic_cast<CppHibernateJStringObject *>(el2->getVal("title"));
//	BOOST_REQUIRE(std::strncmp("hibernateTitle2",s2->getVal(),std::strlen("hibernateTitle2")) == 0);
//	delete s2;
//	delete el2;
//	delete res9;
//
//	CppHibernateCriteria criteria10 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res10 = criteria10.addIlike("title",helper->createJStringObjectWith("hibernateTitle11"),CppHibernateMatchMode::EXACT).list();
//	BOOST_REQUIRE(res10->isEmpty() == true);
//	delete res10;
//
//	CppHibernateCriteria criteria11 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res11 = criteria11.addIlike("title",helper->createJStringObjectWith("hibernateTitle1"),CppHibernateMatchMode::EXACT).list();
//	BOOST_REQUIRE(res11->size() == 1);
//	delete res11;
//
//	CppHibernateCriteria criteria12 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res12 = criteria12.addIlike("title",helper->createJStringObjectWith("hibernate"),CppHibernateMatchMode::START).addOrderDesc("title").list();
//	CppHibernateJObject *e1 = res12->get(0);
//	CppHibernateJStringObject *e1Str = dynamic_cast<CppHibernateJStringObject *>(e1->getVal("title"));
//	BOOST_REQUIRE(std::strncmp("hibernateTitle3",e1Str->getVal(),std::strlen("hibernateTitle3")) == 0);
//	delete e1Str;
//	delete e1;
//	delete res12;
//
//	CppHibernateCriteria criteria13 = session->createCriteria(obj);
//	BOOST_REQUIRE_THROW(criteria13.addIlike("title",helper->createJStringObjectWith("hibernate"),"GOOGLE").list(),CppHibernateException);
//
//	CppHibernateCriteria criteria14 = session->createCriteria(obj);
//	std::deque<CppHibernateJObject *> objects;
//	objects.push_back(helper->createJStringObjectWith("google"));
//	objects.push_back(helper->createJStringObjectWith("yahoo"));
//	objects.push_back(helper->createJStringObjectWith("apple"));
//	CppHibernateJCollectionObject *res14 = criteria14.addIn("title",objects).list();
//	BOOST_REQUIRE(res14->isEmpty() == true);
//	BOOST_REQUIRE(objects.size() == 0);
//	delete res14;
//
//	CppHibernateCriteria criteria15 = session->createCriteria(obj);
//	objects.push_back(helper->createJLongObjectWith(6));
//	objects.push_back(helper->createJLongObjectWith(7));
//	objects.push_back(helper->createJLongObjectWith(2));
//	CppHibernateJCollectionObject *res15 = criteria15.addIn("id",objects).list();
//	BOOST_REQUIRE(res15->size() == 1);
//	CppHibernateJObject *o1 = res15->get(0);
//	CppHibernateJStringObject *o1Str = dynamic_cast<CppHibernateJStringObject *>(o1->getVal("title"));
//	BOOST_REQUIRE(std::strncmp("hibernateTitle2",o1Str->getVal(),std::strlen("hibernateTitle2")) == 0);
//	delete o1Str;
//	delete o1;
//	delete res15;
//
//	CppHibernateCriteria criteria16 = session->createCriteria(obj);
//	BOOST_REQUIRE_THROW(criteria16.addIn("title",objects).list(),CppHibernateException);
//
//	CppHibernateCriteria criteria17 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res17 = criteria17.addIsNotNULL("title").list();
//	BOOST_REQUIRE(res17->size() == 3);
//	delete res17;
//
//	CppHibernateCriteria criteria18 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res18 = criteria18.addIsNotNULL("date").list();
//	BOOST_REQUIRE(res18->isEmpty() == true);
//	delete res18;
//
//	CppHibernateCriteria criteria19 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res19 = criteria19.addIsNULL("date").list();
//	BOOST_REQUIRE(res19->size() == 3);
//	delete res19;
//
//	CppHibernateCriteria criteria20 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res20 = criteria20.addIsNULL("title").list();
//	BOOST_REQUIRE(res20->isEmpty() == true);
//	delete res20;
//
//	CppHibernateCriteria criteria21 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res21 = criteria21.addLe("id",helper->createJLongObjectWith(0)).list();
//	BOOST_REQUIRE(res21->isEmpty() == true);
//	delete res21;
//
//	CppHibernateCriteria criteria22 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res22 = criteria22.addLe("id",helper->createJLongObjectWith(100)).list();
//	BOOST_REQUIRE(res22->size() == 3);
//	delete res22;
//
//	CppHibernateCriteria criteria23 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res23 = criteria23.addLe("id",helper->createJLongObjectWith(4)).addIsNotNULL("title").addIlike("title",helper->createJStringObjectWith("2"),CppHibernateMatchMode::END).addIdEq(helper->createJLongObjectWith(2)).list();
//	BOOST_REQUIRE(res23->size() == 1);
//	CppHibernateJObject *el23 = res23->get(0);
//	CppHibernateJStringObject *el23Str = dynamic_cast<CppHibernateJStringObject *>(el23->getVal("title"));
//	BOOST_REQUIRE(std::strncmp("hibernateTitle2",el23Str->getVal(),std::strlen("hibernateTitle2")) == 0);
//	delete el23Str;
//	delete el23;
//	delete res23;
//
//	CppHibernateCriteria criteria24 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res24 = criteria24.addLike("title",helper->createJStringObjectWith("Hibernate")).list();
//	BOOST_REQUIRE(res24->isEmpty() == true);
//	delete res24;
//
//	CppHibernateCriteria criteria25 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res25 = criteria25.addLike("title",helper->createJStringObjectWith("hibernate")).list();
//	BOOST_REQUIRE(res25->size() == 3);
//	delete res25;
//
//	CppHibernateCriteria criteria26 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res26 = criteria26.addLike("title",helper->createJStringObjectWith("Title"),CppHibernateMatchMode::ANYWHERE).list();
//	BOOST_REQUIRE(res26->size() == 3);
//	delete res26;
//
//	CppHibernateCriteria criteria27 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res27 = criteria27.addLt("id",helper->createJLongObjectWith(2)).list();
//	BOOST_REQUIRE(res27->size() == 1);
//	CppHibernateJObject *obj27 = res27->get(0);
//	CppHibernateJStringObject *obj27Str = dynamic_cast<CppHibernateJStringObject *>(obj27->getVal("title"));
//	BOOST_REQUIRE(std::strncmp("hibernateTitle1",obj27Str->getVal(),std::strlen("hibernateTitle1")) == 0);
//	delete obj27Str;
//	delete obj27;
//	delete res27;
//
//	CppHibernateCriteria criteria28 = session->createCriteria(obj);
//	CppHibernateJCollectionObject *res28 = criteria28.addNe("title",helper->createJStringObjectWith("hibernateTitle1")).setCachable(true).setCacheRegion("org.hibernateDomain.Event").list();
//	BOOST_REQUIRE(res28->size() == 2);
//	delete res28;
//
//	CppHibernateSessionStatistics *sessionStatistics = NULL;
//	BOOST_REQUIRE_NO_THROW(sessionStatistics = session->getStatistics());
//	BOOST_REQUIRE(sessionStatistics != NULL);
//	int collectionCount = -1;
//	BOOST_REQUIRE_NO_THROW(collectionCount = sessionStatistics->getCollectionCount());
//	BOOST_REQUIRE(collectionCount == 0);
//	CppHibernateJCollectionObject *keys = NULL;
//	BOOST_REQUIRE_NO_THROW(keys = sessionStatistics->getCollectionKeys());
//	BOOST_TEST_MESSAGE(keys->toString());
//	BOOST_REQUIRE(keys->size() == 0);
//	BOOST_REQUIRE(keys->isEmpty() == true);
//	int count = -1;
//	BOOST_REQUIRE_NO_THROW(count = sessionStatistics->getEntityCount());
//	BOOST_REQUIRE(count == 3);
//	CppHibernateJCollectionObject *entityKeys = NULL;
//	BOOST_REQUIRE_NO_THROW(entityKeys = sessionStatistics->getEntityKeys());
//	BOOST_REQUIRE(entityKeys->size() == 3);
//	BOOST_TEST_MESSAGE(sessionStatistics->toString());
//	delete entityKeys;
//	delete keys;
//	delete sessionStatistics;
//
//	CppHibernateStatistics *st = NULL;
//	BOOST_REQUIRE_NO_THROW(st = hibernate->getSessionFactory()->getStatistics());
//	BOOST_REQUIRE(st != NULL);
//
//	long closeStatementCount = -1;
//	BOOST_REQUIRE_NO_THROW(closeStatementCount = st->getCloseStatementCount());
//	BOOST_TEST_MESSAGE("closeStatementCount is " << closeStatementCount);
//
//	long collectionFetchCount = -1;
//	BOOST_REQUIRE_NO_THROW(collectionFetchCount = st->getCollectionFetchCount());
//	BOOST_TEST_MESSAGE("collectionFetchCount is " << collectionFetchCount);
//
//	long collectionLoadCount = -1;
//	BOOST_REQUIRE_NO_THROW(collectionLoadCount = st->getCollectionLoadCount());
//	BOOST_TEST_MESSAGE("collectionLoadCount is: " << collectionLoadCount);
//
//	long collectionRecreateCount = -1;
//	BOOST_REQUIRE_NO_THROW(collectionRecreateCount = st->getCollectionRecreateCount());
//	BOOST_TEST_MESSAGE("collectionRecreateCount is: " << collectionRecreateCount);
//
//	long collectionRemoveCount = -1;
//	BOOST_REQUIRE_NO_THROW(collectionRemoveCount = st->getCollectionRemoveCount());
//	BOOST_TEST_MESSAGE("collectionRemoveCount is: " << collectionRemoveCount);
//
//	std::deque<std::string> roleNames;
//	BOOST_REQUIRE_NO_THROW(roleNames = st->getCollectionRoleNames());
//
//	CppHibernateCollectionStatistics *collectionStatistics = NULL;
//	BOOST_REQUIRE_NO_THROW(collectionStatistics = st->getCollectionStatistics(""));
//	delete collectionStatistics;
//
//	long updateCount = -1;
//	BOOST_REQUIRE_NO_THROW(updateCount = st->getCollectionUpdateCount());
//
//	long connectCount = -1;
//	BOOST_REQUIRE_NO_THROW(connectCount = st->getConnectCount());
//
//	long deleteEntityCount = -1;
//	BOOST_REQUIRE_NO_THROW(deleteEntityCount = st->getEntityDeleteCount());
//
//	long fetchEntityCount = -1;
//	BOOST_REQUIRE_NO_THROW(fetchEntityCount = st->getEntityFetchCount());
//
//	long insertEntityCount = -1;
//	BOOST_REQUIRE_NO_THROW(insertEntityCount = st->getEntityInsertCount());
//
//	long loadEntityCount = -1;
//	BOOST_REQUIRE_NO_THROW(loadEntityCount = st->getEntityLoadCount());
//
//	std::deque<std::string> entityNames;
//	BOOST_REQUIRE_NO_THROW(entityNames = st->getEntityNames());
//
//	std::cout << "toString: " << st->toString() << std::endl;
//
//	CppHibernateEntityStatistics *entityStatistics = NULL;
//	BOOST_REQUIRE_NO_THROW(entityStatistics = st->getEntityStatistics("org.hibernateDomain.Event"));
//	BOOST_REQUIRE(entityStatistics != NULL);
//	long entityDeleteCount = -1;
//	BOOST_REQUIRE_NO_THROW(entityDeleteCount = entityStatistics->getDeleteCount());
//	BOOST_TEST_MESSAGE("entity delete count: " << entityDeleteCount);
//	long entityFetchCount = -1;
//	BOOST_REQUIRE_NO_THROW(entityFetchCount = entityStatistics->getFetchCount());
//	BOOST_TEST_MESSAGE("entity fetch count: " << entityFetchCount);
//	long entityInsertCount = -1;
//	BOOST_REQUIRE_NO_THROW(entityInsertCount = entityStatistics->getInsertCount());
//	BOOST_TEST_MESSAGE("entity insert count: " << entityInsertCount);
//	BOOST_REQUIRE(entityInsertCount == 3);
//	long entityLoadCount = -1;
//	BOOST_REQUIRE_NO_THROW(entityLoadCount = entityStatistics->getLoadCount());
//	BOOST_TEST_MESSAGE("entity load count: " << entityLoadCount);
//	long entityOptimisticFailureCount = -1;
//	BOOST_REQUIRE_NO_THROW(entityOptimisticFailureCount = entityStatistics->getOptimisticFailureCount());
//	BOOST_TEST_MESSAGE("optimistic failure count: " << entityOptimisticFailureCount);
//	long entityUpdateCount = -1;
//	BOOST_REQUIRE_NO_THROW(entityUpdateCount = entityStatistics->getUpdateCount());
//	BOOST_TEST_MESSAGE("entity update count: " << entityUpdateCount);
//
//	long entityUpdateCountGlobal = -1;
//	BOOST_REQUIRE_NO_THROW(entityUpdateCountGlobal = st->getEntityUpdateCount());
//	BOOST_TEST_MESSAGE("global entity update count: " << entityUpdateCountGlobal);
//
//	long flushCount = -1;
//	BOOST_REQUIRE_NO_THROW(flushCount = st->getFlushCount());
//	BOOST_TEST_MESSAGE("flush count: " << flushCount);
//
//	long optimisticFailureCount = -1;
//	BOOST_REQUIRE_NO_THROW(optimisticFailureCount = st->getOptimisticFailureCount());
//	BOOST_TEST_MESSAGE("optimistic failure count: " << optimisticFailureCount);
//
//	long prepareStatementCount = -1;
//	BOOST_REQUIRE_NO_THROW(prepareStatementCount = st->getPrepareStatementCount());
//	BOOST_TEST_MESSAGE("prepare statement count: " << prepareStatementCount);
//
//	std::deque<std::string> queries;
//	BOOST_REQUIRE_NO_THROW(queries = st->getQueries());
//
//	long queryCacheHitCount = -1;
//	BOOST_REQUIRE_NO_THROW(queryCacheHitCount = st->getQueryCacheHitCount());
//	BOOST_TEST_MESSAGE("query cache hit count: " << queryCacheHitCount);
//
//	long queryCacheMissCount = -1;
//	BOOST_REQUIRE_NO_THROW(queryCacheMissCount = st->getQueryCacheMissCount());
//	BOOST_TEST_MESSAGE("query cache miss count: " << queryCacheMissCount);
//
//	long queryCachePutCount = -1;
//	BOOST_REQUIRE_NO_THROW(queryCachePutCount = st->getQueryCachePutCount());
//	BOOST_TEST_MESSAGE("query cache put count: " << queryCachePutCount);
//
//	long queryExecutionCount = -1;
//	BOOST_REQUIRE_NO_THROW(queryExecutionCount = st->getQueryExecutionCount());
//	BOOST_TEST_MESSAGE("query execution count: " << queryExecutionCount);
//
//	long queryExecutionMaxTime = -1;
//	BOOST_REQUIRE_NO_THROW(queryExecutionMaxTime = st->getQueryExecutionMaxTime());
//	BOOST_TEST_MESSAGE("query execution max time: " << queryExecutionMaxTime);
//
//	std::string queryName;
//	BOOST_REQUIRE_NO_THROW(queryName = st->getQueryExecutionMaxTimeQueryString());
//	BOOST_TEST_MESSAGE("query execution max time: " << queryName.c_str());
//
//	CppHibernateQueryStatistics *queryStatistics = NULL;
//	BOOST_REQUIRE_NO_THROW(queryStatistics = st->getQueryStatistics(""));
//	BOOST_REQUIRE(queryStatistics != NULL);
//	delete queryStatistics;
//
//	long secondLevelHitCount = -1;
//	BOOST_REQUIRE_NO_THROW(secondLevelHitCount = st->getSecondLevelCacheHitCount());
//	BOOST_TEST_MESSAGE("second level hit count: " << secondLevelHitCount);
//
//	long secondLevelMissCount = -1;
//	BOOST_REQUIRE_NO_THROW(secondLevelMissCount = st->getSecondLevelCacheMissCount());
//	BOOST_TEST_MESSAGE("second level miss count: " << secondLevelMissCount);
//
//	long secondLevelPutCount = -1;
//	BOOST_REQUIRE_NO_THROW(secondLevelPutCount = st->getSecondLevelCachePutCount());
//	BOOST_TEST_MESSAGE("second level put count: " << secondLevelPutCount);
//
//	std::deque<std::string> regionNames;
//	BOOST_REQUIRE_NO_THROW(regionNames = st->getSecondLevelCacheRegionNames());
//
//	CppHibernateSecondLevelCacheStatistics *secondLevelCacheStatistics = NULL;
//	BOOST_TEST_MESSAGE("is statistics enabled? : " << st->isStatisticsEnabled());
//	BOOST_REQUIRE_NO_THROW(secondLevelCacheStatistics = st->getSecondLevelCacheStatistics("org.hibernateDomain.Event"));
//	BOOST_TEST_MESSAGE("second level cache statistics: " << secondLevelCacheStatistics->toString());
//	delete secondLevelCacheStatistics;
//
//	long sessionCloseCount = -1;
//	BOOST_REQUIRE_NO_THROW(sessionCloseCount = st->getSessionCloseCount());
//	BOOST_TEST_MESSAGE("session close count: " << sessionCloseCount);
//
//	long sessionOpenCount = -1;
//	BOOST_REQUIRE_NO_THROW(sessionOpenCount = st->getSessionOpenCount());
//	BOOST_TEST_MESSAGE("session open count: " << sessionOpenCount);
//
//	long startTime = -1;
//	BOOST_REQUIRE_NO_THROW(startTime = st->getStartTime());
//	BOOST_TEST_MESSAGE("start time: " << startTime);
//
//	long successfulTransactionCount = -1;
//	BOOST_REQUIRE_NO_THROW(successfulTransactionCount = st->getSuccessfulTransactionCount());
//	BOOST_TEST_MESSAGE("successful transaction count: " << successfulTransactionCount);
//
//	long transactionCount = -1;
//	BOOST_REQUIRE_NO_THROW(transactionCount = st->getTransactionCount());
//	BOOST_TEST_MESSAGE("transaction count: " << transactionCount);
//
//	bool isEnabled = false;
//	BOOST_REQUIRE_NO_THROW(isEnabled = st->isStatisticsEnabled());
//	BOOST_REQUIRE(isEnabled == true);
//
//	BOOST_REQUIRE_NO_THROW(st->clear());
//	delete st;
//
//	//// delete domain objects
//	session->deleteObj(obj);
//	session->deleteObj(obj2);
//	session->deleteObj(obj3);
//
//	//// commit the transaction
//	BOOST_REQUIRE_NO_THROW(transaction->commit());
//	BOOST_REQUIRE(transaction != NULL);
//
//	delete helper;
//	delete transaction;
//	delete session;
//	delete loader;
//	delete hibernate;
}

BOOST_AUTO_TEST_CASE(testCppHibernateQuery) {
//	CppHibernateJVMConfiguration configuration(ROOT_CLASS_PATH);
//	AbstractClassLoader *loader = new URLClassLoader(configuration.getJNIEnv(),HIBERNATE_LIB_LOCATION);
//	CppHibernateObjectHelper *helper = new CppHibernateObjectHelper(configuration.getJNIEnv(),loader);
//	CppHibernate *hibernate = new CppHibernate(&configuration,loader);
//	CppHibernateSession *session = NULL;
//	CppHibernateTransaction *transaction = NULL;
//
//	session = hibernate->getSessionFactory()->getCurrentSession();
//	BOOST_REQUIRE_NO_THROW(transaction = session->beginTransaction());
//
//	CppHibernateJObject *obj1 = helper->createJObjectWith("org.hibernateDomain.Event");
//	CppHibernateJStringObject *obj1Str = helper->createJStringObjectWith("title1");
//	obj1->setVal("title",obj1Str);
//	session->saveObj(obj1);
//	CppHibernateJObject *obj2 = helper->createJObjectWith("org.hibernateDomain.Event");
//	CppHibernateJStringObject *obj2Str = helper->createJStringObjectWith("title2");
//	obj2->setVal("title",obj2Str);
//	session->saveObj(obj2);
//	CppHibernateJObject *obj3 = helper->createJObjectWith("org.hibernateDomain.Event");
//	CppHibernateJStringObject *obj3Str = helper->createJStringObjectWith("title3");
//	obj3->setVal("title",obj3Str);
//	session->saveObj(obj3);
//	CppHibernateJObject *obj4 = helper->createJObjectWith("org.hibernateDomain.Event");
//	CppHibernateJStringObject *obj4Str = helper->createJStringObjectWith("title4");
//	obj4->setVal("title",obj4Str);
//	session->saveObj(obj4);
//
//	delete obj1;
//	delete obj2;
//	delete obj3;
//	delete obj4;
//
//	CppHibernateQuery query = session->createQuery("from Event");
//	CppHibernateJCollectionObject *res1 = query.list();
//	BOOST_REQUIRE(res1->size() == 4);
//	delete res1;
//
//	CppHibernateQuery query2 = session->createQuery("from Event event where event.id = 2");
//	CppHibernateJCollectionObject *res2 = query2.list();
//	BOOST_REQUIRE(res2->size() == 1);
//	CppHibernateJObject *el2 = res2->get(0);
//	CppHibernateJStringObject *res2Str = dynamic_cast<CppHibernateJStringObject *>(el2->getVal("title"));
//	BOOST_REQUIRE(std::strncmp("title2",res2Str->getVal(),std::strlen("title2")) == 0);
//	delete res2Str;
//	delete el2;
//	delete res2;
//
//	CppHibernateQuery query3 = session->createQuery("from Event event where event.id > 2");
//	CppHibernateJCollectionObject *res3 = query3.list();
//	BOOST_REQUIRE(res3->size() == 2);
//	CppHibernateJObject *el32 = res3->get(0);
//	CppHibernateJStringObject *el32Str = dynamic_cast<CppHibernateJStringObject *>(el32->getVal("title"));
//	BOOST_REQUIRE(std::strncmp("title3",el32Str->getVal(),std::strlen("title3")) == 0);
//	CppHibernateJObject *el33 = res3->get(1);
//	CppHibernateJStringObject *el33Str = dynamic_cast<CppHibernateJStringObject *>(el33->getVal("title"));
//	BOOST_REQUIRE(std::strncmp("title4",el33Str->getVal(),std::strlen("title4")) == 0);
//	delete el33Str;
//	delete el33;
//	delete el32Str;
//	delete el32;
//	delete res3;
//
//	CppHibernateQuery query4 = session->createQuery("from Event event where event.id > 1");
//	CppHibernateJCollectionObject *res4 = query4.setMaxResults(2).list();
//	BOOST_REQUIRE(res4->size() == 2);
//	CppHibernateJObject *res42 = res4->get(0);
//	CppHibernateJStringObject *res42Str = dynamic_cast<CppHibernateJStringObject *>(res42->getVal("title"));
//	BOOST_REQUIRE(std::strncmp("title2",res42Str->getVal(),std::strlen("title2")) == 0);
//	CppHibernateJObject *res43 = res4->get(1);
//	CppHibernateJStringObject * res43Str = dynamic_cast<CppHibernateJStringObject *>(res43->getVal("title"));
//	BOOST_REQUIRE(std::strncmp("title3",res43Str->getVal(),std::strlen("title3")) == 0);
//	delete res43Str;
//	delete res43;
//	delete res42Str;
//	delete res42;
//	delete res4;
//
//	CppHibernateQuery query5 = session->createQuery("from Event event where event.id > 3");
//	CppHibernateJCollectionObject *res5 = query5.setMaxResults(5).list();
//	BOOST_REQUIRE(res5->size() == 1);
//	delete res5;
//
//	CppHibernateQuery query6 = session->createQuery("from Event event where event.id > 2");
//	BOOST_REQUIRE_THROW(query6.setMaxResults(0).list(),CppHibernateException);
//
//	CppHibernateQuery query7 = session->createQuery("from Event event where event.title is not null");
//	CppHibernateJCollectionObject *res7 = query7.setMaxResults(1).list();
//	BOOST_REQUIRE(res7->size() == 1);
//	delete res7;
//
//	CppHibernateQuery query8 = session->createQuery("from Event event where event.title = :t");
//	CppHibernateJCollectionObject *res8 = query8.setParameter(helper->createJStringObjectWith("t"),helper->createJStringObjectWith("title4")).list();
//	BOOST_REQUIRE(res8->size() == 1);
//	delete res8;
//
//	CppHibernateQuery query9 = session->createQuery("from Event event where event.id > :i and event.title = :t");
//	CppHibernateJCollectionObject *res9 = query9.setParameter(helper->createJStringObjectWith("i"),helper->createJLongObjectWith(2)).setParameter(helper->createJStringObjectWith("t"),helper->createJStringObjectWith("title3")).list();
//	BOOST_REQUIRE(res9->size() == 1);
//	CppHibernateJObject *res9El = res9->get(0);
//	CppHibernateJStringObject *res9Str = dynamic_cast<CppHibernateJStringObject *>(res9El->getVal("title"));
//	BOOST_REQUIRE(std::strncmp("title3",res9Str->getVal(),std::strlen("title3")) == 0);
//	delete res9Str;
//	delete res9El;
//	delete res9;
//
//	//// commit the transaction
//	BOOST_REQUIRE_NO_THROW(transaction->commit());
//	BOOST_REQUIRE(transaction != NULL);
//
//	delete helper;
//	delete transaction;
//	delete session;
//	delete loader;
//	delete hibernate;
}

BOOST_AUTO_TEST_CASE(testForSample) {
//	CppHibernateJVMConfiguration configuration(ROOT_CLASS_PATH);
//	URLClassLoader loader = URLClassLoader(configuration.getJNIEnv(),HIBERNATE_LIB_LOCATION);
//	CppHibernateObjectHelper helper = CppHibernateObjectHelper(configuration.getJNIEnv(),&loader);
//	CppHibernate hibernate = CppHibernate(&configuration,&loader);
//
//	CppHibernateSession *session = hibernate.getSessionFactory()->getCurrentSession();
//	CppHibernateTransaction *transaction = session->beginTransaction();
//
//	CppHibernateJObject *obj1 = helper.createJObjectWith("org.hibernateDomain.Event");
//	CppHibernateJStringObject *obj1Str = helper.createJStringObjectWith("title1");
//	obj1->setVal("title",obj1Str);
//	session->saveObj(obj1);
//
//	CppHibernateCriteria criteria = session->createCriteria(obj1);
//	CppHibernateJCollectionObject *res = criteria.addLe("id",helper.createJLongObjectWith(4)).addIsNotNULL("title").addIlike("title",helper.createJStringObjectWith("1"),"END").addIdEq(helper.createJLongObjectWith(1)).list();
//	BOOST_REQUIRE(res->size() == 1);
//
//	CppHibernateQuery query = session->createQuery("from Event event where event.id > :i and event.title = :t");
//	CppHibernateJCollectionObject *res2 = query.setParameter(helper.createJStringObjectWith("i"),helper.createJLongObjectWith(0)).setParameter(helper.createJStringObjectWith("t"),helper.createJStringObjectWith("title1")).list();
//	BOOST_REQUIRE(res2->size() == 1);
//	transaction->commit();
//
//	delete res;
//	delete res2;
//	delete obj1;
//	delete obj1Str;
//	delete transaction;
//	delete session;
}

BOOST_AUTO_TEST_CASE(testCppHibernateSecondLevelCache) {

	CppHibernateJVMConfiguration configuration(ROOT_CLASS_PATH);
	URLClassLoader loader = URLClassLoader(configuration.getJNIEnv(),HIBERNATE_LIB_LOCATION);
	CppHibernateObjectHelper helper = CppHibernateObjectHelper(configuration.getJNIEnv(),&loader);
	CppHibernate hibernate = CppHibernate(&configuration,&loader);

	CppHibernateSession *session = hibernate.getSessionFactory()->getCurrentSession();
	CppHibernateTransaction *transaction = session->beginTransaction();

	CppHibernateJObject *obj1 = helper.createJObjectWith("org.hibernateDomain.Event");
	CppHibernateJStringObject *obj1Str = helper.createJStringObjectWith("title1");
	obj1->setVal("title",obj1Str);
	session->saveObj(obj1);

	CppHibernateCriteria criteria = session->createCriteria(obj1);
	CppHibernateJCollectionObject *res = criteria.addLe("id",helper.createJLongObjectWith(4)).addIsNotNULL("title").addIlike("title",helper.createJStringObjectWith("1"),"END").addIdEq(helper.createJLongObjectWith(1)).list();
	BOOST_REQUIRE(res->size() == 1);

	CppHibernateQuery query = session->createQuery("from Event event where event.id > :i and event.title = :t");
	CppHibernateJCollectionObject *res2 = query.setParameter(helper.createJStringObjectWith("i"),helper.createJLongObjectWith(0)).setParameter(helper.createJStringObjectWith("t"),helper.createJStringObjectWith("title1")).setCacheable(true).setCacheRegion("org.hibernateDomain.Event").list();
	BOOST_REQUIRE(res2->size() == 1);
	transaction->commit();

	delete res;
	delete res2;
	delete obj1;
	delete obj1Str;
	delete transaction;
	delete session;

	CppHibernateStatistics *statistics = hibernate.getSessionFactory()->getStatistics();
	BOOST_TEST_MESSAGE("statistics: " << statistics->toString());
	CppHibernateSecondLevelCacheStatistics *secondLevelCacheStatistics = statistics->getSecondLevelCacheStatistics("org.hibernateDomain.Event");
	if(secondLevelCacheStatistics != NULL) {
		BOOST_TEST_MESSAGE("second level cache statistics: " << secondLevelCacheStatistics->toString());
		delete secondLevelCacheStatistics;
	} else {
		BOOST_TEST_MESSAGE("second level cache statistics is not available");
	}
	delete statistics;
}

BOOST_AUTO_TEST_SUITE_END()
