#pragma once
#include <typeinfo>
#include "SpecialTypes.h"

struct TypeInfo {
	const std::type_info& _type;

	TypeInfo(const TypeInfo& obj) : _type(obj._type) {}

	template<class T>
	TypeInfo(const T& obj): _type(typeid(obj)) {}
	
	bool operator==(const TypeInfo& obj) const {
		return _type == obj._type;
	}
	bool operator!=(const TypeInfo& obj) const {
		return _type != obj._type;
	}
	bool operator>(const TypeInfo& obj) const {
		return !(_type.before(obj._type));
	}
	bool operator<(const TypeInfo& obj) const {
		return _type.before(obj._type);
	}
};