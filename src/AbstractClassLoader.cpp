/*
 * AbstractClassLoader.cpp
 *  This class is not intended to be instantiated directly. Use the concrete subclass instead.
 *  Created on: Nov 4, 2011
 *      Author: apple
 */

#include <memory>
#include <unistd.h>
#include <dirent.h>
#include <sstream>

#include "AbstractClassLoader.h"

namespace cppHibernate {

AbstractClassLoader::AbstractClassLoader(JNIEnv *env) :
		classPaths(new std::deque<std::string*>), PERIOD("."), UNIX_SEPARATOR(
				"/"), LOWER_CASE_JAR("jar"), UPPER_CASE_JAR("JAR"), JAVA_IO_FILE(
				"java/io/File"), JAVA_CONSTRUCTOR_NAME("<init>"), JAVA_IO_FILE_EXIST_NAME(
				"exists"), JAVA_IO_FILE_TOURI_NAME("toURI"), JAVA_NET_URI(
				"java/net/URI"), JAVA_NET_URI_TOURL_NAME("toURL"), JAVA_NET_URL(
				"java/net/URL"), JAVA_LANG_CLASSLOADER_LOADCLASS_NAME(
				"loadClass"), JAVA_LANG_CLASSLOADER_FINDCLASS_NAME("findClass"), classLoader(
				NULL), classLoaderClass(NULL) {

	this->env = env;
}

AbstractClassLoader::AbstractClassLoader() :
		classPaths(new std::deque<std::string*>), PERIOD("."), UNIX_SEPARATOR(
				"/"), LOWER_CASE_JAR("jar"), UPPER_CASE_JAR("JAR"), JAVA_IO_FILE(
				"java.io.File"), JAVA_CONSTRUCTOR_NAME("<init>"), JAVA_IO_FILE_EXIST_NAME(
				"exists"), JAVA_IO_FILE_TOURI_NAME("toURI"), JAVA_NET_URI(
				"java/net/URI"), JAVA_NET_URI_TOURL_NAME("toURL"), JAVA_NET_URL(
				"java/net/URL"), JAVA_LANG_CLASSLOADER_LOADCLASS_NAME(
				"loadClass"), JAVA_LANG_CLASSLOADER_FINDCLASS_NAME("findClass"), classLoader(
				NULL), classLoaderClass(NULL) {

}

/**
 * Creates a java.io.File object from the path specified by the parameter.
 * @param const char* path Used to convert it to java.io.File object.
 * @return jobject Returns an object representing java.io.File> Returns NULL when the specified path is invalid
 * or when env property, JNIEnv is NULL. The returned object must be released once the job is done when it's successfully created.
 * @throw Throws when JNI encounters an exception.
 */
jobject AbstractClassLoader::createFileFrom(const char *path) {

	if (this->isEnvNull()) {
		return NULL;
	}

	jobject fileObj = NULL;
	jclass fileClass = this->env->FindClass(this->JAVA_IO_FILE);

	if (fileClass != NULL) {

		jmethodID fileClassCtorId = this->env->GetMethodID(fileClass,
				this->JAVA_CONSTRUCTOR_NAME, "(Ljava/lang/String;)V");

		if (fileClassCtorId != NULL) {

			jstring pathUTF = this->env->NewStringUTF(path);
			jobject fileLocalObj = this->env->NewObject(fileClass,
					fileClassCtorId, pathUTF);

			if (this->exist(fileClass, fileLocalObj)) {
				fileObj = this->env->NewGlobalRef(fileLocalObj);
			}

			this->env->DeleteLocalRef(pathUTF);
		} else {
			this->throwException();
		}
	} else {
		this->throwException();
	}

	return fileObj;
}

/**
 * Checks if env property is null or not.
 * @return bool True if it's NULL, false otherwise.
 */
bool AbstractClassLoader::isEnvNull() {
	if (this->env == NULL) {
		return true;
	}

	return false;
}

/**
 *	Checks if the specified java.io.File object has a valid,existing path or not.
 *  @param jclass fileClass Represents java.io.File class.
 *	@param jobject fileObj Examined java.io.File object.
 *	@return bool Returns true if it's valid, false otherwise.
 */
bool AbstractClassLoader::exist(jclass fileClass, jobject fileObj) {

	jmethodID existId = this->env->GetMethodID(fileClass,
			this->JAVA_IO_FILE_EXIST_NAME, "()Z");

	if (existId != NULL) {
		if (this->env->CallBooleanMethod(fileObj, existId) == JNI_TRUE) {
			return true;
		}
	} else {
		this->throwException();
	}

	return false;
}

/**
 * Creates a java.net.URI object from the parameter object.
 * @param jobject obj Used to create a java.net.URI object.
 * @return jobject Returns jobject representing java.net.URI.
 * The returned object must be released once the job is done when it's successfully created or
 * NULL when the specified path is invalid or when env property, JNIEnv is NULL.
 * @throw Throws when JNI encounters an exception.
 */
jobject AbstractClassLoader::createURIFrom(jobject fileObj) {

	////TODO need to add checking if the input object is an expected one or not.

	if (fileObj == NULL) {
		return NULL;
	}

	if (this->isEnvNull()) {
		return NULL;
	}

	jobject uriObj = NULL;
	jclass fileClass = this->env->FindClass(this->JAVA_IO_FILE);
	if (fileClass != NULL) {
		jmethodID toUriId = this->env->GetMethodID(fileClass,
				this->JAVA_IO_FILE_TOURI_NAME, "()Ljava/net/URI;");

		if (toUriId != NULL) {
			jobject uriLocalObj = this->env->CallObjectMethod(fileObj, toUriId);

			if (this->env->ExceptionCheck()) {
				this->throwException();
			} else {
				uriObj = this->env->NewGlobalRef(uriLocalObj);
			}
		} else {
			this->throwException();
		}
	} else {
		this->throwException();
	}

	return uriObj;
}

/**
 * Creates a java.net.URL object using the parameter object's method, toURL() method. The parameter is expected to be
 * a java.net.URI object.
 * @param jobject obj Used to call toURL() method on the object.
 * @return jobject Returns a java.net.URL object or returns NULL when JNI encounters an exception or env,JNIEnv property is NULL.
 * The returned object must be released once the job is done when it's successfully created.
 * @throw Throws when JNI encounters an exception.
 */
jobject AbstractClassLoader::createURLFrom(jobject uriObj) {

	////TODO need to add checking if the input object is an expected one or not.

	if (uriObj == NULL) {
		return NULL;
	}

	if (this->isEnvNull()) {
		return NULL;
	}

	jobject urlObj = NULL;

	jclass uriClass = this->env->FindClass(this->JAVA_NET_URI);
	if (uriClass != NULL) {
		jmethodID toUrlId = this->env->GetMethodID(uriClass,
				this->JAVA_NET_URI_TOURL_NAME, "()Ljava/net/URL;");

		if (toUrlId != NULL) {
			jobject urlLocalObj = this->env->CallObjectMethod(uriObj, toUrlId);

			if (this->env->ExceptionCheck()) {
				this->throwException();
			} else {
				urlObj = this->env->NewGlobalRef(urlLocalObj);
			}
		} else {
			this->throwException();
		}
	} else {
		this->throwException();
	}

	return urlObj;
}

/**
 * Creates an array of java.net.URL adding the parameter as an element. This method expects a class search path is already read by
 * the method AbstractClassLoader::findJars().
 * @param jobject obj To be stored in the array.
 * @return jobject Returns an array of java.bet.URL or NULL.
 * The returned object must be released once the job is done when it's successfully created.
 * @throw Throws when JNI encounters an exception.
 */
jobject AbstractClassLoader::createURLsFrom(jobject urlObj) {

	////TODO need to add checking if the input object is an expected one or not.

	if (urlObj == NULL) {
		return NULL;
	}

	if (this->isEnvNull()) {
		return NULL;
	}

	jobject urls = NULL;
	jobjectArray localUrls = NULL;
	jclass urlClass = this->env->FindClass(this->JAVA_NET_URL);
	if (urlClass != NULL) {
		localUrls = this->env->NewObjectArray(1, urlClass, urlObj);

		if (this->env->ExceptionCheck()) {
			this->throwException();
		} else {
			urls = (jobject) this->env->NewGlobalRef(localUrls);
		}
	} else {
		this->throwException();
	}

	return urls;
}

/**
 * Creates an array of java.net.URL object. This method expects AbstractClassLoader::findJars() method before the call of this method.
 * Also this method adds the elements in the array as the class search paths.
 * @return jobject Returns an array of java.bet.URL or NULL.
 * The returned object must be released once the job is done when it's successfully created.
 * @throw Throws when JNI encounters an exception or when the size of classPaths property is 0.
 */
jobject AbstractClassLoader::createURLsFrom() {

	if (this->isEnvNull()) {
		this->throwException();
	}

	if (this->classPaths->size() == 0) {
		return NULL;
	}

	jobject urls = NULL;
	jclass urlClass = this->env->FindClass(this->JAVA_NET_URL);
	if (urlClass != NULL) {

		jobjectArray localUrls = this->env->NewObjectArray(
				this->classPaths->size(), urlClass, NULL);

		if (this->env->ExceptionCheck()) {
			this->throwException();
		} else {
			unsigned int i;
			for (i = 0; i < this->classPaths->size(); i++) {

				jobject fileObj = this->createFileFrom(
						this->classPaths->at(i)->c_str());
				jobject uriObj = this->createURIFrom(fileObj);
				jobject urlObj = this->createURLFrom(uriObj);

				this->env->SetObjectArrayElement(localUrls, i, urlObj);

				this->env->DeleteGlobalRef(fileObj);
				this->env->DeleteGlobalRef(uriObj);
				this->env->DeleteGlobalRef(urlObj);
			}

			if (this->env->ExceptionCheck()) {
				this->throwException();
			} else {
				urls = this->env->NewGlobalRef(localUrls);
			}
		}
	} else {
		this->throwException();
	}

	return urls;
}

/**
 * Loads a class specified by the parameter.
 * @param const char* className Target class to be loaded.
 * @return jclass Returns class representation of the specified class name or NULL.
 * The returned object must be released once the job is done when it's successfully created.
 * @throw Throws when JNI encounters an exception.
 */
jobject AbstractClassLoader::loadClass(const char *className) {

	if (this->isEnvNull()) {
		this->throwException();
	}

	jobject cls = NULL;
	jstring classNameString = this->env->NewStringUTF(className);

	if (classNameString != NULL) {

		if (this->classLoader != NULL && this->classLoaderClass != NULL) {

			jmethodID loadClassId = this->env->GetMethodID(
					(jclass) this->classLoaderClass,
					this->JAVA_LANG_CLASSLOADER_LOADCLASS_NAME,
					"(Ljava/lang/String;)Ljava/lang/Class;");

			if (loadClassId != NULL) {
				jobject localCls = this->env->CallObjectMethod(
						this->classLoader, loadClassId, classNameString);

				if (this->env->ExceptionCheck()) {
					this->env->DeleteLocalRef(classNameString);
					this->throwException();
				} else {
					cls = this->env->NewGlobalRef(localCls);
				}
			} else {
				this->env->DeleteLocalRef(classNameString);
				this->throwException();
			}
		} else {
			this->env->DeleteLocalRef(classNameString);
			return NULL;
		}

		this->env->DeleteLocalRef(classNameString);
	} else {
		this->throwException();
	}

	return cls;
}

/**
 * Finds class representation of the class specified by the parameter.
 * @param const char *className Class name to be looked up.
 * @return jobject Returns Class representation as jobject or NULL.
 * The returned object must be released once the job is done when it's successfully created.
 * @throw Throws when JNI encounters an exception.
 */
jobject AbstractClassLoader::findClass(const char *className) {

	if (this->isEnvNull()) {
		this->throwException();
	}

	if (this->classLoader == NULL || this->classLoaderClass == NULL) {
		return NULL;
	}

	jobject classObj = NULL;
	jstring classNameString = this->env->NewStringUTF(className);
	if (classNameString != NULL) {

		jmethodID findClassId = this->env->GetMethodID(
				(jclass) this->classLoaderClass,
				this->JAVA_LANG_CLASSLOADER_FINDCLASS_NAME,
				"(Ljava/lang/String;)Ljava/lang/Class;");

		if (findClassId != NULL) {

			jobject localClassObj = this->env->CallObjectMethod(
					this->classLoader, findClassId, classNameString);

			if (this->env->ExceptionCheck()) {

				this->env->DeleteLocalRef(classNameString);
				this->throwException();
			} else {
				classObj = this->env->NewGlobalRef(localClassObj);
			}
		} else {
			this->env->DeleteLocalRef(classNameString);
			this->throwException();
		}
	} else {
		this->throwException();
	}
	return classObj;
}

void AbstractClassLoader::throwException() {

	this->env->ExceptionDescribe();
	this->env->ExceptionClear();

	//TODO need to think about how to get exception messages and causes from the jthrowable object.
	throw CppHibernateClassLoaderException("error occurred");
}

/**
 * Searches std::string jar files in the directory specified by the parameter.
 * @return int Returns number of jar files found in the directory.
 * @throw CppHibernateIOException Throws when can't read the directory's entries.
 */
int AbstractClassLoader::findJars(std::string & jarSearchPath) {

	std::auto_ptr<DIR> directory(opendir(jarSearchPath.c_str()));
	struct dirent *directoryEntries;
	if (directory.get() == NULL) {
		throw CppHibernateIOException(
				"could not open base script location correctly.");
	}

	while (directoryEntries = readdir(directory.get())) {
		if (directoryEntries == NULL) {
			throw CppHibernateIOException(
					"error happened when reading an entry in the directory");
		}
		std::string entry(static_cast<const char *>(directoryEntries->d_name));

		if (this->isJarFile(entry)) {
			//TODO add synchronization lock here

			if (this->isEndedWithSeparator(entry)) {
				std::string *jarAbsolutePath = new std::string(
						jarSearchPath + entry);

				this->classPaths->push_back(jarAbsolutePath);
			} else {
				std::string *jarAbsolutePath = new std::string(
						jarSearchPath + this->UNIX_SEPARATOR + entry);

				this->classPaths->push_back(jarAbsolutePath);
			}
		}
	}

	return this->classPaths->size();
}

/**
 * Checks if the file has the jar or JAR extension as jar file.
 * @param std::string& fileName File name to be examined if it's a jar file or not.
 * @return bool Returns true if the file is a jar file, false otherwise.
 */
bool AbstractClassLoader::isJarFile(std::string& fileName) {

	size_t pos = fileName.find_last_of(this->PERIOD);

	if (pos != std::string::npos) {
		std::string cpFileName(fileName);
		std::string extension = cpFileName.substr(pos + 1);

		if (extension.compare(this->LOWER_CASE_JAR) == 0
				|| extension.compare(this->UPPER_CASE_JAR) == 0) {
			return true;
		}
	}

	return false;
}

/**
 * Checks if the specified path ends with a separator or not.
 * @param std::string& jarFilePath Path for a jar file.
 * @return bool Returns true when the specified path ends with OS dependent separator, false otherwise.
 */
bool AbstractClassLoader::isEndedWithSeparator(std::string& jarFilePath) {

	if ((jarFilePath.length() - 1)
			== (jarFilePath.find_last_of(this->UNIX_SEPARATOR))) {
		return true;
	}

	return false;
}

/**
 * Returns the size of found jar files.
 * @return Returns size of found jar files.
 */
int AbstractClassLoader::size() {
	return this->classPaths->size();
}

/**
 * Returns a specified jar file path by the index.
 * @param int& index The index to be retrieved.
 * @return const std::string Returns the specified absolute jar file path.
 * @throw CppHibernateIndexError Throws if the specified index is invalid.
 */
const std::string AbstractClassLoader::get(int index) {

	if (index < 0 || index > (this->classPaths->size() - 1)) {
		std::string errorMessage("specified invalid index, ");
		std::stringstream indexStr;

		indexStr << index;
		errorMessage += indexStr.str();

		std::stringstream sizeStr;
		sizeStr << this->classPaths->size();

		errorMessage += " size, " + sizeStr.str() + ".";

		throw CppHibernateIndexException(errorMessage.c_str());
	}

	return static_cast<const std::string>(*(this->classPaths->at(index)));
}

/**
 * Gets classLoader.
 * @return jobject Returns the classLoader property.
 */
jobject AbstractClassLoader::getClassLoader() {

	return this->classLoader;
}

/**
 * Sets classLoader.
 */
void AbstractClassLoader::setClassLoader(jobject classLoader) {

	this->classLoader = classLoader;
}

/**
 * Sets classLoaderClass.
 * @param jobject classLoaderClass The class representation of classLoader property.
 */
void AbstractClassLoader::setClassLoaderClass(jobject classLoaderClass) {

	this->classLoaderClass = classLoaderClass;
}

/**
 * Gets classLoaderClass.
 */
jobject AbstractClassLoader::getClassLoaderClass() {

	return this->classLoaderClass;
}

/**
 * Deletes all the stored jar absolute paths. Called by AbstractClassLoader::~AbstractClassLoader().
 */
void AbstractClassLoader::deleteClassPaths() {
	unsigned int i;
	for (i = 0; i < this->classPaths->size(); i++) {
		delete this->classPaths->at(i);
	}

	delete this->classPaths;
}

/**
 * Deletes two global ref properties, classLoader and classLoaderClass. Call this method when class loader is
 * not required any more.
 */
void AbstractClassLoader::deleteClassLoader() {

	if (this->classLoader != NULL) {
		this->env->DeleteGlobalRef(this->classLoader);
		this->classLoader = NULL;
	}

	if (this->classLoaderClass != NULL) {
		this->env->DeleteGlobalRef(this->classLoaderClass);
		this->classLoaderClass = NULL;
	}
}

AbstractClassLoader::~AbstractClassLoader() {

	if (this->classPaths != NULL) {
		this->deleteClassPaths();
	}

	this->deleteClassLoader();
}

} /* namespace cppHibernate */
