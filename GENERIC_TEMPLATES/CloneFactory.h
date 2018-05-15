#pragma once
#include <map>
#include <cstdlib>
#include <fstream>
#include "SpecialTypes.h"
#include "FactoryErrorPolicy.h"
#include "TypeInfo.h"

template <
	class AbstractProduct,
	class ProductCreator = AbstractProduct* (AbstractProduct::*)(),
	class FactoryErrorPolicy = IgnoreError<AbstractProduct>
>
class CloneFactory :public FactoryErrorPolicy {
	typedef std::map<TypeInfo, ProductCreator> _callbacksMap;
	_callbacksMap _callbacks;
public:
	bool Register(const TypeInfo& type, ProductCreator creator);
	bool Unregister(const TypeInfo& type);
	AbstractProduct* CreateObject(AbstractProduct* model);
};

template <class AbstractProduct, class ProductCreator, class FactoryErrorPolicy>
bool CloneFactory<AbstractProduct, ProductCreator, FactoryErrorPolicy>::Register(const TypeInfo& type, ProductCreator creator) {
	return _callbacks.insert(_callbacksMap::value_type(type,creator)).second;
}

template <class AbstractProduct, class ProductCreator, class FactoryErrorPolicy>
bool CloneFactory<AbstractProduct, ProductCreator, FactoryErrorPolicy>::Unregister(const TypeInfo& type) {
	return _callbacks.erase(type) == 1;
}

template <class AbstractProduct, class ProductCreator, class FactoryErrorPolicy>
AbstractProduct* CloneFactory<AbstractProduct, ProductCreator, FactoryErrorPolicy>::CreateObject(AbstractProduct* model) {
	TypeInfo type(*model);

	_callbacksMap::const_iterator i = _callbacks.find(type);
	if (i == _callbacks.end()) {
		return NoCallback();
	}
	else return ((*model).*(i->second))();
}