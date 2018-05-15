#pragma once

template <class T>
class CreateUsingNew {
	protected:
	static T* Create() {
		T* _obj = new T;
		return _obj;
	}

	static void Destroy(T* _obj) {
		delete _obj;
	}
};

template <class T>
class CreateStatic {
	protected:
	static T* Create() {
		static T _obj;
		return _obj;
	}

	static void Destroy(T* _obj) {}
};

template <class T>
class CreateMalloc {
	protected:
	static T* Create() {
		T* _obj = malloc(sizeof(T));
		return _obj;
	}

	static void Destroy(T* _obj) {
		free(_obj);
	}
};

template <class T>
class DefaultLifetime {
	protected:
	static void ScheduleDestruction(void (*_fun)()) {
		std::atexit(_fun);
	}
};

template <class T>
class NoDestory {
	protected:
	static void ScheduleDestruction(void(*_fun)()) { }
};
