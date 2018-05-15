#pragma once
#include "FunctorImpl.h"

template<class ParentFunctor, typename Fun, class Base = NullType>
class FunctorHandler : public FunctorImpl <typename ParentFunctor::ResultType, typename ParentFunctor::ParmList> {
private:
	Base& _obj;
	Fun _fun;
public:
	typedef typename ParentFunctor::ResultType ResultType;

	FunctorHandler(const Fun& fun, Base& obj) : _fun(fun), _obj(obj) {}
	FunctorHandler* Clone() const {
		return new FunctorHandler(*this);
	}

	ResultType operator()() {
		return ((_obj).*(_fun))();
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1) {
		return((_obj).*(_fun))(p1);
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1, typename ParentFunctor::Parm2 p2) {
		return ((_obj).*(_fun))(p1, p2);
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1, typename ParentFunctor::Parm2 p2, typename ParentFunctor::Parm3 p3) {
		return ((_obj).*(_fun))(p1, p2, p3);
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1, typename ParentFunctor::Parm2 p2, typename ParentFunctor::Parm3 p3, typename ParentFunctor::Parm4 p4) {
		return ((_obj).*(_fun))(p1, p2, p3, p4);
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1, typename ParentFunctor::Parm2 p2, typename ParentFunctor::Parm3 p3, typename ParentFunctor::Parm4 p4, typename ParentFunctor::Parm5 p5) {
		return ((_obj).*(_fun))(p1, p2, p3, p4, p5);
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1, typename ParentFunctor::Parm2 p2, typename ParentFunctor::Parm3 p3, typename ParentFunctor::Parm4 p4, typename ParentFunctor::Parm5 p5,
		typename ParentFunctor::Parm6 p6) {
		return ((_obj).*(_fun))(p1, p2, p3, p4, p5, p6);
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1, typename ParentFunctor::Parm2 p2, typename ParentFunctor::Parm3 p3, typename ParentFunctor::Parm4 p4, typename ParentFunctor::Parm5 p5,
		typename ParentFunctor::Parm6 p6, typename ParentFunctor::Parm7 p7) {
		return ((_obj).*(_fun))(p1, p2, p3, p4, p5, p6, p7);
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1, typename ParentFunctor::Parm2 p2, typename ParentFunctor::Parm3 p3, typename ParentFunctor::Parm4 p4, typename ParentFunctor::Parm5 p5,
		typename ParentFunctor::Parm6 p6, typename ParentFunctor::Parm7 p7, typename ParentFunctor::Parm8 p8) {
		return ((_obj).*(_fun))(p1, p2, p3, p4, p5, p6, p7, p8);
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1, typename ParentFunctor::Parm2 p2, typename ParentFunctor::Parm3 p3, typename ParentFunctor::Parm4 p4, typename ParentFunctor::Parm5 p5,
		typename ParentFunctor::Parm6 p6, typename ParentFunctor::Parm7 p7, typename ParentFunctor::Parm8 p8, typename ParentFunctor::Parm9 p9) {
		return ((_obj).*(_fun))(p1, p2, p3, p4, p5, p6, p7, p8, p9);
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1, typename ParentFunctor::Parm2 p2, typename ParentFunctor::Parm3 p3, typename ParentFunctor::Parm4 p4, typename ParentFunctor::Parm5 p5,
		typename ParentFunctor::Parm6 p6, typename ParentFunctor::Parm7 p7, typename ParentFunctor::Parm8 p8, typename ParentFunctor::Parm9 p9, typename ParentFunctor::Parm10 p10) {
		return ((_obj).*(_fun))(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
	}
};

template<class ParentFunctor, typename Fun>
class FunctorHandler<ParentFunctor, Fun, NullType> : public FunctorImpl <typename ParentFunctor::ResultType, typename ParentFunctor::ParmList> {
private:
	Fun _fun;
public:
	typedef typename ParentFunctor::ResultType ResultType;

	FunctorHandler(const Fun& fun) : _fun(fun) {}
	FunctorHandler* Clone() const {
		return new FunctorHandler(*this);
	}

	ResultType operator()() {
		return _fun();
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1) {
		return _fun(p1);
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1, typename ParentFunctor::Parm2 p2) {
		return _fun(p1, p2);
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1, typename ParentFunctor::Parm2 p2, typename ParentFunctor::Parm3 p3) {
		return _fun(p1, p2, p3);
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1, typename ParentFunctor::Parm2 p2, typename ParentFunctor::Parm3 p3, typename ParentFunctor::Parm4 p4) {
		return _fun(p1, p2, p3, p4);
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1, typename ParentFunctor::Parm2 p2, typename ParentFunctor::Parm3 p3, typename ParentFunctor::Parm4 p4, typename ParentFunctor::Parm5 p5) {
		return _fun(p1, p2, p3, p4, p5);
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1, typename ParentFunctor::Parm2 p2, typename ParentFunctor::Parm3 p3, typename ParentFunctor::Parm4 p4, typename ParentFunctor::Parm5 p5,
		typename ParentFunctor::Parm6 p6) {
		return _fun(p1, p2, p3, p4, p5, p6);
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1, typename ParentFunctor::Parm2 p2, typename ParentFunctor::Parm3 p3, typename ParentFunctor::Parm4 p4, typename ParentFunctor::Parm5 p5,
		typename ParentFunctor::Parm6 p6, typename ParentFunctor::Parm7 p7) {
		return _fun(p1, p2, p3, p4, p5, p6, p7);
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1, typename ParentFunctor::Parm2 p2, typename ParentFunctor::Parm3 p3, typename ParentFunctor::Parm4 p4, typename ParentFunctor::Parm5 p5,
		typename ParentFunctor::Parm6 p6, typename ParentFunctor::Parm7 p7, typename ParentFunctor::Parm8 p8) {
		return _fun(p1, p2, p3, p4, p5, p6, p7, p8);
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1, typename ParentFunctor::Parm2 p2, typename ParentFunctor::Parm3 p3, typename ParentFunctor::Parm4 p4, typename ParentFunctor::Parm5 p5,
		typename ParentFunctor::Parm6 p6, typename ParentFunctor::Parm7 p7, typename ParentFunctor::Parm8 p8, typename ParentFunctor::Parm9 p9) {
		return _fun(p1, p2, p3, p4, p5, p6, p7, p8, p9);
	}
	ResultType operator()(typename ParentFunctor::Parm1 p1, typename ParentFunctor::Parm2 p2, typename ParentFunctor::Parm3 p3, typename ParentFunctor::Parm4 p4, typename ParentFunctor::Parm5 p5,
		typename ParentFunctor::Parm6 p6, typename ParentFunctor::Parm7 p7, typename ParentFunctor::Parm8 p8, typename ParentFunctor::Parm9 p9, typename ParentFunctor::Parm10 p10) {
		return _fun(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
	}
};