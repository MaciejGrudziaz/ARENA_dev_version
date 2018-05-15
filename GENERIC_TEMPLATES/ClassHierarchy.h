#pragma once
#include "TypeList.h"

namespace CH{
	template
	<
		class TList,
		template <class AtomicType, class Base> class Unit,
		class Root = EmptyType
	>
		class GenLinHierarchy;

	template
	<
		class T1,class T2,template<class ,class> class Unit,class Root
	>
		class GenLinHierarchy<TL::TypeList<T1,T2>,Unit,Root>
		: public Unit<T1,GenLinHierarchy<T2,Unit,Root>>
	{};

	template
		<
		class T, template<class, class> class Unit, class Root
		>
		class GenLinHierarchy<TYPELIST_1(T), Unit, Root>
		: public Unit<T, Root>
	{};

	template<class TList,template<class> class Unit>
	class GenScatterHierarchy;

	template <class T1,class T2,template<class> class Unit>
	class GenScatterHierarchy<TL::TypeList<T1,T2>,Unit>
		: public GenScatterHierarchy<T1,Unit>
		, public GenScatterHierarchy<T2,Unit>
	{};

	template <class AtomicType, template <class> class Unit>
	class GenScatterHierarchy
		: public Unit<AtomicType>
	{};

	template <template <class> class Unit>
	class GenScatterHierarchy<NullType,Unit>
	{};
}