#pragma once
#include <assert.h>
#include "SingletonPolicy.h"

#define SINGLETON(_class) _class(){}\
_class(const _class&){}\
_class& operator=(const _class&){}\
_class(const _class&&){}\
_class& operator=(const _class&&){}

template <
	class T,
	template <class> class CreationPolicy = CreateUsingNew,
	template <class> class LifetimePolicy = DefaultLifetime
>
class SingletonHolder: public CreationPolicy<T>, LifetimePolicy<T>{
	static T* _instance;

	static void DestroySingleton() {
		assert(_instance!=nullptr);
		Destroy(_instance);
	}

	SingletonHolder() {}
	SingletonHolder(const SingletonHolder&) {}
	SingletonHolder& operator=(const SingletonHolder&) {}
	SingletonHolder(const SingletonHolder&&) {}
	SingletonHolder& operator=(const SingletonHolder&&) {}

public:
	static T& Instance();

};

template <class T,template <class> class CreationPolicy,template <class> class LifetimePolicy>
T* SingletonHolder<T,CreationPolicy,LifetimePolicy>::_instance = nullptr;

template<class T,template <class T> class CreationPolicy, template <class T> class LifetimePolicy>
T& SingletonHolder<T, CreationPolicy, LifetimePolicy>::Instance() {
	if (!_instance) {
		_instance = Create();
		ScheduleDestruction(DestroySingleton);
	}

	return *_instance;
}