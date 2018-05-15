#pragma once
#include "SpecialTypes.h"

#define TYPELIST_1(T1) TL::TypeList<T1,NullType>
#define TYPELIST_2(T1,T2) TL::TypeList< T1,TYPELIST_1(T2) >
#define TYPELIST_3(T1,T2,T3) TL::TypeList< T1,TYPELIST_2(T2,T3) >
#define TYPELIST_4(T1,T2,T3,T4) TL::TypeList< T1,TYPELIST_3(T2,T3,T4) >
#define TYPELIST_5(T1,T2,T3,T4,T5) TL::TypeList< T1,TYPELIST_4(T2,T3,T4,T5) >
#define TYPELIST_6(T1,T2,T3,T4,T5,T6) TL::TypeList< T1,TYPELIST_5(T2,T3,T4,T5,T6) >
#define TYPELIST_7(T1,T2,T3,T4,T5,T6,T7) TL::TypeList< T1,TYPELIST_6(T2,T3,T4,T5,T6,T7) >
#define TYPELIST_8(T1,T2,T3,T4,T5,T6,T7,T8) TL::TypeList< T1,TYPELIST_7(T2,T3,T4,T5,T6,T7,T8) >
#define TYPELIST_9(T1,T2,T3,T4,T5,T6,T7,T8,T9) TL::TypeList< T1,TYPELIST_8(T2,T3,T4,T5,T6,T7,T8,T9) >
#define TYPELIST_10(T1,T2,T3,T4,T5,T6,T7,T8,T9,T10) TL::TypeList< T1,TYPELIST_9(T2,T3,T4,T5,T6,T7,T8,T9,T10) >

namespace TL {
	template <int i> struct Int2Type{
		enum {_type=i};
	};

	template <class T,int i> struct Type2Int{
		enum { val=i};
		typedef T OriginalType;
	};
	
	template <class T>
	struct Type2Type {
		typedef T OriginalType;
	};

	template<class T,class U>
	struct TypeList {
		typedef T Head;
		typedef U Tail;
	};

	template <class TList> struct SizeOf;
	template <>
	struct SizeOf<NullType>
	{
		enum { value = 0 };
	};

	template<class T, class U>
	struct SizeOf<TypeList<T, U>>
	{
		enum { value = 1 + SizeOf<U>::value };
	};

	template<class TList, class T> struct IndexOf;
	template<class T>
	struct IndexOf<NullType, T> {
		enum { value = -1 };
	};
	
	template <class T, class Tail> 
	struct IndexOf<TypeList<T,Tail>, T>
	{
		enum { value = 0 };
	};

	template<class Head, class Tail, class T>
	struct IndexOf<TypeList<Head, Tail>, T> 
	{
	private:
		enum{temp=IndexOf<Tail,T>::value };
	public:
		enum{value= temp==-1 ? -1 : 1 + temp};
	};

	template<class TList, int idx> struct TypeAt;
	template<int idx>
	struct TypeAt<NullType, idx>
	{
		typedef NullType Result;
	};

	template<class TList>
	struct TypeAt<TList, -1>
	{
		typedef NullType Result;
	};

	template<class Head,class Tail>
	struct TypeAt<TypeList<Head,Tail>, 0>
	{
		typedef Head Result;
	};

	template<class Head,class Tail,int idx>
	struct TypeAt<TypeList<Head,Tail>,idx>
	{
		typedef typename TypeAt<Tail, idx - 1>::Result Result;
	};

	template <class TList, class T> struct EraseAll;
	template <class T>
	struct EraseAll<NullType, T> 
	{
		typedef NullType Result;
	};

	template <class Tail, class T>
	struct EraseAll<TypeList<T, Tail>, T> 
	{
		typedef typename EraseAll<Tail,T>::Result Result;
	};

	template <class Head, class Tail, class T>
	struct EraseAll<TypeList<Head, Tail>, T>
	{
		typedef TypeList<Head, typename EraseAll<Tail, T>::Result> Result;
	};

	
	template <class TList, class T> struct Erase;
	template <class T>
	struct Erase<NullType, T>
	{
		typedef NullType Result;
	};

	template <class Tail, class T>
	struct Erase<TypeList<T, Tail>, T>
	{
		typedef Tail Result;
	};

	template <class Head, class Tail, class T>
	struct Erase<TypeList<Head, Tail>, T>
	{
		typedef TypeList<Head, typename Erase<Tail, T>::Result> Result;
	};

	template <class TList> struct NoDuplicate;
	template <>
	struct NoDuplicate<NullType>
	{
		typedef NullType Result;
	};

	template <class Head,class Tail>
	struct NoDuplicate<TypeList<Head, Tail>>
	{
	private:
		typedef typename NoDuplicate<Tail>::Result L1;
		typedef typename Erase<L1, Head>::Result L2;

	public:

		typedef TypeList<Head,L2> Result;
	};

	template<class TList> struct Reverse;
	template<> 
	struct Reverse<NullType>
	{
		typedef NullType Result;
	};

	template <class Head>
	struct Reverse <TypeList<Head, NullType> >
	{
		typedef Head Result;
	};

	template <class Head, class Tail>
	struct Reverse<TypeList<Head, Tail> >
	{
		typedef TypeList<typename Reverse<typename Tail::Tail>::Result, TypeList<typename Tail::Head, TypeList<Head,NullType> > > Result;
	};

	template <class Head1, class Tail1, class Tail2>
	struct Reverse<TypeList<TypeList<Head1,Tail1>, Tail2> >
	{
		typedef TypeList<typename Reverse<typename Tail2::Tail>::Result,TypeList<typename Tail2::Head,TypeList<Head1,Tail1> > > Result;
	};

	template <class L1, class L2> struct Append;
	template <>
	struct Append<NullType, NullType>
	{
		typedef NullType Result;
	};

	template <class Head, class Tail>
	struct Append<TypeList<Head,Tail>, NullType>
	{
		typedef TypeList<Head,Tail> Result;
	};

	template<class Head, class Tail>
	struct Append<NullType, TypeList<Head,Tail>>
	{
		typedef TypeList<Head,Tail> Result;
	};

	template <class Head1, class Tail1, class Head2, class Tail2>
	struct Append<TypeList<Head1, Tail1>, TypeList<Head2,Tail2>>
	{
	private:
		typedef TypeList<Head2, Tail2> L2;
		typedef typename Append<Tail1, L2>::Result L1;

	public:
		typedef TypeList<Head1, L1> Result;
	};

	typedef TYPELIST_1(bool) _bool;
	typedef TYPELIST_1(signed char) _signChar;
	typedef TYPELIST_2(char, wchar_t) _standardChars;
	typedef TYPELIST_1(unsigned char) _unsignedChar;
	typedef TYPELIST_7(short, short int, int, long, long int, long long, long long int) _standardInts;
	typedef TYPELIST_8(signed short, signed short int, signed, signed int, signed long, signed long int, signed long long, signed long long int) _signInts;
	typedef TYPELIST_8(unsigned short, unsigned short int, unsigned, unsigned int, unsigned long, unsigned long int, unsigned long long, unsigned long long int) _unsignedInts;
	typedef TYPELIST_3(float, double, long double) _floating;

	typedef typename Append <_signChar, typename Append<_standardChars, _unsignedChar>::Result>::Result _chars;
	typedef typename Append < _standardInts, typename Append<_signInts, _unsignedInts>::Result>::Result _ints;
	typedef typename Append <_bool, typename Append<_chars, typename Append<_ints, _floating>::Result >::Result >::Result _all;

	template <class T> struct IsStandard {
		enum { Result = IndexOf<_all, T>::value != -1 ? 1 : 0 };
	};

	template<class TList, int idx, class Base> struct TypeAtNonStrict;
	template<class Head, class Tail, class Base>
	struct TypeAtNonStrict<TypeList<Head, Tail>, 0, Base>
	{
		typedef Head Result;
	};

	template <int idx, class Base>
	struct TypeAtNonStrict<NullType, idx, Base>
	{
		typedef Base Result;
	};	

	template<class Head, class Tail, int idx, class Base> 
	struct TypeAtNonStrict<TypeList<Head,Tail>,idx,Base>
	{
	private:
		enum{temp = idx < 0 ? SizeOf<TypeList<Head,Tail> >::value : idx-1 };

	public:
		typedef typename TypeAtNonStrict<Tail, temp, Base>::Result Result;
	};
}