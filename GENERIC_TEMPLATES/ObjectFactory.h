#pragma once
#include <map>
#include <cstdlib>
#include "SpecialTypes.h"
#include "FactoryErrorPolicy.h"

template <
	class AbstractProduct,
	class IdentifierType,
	class ProductCreator = AbstractProduct* (*)(),
	class FactoryErrorPolicy = IgnoreError<AbstractProduct>
> 
class ObjectFactory:public FactoryErrorPolicy {
	typedef std::map<IdentifierType, ProductCreator> _callbacksMap;
	_callbacksMap _callbacks;
public:
	bool Register(const IdentifierType& id, ProductCreator creator);
	bool Unregister(const IdentifierType& id);
	AbstractProduct* CreateObject(const IdentifierType& id);
};

template < class AbstractProduct,class IdentifierType,class ProductCreator, class FactoryErrorPolicy>
bool ObjectFactory<AbstractProduct, IdentifierType, ProductCreator, FactoryErrorPolicy>::Register(const IdentifierType& id, ProductCreator creator) {
	return _callbacks.insert(_callbacksMap::value_type(id, creator)).second;
}

template < class AbstractProduct, class IdentifierType, class ProductCreator, class FactoryErrorPolicy>
bool ObjectFactory<AbstractProduct, IdentifierType, ProductCreator, FactoryErrorPolicy>::Unregister(const IdentifierType& id) {
	return _callbacks.erase(id) == 1;
}

template < class AbstractProduct, class IdentifierType, class ProductCreator, class FactoryErrorPolicy>
AbstractProduct* ObjectFactory<AbstractProduct, IdentifierType, ProductCreator, FactoryErrorPolicy>::CreateObject(const IdentifierType& id) {
	_callbacksMap::const_iterator i = _callbacks.find(id);
	if (i == _callbacks.end()) {
		return NoCallback();
	}
	else return (i->second)();
}
