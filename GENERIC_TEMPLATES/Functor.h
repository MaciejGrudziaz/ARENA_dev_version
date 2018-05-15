#pragma once
#include "FunctorHandler.h"
#include <memory>

template <class R,class TList>
class Functor {
private:
	typedef FunctorImpl<R, TList> Impl;
	std::auto_ptr<Impl> _spImpl;
public:
	Functor() { }
	Functor(const Functor& obj) { _spImpl = std::auto_ptr<Impl>(obj._spImpl->Clone()); }
	Functor(const Functor&& obj) { _spImpl = std::auto_ptr<Impl>(obj._spImpl->Clone()); }
	Functor& operator=(const Functor& obj) {
		_spImpl = std::auto_ptr<Impl>(obj._spImpl->Clone());
		return *this;
	}
	Functor& operator=(const Functor&& obj) {
		_spImpl = std::auto_ptr<Impl>(obj._spImpl->Clone());
		return *this;
	}

	typedef TList ParmList;
	typedef R ResultType;
	typedef typename TL::TypeAtNonStrict<TList, 0, NullType>::Result Parm1;
	typedef typename TL::TypeAtNonStrict<TList, 1, NullType>::Result Parm2;
	typedef typename TL::TypeAtNonStrict<TList, 2, NullType>::Result Parm3;
	typedef typename TL::TypeAtNonStrict<TList, 3, NullType>::Result Parm4;
	typedef typename TL::TypeAtNonStrict<TList, 4, NullType>::Result Parm5;
	typedef typename TL::TypeAtNonStrict<TList, 5, NullType>::Result Parm6;
	typedef typename TL::TypeAtNonStrict<TList, 6, NullType>::Result Parm7;
	typedef typename TL::TypeAtNonStrict<TList, 7, NullType>::Result Parm8;
	typedef typename TL::TypeAtNonStrict<TList, 8, NullType>::Result Parm9;
	typedef typename TL::TypeAtNonStrict<TList, 9, NullType>::Result Parm10;

	template <class Fun>
	Functor(const Fun& fun) :_spImpl(new FunctorHandler<Functor, Fun>(fun)) {}

	template <class Fun, class Base>
	Functor(const Fun& fun, Base& obj) : _spImpl(new FunctorHandler<Functor, Fun, Base>(fun, obj)) {}

	ResultType operator()() {
		return (*_spImpl)();
	}
	ResultType operator()(Parm1 p1) {
		return (*_spImpl)(p1);
	}
	ResultType operator()(Parm1 p1,Parm2 p2) {
		return (*_spImpl)(p1,p2);
	}
	ResultType operator()(Parm1 p1, Parm2 p2, Parm3 p3) {
		return (*_spImpl)(p1, p2, p3);
	}
	ResultType operator()(Parm1 p1, Parm2 p2, Parm3 p3,Parm4 p4) {
		return (*_spImpl)(p1, p2, p3, p4);
	}
	ResultType operator()(Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4, Parm5 p5) {
		return (*_spImpl)(p1, p2, p3, p4 ,p5);
	}
	ResultType operator()(Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4, Parm5 p5, Parm6 p6) {
		return (*_spImpl)(p1, p2, p3, p4, p5, p6);
	}
	ResultType operator()(Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4, Parm5 p5, Parm6 p6, Parm7 p7) {
		return (*_spImpl)(p1, p2, p3, p4, p5, p6, p7);
	}
	ResultType operator()(Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4, Parm5 p5, Parm6 p6, Parm7 p7, Parm8 p8) {
		return (*_spImpl)(p1, p2, p3, p4, p5, p6, p7, p8);
	}
	ResultType operator()(Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4, Parm5 p5, Parm6 p6, Parm7 p7, Parm8 p8, Parm9 p9) {
		return (*_spImpl)(p1, p2, p3, p4, p5, p6, p7, p8, p9);
	}
	ResultType operator()(Parm1 p1, Parm2 p2, Parm3 p3, Parm4 p4, Parm5 p5, Parm6 p6, Parm7 p7, Parm8 p8, Parm9 p9, Parm10 p10) {
		return (*_spImpl)(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
	}
};

template<class InFunctor>
class Binder : public FunctorImpl<typename InFunctor::ResultType, typename InFunctor::ParmList::Tail> {
	typedef Functor<typename InFunctor::ResultType, typename InFunctor::ParmList::Tail> OutFunctor;
	typedef typename InFunctor::Parm1 Bound;
	typedef typename InFunctor::ResultType ResultType;

	InFunctor _fun;
	Bound _val;

public:
	Binder(const InFunctor& fun, Bound bound) :_fun(fun), _val(bound) {}

	Binder* Clone() const {
		return new Binder(*this);
	}

	ResultType operator()() {
		return _fun(_val);
	}
	ResultType operator()(typename OutFunctor::Parm1 p1) {
		return _fun(_val, p1);
	}
	ResultType operator()(typename OutFunctor::Parm1 p1, typename OutFunctor::Parm2 p2) {
		return _fun(_val, p1, p2);
	}
	ResultType operator()(typename OutFunctor::Parm1 p1, typename OutFunctor::Parm2 p2, typename OutFunctor::Parm3 p3) {
		return _fun(_val, p1, p2, p3);
	}
	ResultType operator()(typename OutFunctor::Parm1 p1, typename OutFunctor::Parm2 p2, typename OutFunctor::Parm3 p3, typename OutFunctor::Parm4 p4) {
		return _fun(_val, p1, p2, p3, p4);
	}
	ResultType operator()(typename OutFunctor::Parm1 p1, typename OutFunctor::Parm2 p2, typename OutFunctor::Parm3 p3, typename OutFunctor::Parm4 p4, typename OutFunctor::Parm5 p5) {
		return _fun(_val, p1, p2, p3, p4, p5);
	}
	ResultType operator()(typename OutFunctor::Parm1 p1, typename OutFunctor::Parm2 p2, typename OutFunctor::Parm3 p3, typename OutFunctor::Parm4 p4, typename OutFunctor::Parm5 p5,
		typename OutFunctor::Parm6 p6) {
		return _fun(_val, p1, p2, p3, p4, p5, p6);
	}
	ResultType operator()(typename OutFunctor::Parm1 p1, typename OutFunctor::Parm2 p2, typename OutFunctor::Parm3 p3, typename OutFunctor::Parm4 p4, typename OutFunctor::Parm5 p5,
		typename OutFunctor::Parm6 p6, typename OutFunctor::Parm7 p7) {
		return _fun(_val, p1, p2, p3, p4, p5, p6, p7);
	}
	ResultType operator()(typename OutFunctor::Parm1 p1, typename OutFunctor::Parm2 p2, typename OutFunctor::Parm3 p3, typename OutFunctor::Parm4 p4, typename OutFunctor::Parm5 p5,
		typename OutFunctor::Parm6 p6, typename OutFunctor::Parm7 p7, typename OutFunctor::Parm8 p8) {
		return _fun(_val, p1, p2, p3, p4, p5, p6, p7, p8);
	}
	ResultType operator()(typename OutFunctor::Parm1 p1, typename OutFunctor::Parm2 p2, typename OutFunctor::Parm3 p3, typename OutFunctor::Parm4 p4, typename OutFunctor::Parm5 p5,
		typename OutFunctor::Parm6 p6, typename OutFunctor::Parm7 p7, typename OutFunctor::Parm8 p8, typename OutFunctor::Parm9 p9) {
		return _fun(_val, p1, p2, p3, p4, p5, p6, p7, p8, p9);
	}
};

template <class Fctor>
Binder<Fctor>
Bind(const Fctor& fun, typename Fctor::Parm1 bound1) {
	return Binder<Fctor>(fun, bound1);
}

template <class Fctor>
Binder<Functor<typename Fctor::ResultType, typename Fctor::ParmList::Tail> >
Bind(const Fctor& fun, typename Fctor::Parm1 bound1, typename Fctor::Parm2 bound2) {
	typedef typename Fctor::ParmList::Tail ParmList;
	typedef typename Fctor::ResultType ResultType;
	Functor<ResultType, ParmList> _fun1(Bind(fun, bound1));

	return Binder<Functor<ResultType, ParmList> >(_fun1, bound2);
}

template <class Fctor>
Binder<Functor<typename Fctor::ResultType, typename Fctor::ParmList::Tail::Tail> >
Bind(const Fctor& fun, typename Fctor::Parm1 bound1, typename Fctor::Parm2 bound2, typename Fctor::Parm3 bound3) {
	typedef typename Fctor::ParmList::Tail::Tail ParmList;
	typedef typename Fctor::ResultType ResultType;
	Functor<ResultType, ParmList> _fun1(Bind(fun, bound1, bound2));

	return Binder<Functor<ResultType, ParmList> >(_fun1, bound3);
}

template <class Fctor>
Binder<Functor<typename Fctor::ResultType, typename Fctor::ParmList::Tail::Tail::Tail> >
Bind(const Fctor& fun, typename Fctor::Parm1 bound1, typename Fctor::Parm2 bound2, typename Fctor::Parm3 bound3, typename Fctor::Parm4 bound4) {
	typedef typename Fctor::ParmList::Tail::Tail::Tail ParmList;
	typedef typename Fctor::ResultType ResultType;
	Functor<ResultType, ParmList> _fun1(Bind(fun, bound1, bound2, bound3));

	return Binder<Functor<ResultType, ParmList> >(_fun1, bound4);
}

template <class Fctor>
Binder<Functor<typename Fctor::ResultType, typename Fctor::ParmList::Tail::Tail::Tail::Tail> >
Bind(const Fctor& fun, typename Fctor::Parm1 bound1, typename Fctor::Parm2 bound2, typename Fctor::Parm3 bound3, typename Fctor::Parm4 bound4, typename Fctor::Parm5 bound5) {
	typedef typename Fctor::ParmList::Tail::Tail::Tail::Tail ParmList;
	typedef typename Fctor::ResultType ResultType;
	Functor<ResultType, ParmList> _fun1(Bind(fun, bound1, bound2, bound3, bound4));

	return Binder<Functor<ResultType, ParmList> >(_fun1, bound5);
}

template <class Fctor>
Binder<Functor<typename Fctor::ResultType, typename Fctor::ParmList::Tail::Tail::Tail::Tail::Tail> >
Bind(const Fctor& fun, typename Fctor::Parm1 bound1, typename Fctor::Parm2 bound2, typename Fctor::Parm3 bound3, typename Fctor::Parm4 bound4, typename Fctor::Parm5 bound5,
	typename Fctor::Parm6 bound6) {
	typedef typename Fctor::ParmList::Tail::Tail::Tail::Tail::Tail ParmList;
	typedef typename Fctor::ResultType ResultType;
	Functor<ResultType, ParmList> _fun1(Bind(fun, bound1, bound2, bound3, bound4, bound5));

	return Binder<Functor<ResultType, ParmList> >(_fun1, bound6);
}

template <class Fctor>
Binder<Functor<typename Fctor::ResultType, typename Fctor::ParmList::Tail::Tail::Tail::Tail::Tail::Tail> >
Bind(const Fctor& fun, typename Fctor::Parm1 bound1, typename Fctor::Parm2 bound2, typename Fctor::Parm3 bound3, typename Fctor::Parm4 bound4, typename Fctor::Parm5 bound5,
	typename Fctor::Parm6 bound6, typename Fctor::Parm7 bound7) {
	typedef typename Fctor::ParmList::Tail::Tail::Tail::Tail::Tail::Tail ParmList;
	typedef typename Fctor::ResultType ResultType;
	Functor<ResultType, ParmList> _fun1(Bind(fun, bound1, bound2, bound3, bound4, bound5, bound6));

	return Binder<Functor<ResultType, ParmList> >(_fun1, bound7);
}

template <class Fctor>
Binder<Functor<typename Fctor::ResultType, typename Fctor::ParmList::Tail::Tail::Tail::Tail::Tail::Tail::Tail> >
Bind(const Fctor& fun, typename Fctor::Parm1 bound1, typename Fctor::Parm2 bound2, typename Fctor::Parm3 bound3, typename Fctor::Parm4 bound4, typename Fctor::Parm5 bound5,
	typename Fctor::Parm6 bound6, typename Fctor::Parm7 bound7, typename Fctor::Parm8 bound8) {
	typedef typename Fctor::ParmList::Tail::Tail::Tail::Tail::Tail::Tail::Tail ParmList;
	typedef typename Fctor::ResultType ResultType;
	Functor<ResultType, ParmList> _fun1(Bind(fun, bound1, bound2, bound3, bound4, bound5, bound6, bound7));

	return Binder<Functor<ResultType, ParmList> >(_fun1, bound8);
}

template <class Fctor>
Binder<Functor<typename Fctor::ResultType, typename Fctor::ParmList::Tail::Tail::Tail::Tail::Tail::Tail::Tail::Tail> >
Bind(const Fctor& fun, typename Fctor::Parm1 bound1, typename Fctor::Parm2 bound2, typename Fctor::Parm3 bound3, typename Fctor::Parm4 bound4, typename Fctor::Parm5 bound5,
	typename Fctor::Parm6 bound6, typename Fctor::Parm7 bound7, typename Fctor::Parm8 bound8, typename Fctor::Parm9 bound9) {
	typedef typename Fctor::ParmList::Tail::Tail::Tail::Tail::Tail::Tail::Tail::Tail ParmList;
	typedef typename Fctor::ResultType ResultType;
	Functor<ResultType, ParmList> _fun1(Bind(fun, bound1, bound2, bound3, bound4, bound5, bound6, bound7, bound8));

	return Binder<Functor<ResultType, ParmList> >(_fun1, bound9);
}

template <class Fctor>
Binder<Functor<typename Fctor::ResultType, typename Fctor::ParmList::Tail::Tail::Tail::Tail::Tail::Tail::Tail::Tail::Tail> >
Bind(const Fctor& fun, typename Fctor::Parm1 bound1, typename Fctor::Parm2 bound2, typename Fctor::Parm3 bound3, typename Fctor::Parm4 bound4, typename Fctor::Parm5 bound5,
	typename Fctor::Parm6 bound6, typename Fctor::Parm7 bound7, typename Fctor::Parm8 bound8, typename Fctor::Parm9 bound9, typename Fctor::Parm10 bound10) {
	typedef typename Fctor::ParmList::Tail::Tail::Tail::Tail::Tail::Tail::Tail::Tail::Tail ParmList;
	typedef typename Fctor::ResultType ResultType;
	Functor<ResultType, ParmList> _fun1(Bind(fun, bound1, bound2, bound3, bound4, bound5, bound6, bound7, bound8, bound9));

	return Binder<Functor<ResultType, ParmList> >(_fun1, bound10);
}