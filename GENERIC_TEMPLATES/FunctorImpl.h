#pragma once
#include "TypeList.h"

template <class ResultType, class TList> class FunctorImpl;

template<class ResultType>
class FunctorImpl<ResultType, NullType> {
public:
	virtual ResultType operator()() = 0;
	virtual FunctorImpl* Clone() const = 0;
	virtual ~FunctorImpl() {}
};

template<class ResultType, class P1>
class FunctorImpl<ResultType, TYPELIST_1(P1)> {
public:
	virtual ResultType operator()(P1) = 0;
	virtual FunctorImpl* Clone() const = 0;
	virtual ~FunctorImpl() {}
};

template<class ResultType, class P1, class P2>
class FunctorImpl<ResultType, TYPELIST_2(P1, P2)> {
public:
	virtual ResultType operator()(P1, P2) = 0;
	virtual FunctorImpl* Clone() const = 0;
	virtual ~FunctorImpl() {}
};

template<class ResultType, class P1, class P2, class P3>
class FunctorImpl<ResultType, TYPELIST_3(P1, P2, P3)> {
public:
	virtual ResultType operator()(P1, P2, P3) = 0;
	virtual FunctorImpl* Clone() const = 0;
	virtual ~FunctorImpl() {}
};

template<class ResultType, class P1, class P2, class P3, class P4>
class FunctorImpl<ResultType, TYPELIST_4(P1, P2, P3, P4)> {
public:
	virtual ResultType operator()(P1, P2, P3, P4) = 0;
	virtual FunctorImpl* Clone() const = 0;
	virtual ~FunctorImpl() {}
};

template<class ResultType, class P1, class P2, class P3, class P4, class P5>
class FunctorImpl<ResultType, TYPELIST_5(P1, P2, P3, P4, P5)> {
public:
	virtual ResultType operator()(P1, P2, P3, P4, P5) = 0;
	virtual FunctorImpl* Clone() const = 0;
	virtual ~FunctorImpl() {}
};

template<class ResultType, class P1, class P2, class P3, class P4, class P5, class P6>
class FunctorImpl<ResultType, TYPELIST_6(P1, P2, P3, P4, P5, P6)> {
public:
	virtual ResultType operator()(P1, P2, P3, P4, P5, P6) = 0;
	virtual FunctorImpl* Clone() const = 0;
	virtual ~FunctorImpl() {}
};

template<class ResultType, class P1, class P2, class P3, class P4, class P5, class P6, class P7>
class FunctorImpl<ResultType, TYPELIST_7(P1, P2, P3, P4, P5, P6, P7)> {
public:
	virtual ResultType operator()(P1, P2, P3, P4, P5, P6, P7) = 0;
	virtual FunctorImpl* Clone() const = 0;
	virtual ~FunctorImpl() {}
};

template<class ResultType, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8>
class FunctorImpl<ResultType, TYPELIST_8(P1, P2, P3, P4, P5, P6, P7, P8)> {
public:
	virtual ResultType operator()(P1, P2, P3, P4, P5, P6, P7, P8) = 0;
	virtual FunctorImpl* Clone() const = 0;
	virtual ~FunctorImpl() {}
};

template<class ResultType, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9>
class FunctorImpl<ResultType, TYPELIST_9(P1, P2, P3, P4, P5, P6, P7, P8, P9)> {
public:
	virtual ResultType operator()(P1, P2, P3, P4, P5, P6, P7, P8, P9) = 0;
	virtual FunctorImpl* Clone() const = 0;
	virtual ~FunctorImpl() {}
};

template<class ResultType, class P1, class P2, class P3, class P4, class P5, class P6, class P7, class P8, class P9, class P10>
class FunctorImpl<ResultType, TYPELIST_10(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10)> {
public:
	virtual ResultType operator()(P1, P2, P3, P4, P5, P6, P7, P8, P9, P10) = 0;
	virtual FunctorImpl* Clone() const = 0;
	virtual ~FunctorImpl() {}
};