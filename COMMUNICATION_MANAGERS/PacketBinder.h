#pragma once
#include <Functor.h>

template<class TList>
class PacketBinder;

template <>
class PacketBinder<NullType> {
	Functor<void, NullType> bind;

public:

	PacketBinder(const Functor<void, NullType>& fun) {
		bind = fun;
	}

	Functor<void, NullType> GetBind() { return bind; }
};

template <class Parm1>
class PacketBinder<TYPELIST_1(Parm1)> {
	Functor<void, NullType> bind;

public:

	PacketBinder(const Functor<void, TYPELIST_1(Parm1)>& fun, Parm1 val1) {
		bind = Bind(fun, val1);
	}

	Functor<void, NullType> GetBind() { return bind; }
};

template <class Parm1, class Parm2>
class PacketBinder<TYPELIST_2(Parm1, Parm2)> {
	Functor<void, NullType> bind;

public:

	PacketBinder(const Functor<void, TYPELIST_2(Parm1, Parm2)>& fun, Parm1 val1, Parm2 val2) {
		bind = Bind(fun, val1, val2);
	}

	Functor<void, NullType> GetBind() { return bind; }
};

template <class Parm1, class Parm2, class Parm3>
class PacketBinder<TYPELIST_3(Parm1, Parm2, Parm3)> {
	Functor<void, NullType> bind;

public:

	PacketBinder(const Functor<void, TYPELIST_3(Parm1, Parm2, Parm3)>& fun, Parm1 val1, Parm2 val2, Parm3 val3) {
		bind = Bind(fun, val1, val2, val3);
	}

	Functor<void, NullType> GetBind() { return bind; }
};

template <class Parm1, class Parm2, class Parm3, class Parm4>
class PacketBinder<TYPELIST_4(Parm1, Parm2, Parm3, Parm4)> {
	Functor<void, NullType> bind;

public:

	PacketBinder(const Functor<void, TYPELIST_4(Parm1, Parm2, Parm3, Parm4)>& fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4) {
		bind = Bind(fun, val1, val2, val3, val4);
	}

	Functor<void, NullType> GetBind() { return bind; }
};

template <class Parm1, class Parm2, class Parm3, class Parm4, class Parm5>
class PacketBinder<TYPELIST_5(Parm1, Parm2, Parm3, Parm4, Parm5)> {
	Functor<void, NullType> bind;

public:

	PacketBinder(const Functor<void, TYPELIST_5(Parm1, Parm2, Parm3, Parm4, Parm5)>& fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5) {
		bind = Bind(fun, val1, val2, val3, val4, val5);
	}

	Functor<void, NullType> GetBind() { return bind; }
};

template <class Parm1, class Parm2, class Parm3, class Parm4, class Parm5, class Parm6>
class PacketBinder<TYPELIST_6(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6)> {
	Functor<void, NullType> bind;

public:

	PacketBinder(const Functor<void, TYPELIST_6(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6)>& fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5, Parm6 val6) {
		bind = Bind(fun, val1, val2, val3, val4, val5,val6);
	}

	Functor<void, NullType> GetBind() { return bind; }
};

template <class Parm1, class Parm2, class Parm3, class Parm4, class Parm5, class Parm6,class Parm7>
class PacketBinder<TYPELIST_7(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7)> {
	Functor<void, NullType> bind;

public:

	PacketBinder(const Functor<void, TYPELIST_7(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7)>& fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5, Parm6 val6, Parm7 val7) {
		bind = Bind(fun, val1, val2, val3, val4, val5, val6, val7);
	}

	Functor<void, NullType> GetBind() { return bind; }
};

template <class Parm1, class Parm2, class Parm3, class Parm4, class Parm5, class Parm6, class Parm7, class Parm8>
class PacketBinder<TYPELIST_8(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7, Parm8)> {
	Functor<void, NullType> bind;

public:

	PacketBinder(const Functor<void, TYPELIST_8(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7, Parm8)>& fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5, Parm6 val6, Parm7 val7, Parm8 val8) {
		bind = Bind(fun, val1, val2, val3, val4, val5, val6, val7, val8);
	}

	Functor<void, NullType> GetBind() { return bind; }
};

template <class Parm1, class Parm2, class Parm3, class Parm4, class Parm5, class Parm6, class Parm7, class Parm8, class Parm9>
class PacketBinder<TYPELIST_9(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7, Parm8, Parm9)> {
	Functor<void, NullType> bind;

public:

	PacketBinder(const Functor<void, TYPELIST_9(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7, Parm8, Parm9)>& fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5, Parm6 val6, Parm7 val7, Parm8 val8, 
		Parm9 val9) {
		bind = Bind(fun, val1, val2, val3, val4, val5, val6, val7, val8, val9);
	}

	Functor<void, NullType> GetBind() { return bind; }
};

template <class Parm1, class Parm2, class Parm3, class Parm4, class Parm5, class Parm6, class Parm7, class Parm8, class Parm9, class Parm10>
class PacketBinder<TYPELIST_10(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7, Parm8, Parm9, Parm10)> {
	Functor<void, NullType> bind;

public:

	PacketBinder(const Functor<void, TYPELIST_10(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7, Parm8, Parm9, Parm10)>& fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5, Parm6 val6, Parm7 val7, 
		Parm8 val8, Parm9 val9, Parm10 val10) {
		bind = Bind(fun, val1, val2, val3, val4, val5, val6, val7, val8, val9, val10);
	}

	Functor<void, NullType> GetBind() { return bind; }
};