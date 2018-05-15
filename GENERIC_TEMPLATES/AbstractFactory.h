#pragma once
#include "TypeList.h"
#include "ClassHierarchy.h"
#include "SpecialTypes.h"

template <class T>
class AFUnit {
public:
	virtual T* DoCreate(TL::Type2Type<T>) = 0;
	virtual ~AFUnit() {}
};

template
<
	class TList,
	template <class> class Unit=AFUnit
>
class AbstractFactory :public CH::GenScatterHierarchy<TList, Unit> {
public:
	typedef TList ProductList;

	template <class T> 
	T* Create() {
		Unit<T>& unit = *this;
		return unit.DoCreate(TL::Type2Type<T>());
	}
};

template <class ConcreteProduct,class Base>
class OpNewFactoryUnit :public Base {
	typedef typename Base::ProductList BaseProductList;
protected:
	typedef typename BaseProductList::Tail ProductList;
public:
	typedef typename BaseProductList::Head AbstractProduct;

	ConcreteProduct* DoCreate(TL::Type2Type <AbstractProduct>) {
		return new ConcreteProduct;
	}
};

template
<
	class AbstractFact,
	class TList,
	template <class,class> class Creator=OpNewFactoryUnit
>
class ConcreteFactory
	:public CH::GenLinHierarchy<typename TL::Reverse<TList>::Result, Creator, AbstractFact> {
public:
	typedef typename AbstractFact::ProductList ProductList;
	typedef TList ConcreteProductList;
};