#pragma once
#include "PacketBinder.h"

class WithObject{};
class NoObject {};

template<class Obj>
class Packet {
	Functor<void, NullType> functor;

public:

	template<class Fun>
	Packet(Obj& obj, Fun fun) {
		functor = Functor<void, NullType>(fun, obj);
	}

	template<class Fun, class Parm1>
	Packet(Obj& obj, Fun fun, Parm1 val1) {
		Functor<void, TYPELIST_1(Parm1)> baseFun(fun, obj);
		PacketBinder<TYPELIST_1(Parm1)> bind(baseFun, val1);
		functor = bind.GetBind();
	}

	template<class Fun, class Parm1, class Parm2>
	Packet(Obj& obj, Fun fun, Parm1 val1, Parm2 val2) {
		Functor<void, TYPELIST_2(Parm1, Parm2)> baseFun(fun, obj);
		PacketBinder<TYPELIST_2(Parm1, Parm2)> bind(baseFun, val1, val2);
		functor = bind.GetBind();
	}

	template<class Fun, class Parm1, class Parm2, class Parm3>
	Packet(Obj& obj, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3) {
		Functor<void, TYPELIST_3(Parm1, Parm2, Parm3)> baseFun(fun, obj);
		PacketBinder<TYPELIST_3(Parm1, Parm2, Parm3)> bind(baseFun, val1, val2, val3);
		functor = bind.GetBind();
	}

	template<class Fun, class Parm1, class Parm2, class Parm3, class Parm4>
	Packet(Obj& obj, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4) {
		Functor<void, TYPELIST_4(Parm1, Parm2, Parm3, Parm4)> baseFun(fun, obj);
		PacketBinder<TYPELIST_4(Parm1, Parm2, Parm3, Parm4)> bind(baseFun, val1, val2, val3, val4);
		functor = bind.GetBind();
	}

	template<class Fun, class Parm1, class Parm2, class Parm3, class Parm4, class Parm5>
	Packet(Obj& obj, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5) {
		Functor<void, TYPELIST_5(Parm1, Parm2, Parm3, Parm4, Parm5)> baseFun(fun, obj);
		PacketBinder<TYPELIST_5(Parm1, Parm2, Parm3, Parm4, Parm5)> bind(baseFun, val1, val2, val3, val4, val5);
		functor = bind.GetBind();
	}

	template<class Fun, class Parm1, class Parm2, class Parm3, class Parm4, class Parm5, class Parm6>
	Packet(Obj& obj, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5, Parm6 val6) {
		Functor<void, TYPELIST_6(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6)> baseFun(fun, obj);
		PacketBinder<TYPELIST_6(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6)> bind(baseFun, val1, val2, val3, val4, val5, val6);
		functor = bind.GetBind();
	}

	template<class Fun, class Parm1, class Parm2, class Parm3, class Parm4, class Parm5, class Parm6, class Parm7>
	Packet(Obj& obj, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5, Parm6 val6, Parm7 val7) {
		Functor<void, TYPELIST_7(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7)> baseFun(fun, obj);
		PacketBinder<TYPELIST_7(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7)> bind(baseFun, val1, val2, val3, val4, val5, val6, val7);
		functor = bind.GetBind();
	}

	template<class Fun, class Parm1, class Parm2, class Parm3, class Parm4, class Parm5, class Parm6, class Parm7, class Parm8>
	Packet(Obj& obj, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5, Parm6 val6, Parm7 val7, Parm8 val8) {
		Functor<void, TYPELIST_8(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7, Parm8)> baseFun(fun, obj);
		PacketBinder<TYPELIST_8(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7, Parm8)> bind(baseFun, val1, val2, val3, val4, val5, val6, val7, val8);
		functor = bind.GetBind();
	}

	template<class Fun, class Parm1, class Parm2, class Parm3, class Parm4, class Parm5, class Parm6, class Parm7, class Parm8, class Parm9>
	Packet(Obj& obj, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5, Parm6 val6, Parm7 val7, Parm8 val8, Parm9 val9) {
		Functor<void, TYPELIST_9(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7, Parm8, Parm9)> baseFun(fun, obj);
		PacketBinder<TYPELIST_9(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7, Parm8, Parm9)> bind(baseFun, val1, val2, val3, val4, val5, val6, val7, val8, val9);
		functor = bind.GetBind();
	}

	template<class Fun, class Parm1, class Parm2, class Parm3, class Parm4, class Parm5, class Parm6, class Parm7, class Parm8, class Parm9, class Parm10>
	Packet(Obj& obj, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5, Parm6 val6, Parm7 val7, Parm8 val8, Parm9 val9, Parm10 val10) {
		Functor<void, TYPELIST_10(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7, Parm8, Parm9, Parm10)> baseFun(fun, obj);
		PacketBinder<TYPELIST_10(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7, Parm8, Parm9, Parm10)> bind(baseFun, val1, val2, val3, val4, val5, val6, val7, val8, val9, val10);
		functor = bind.GetBind();
	}

	Functor<void, NullType> GetFunctor() { return functor; }

};

template<>
class Packet<NoObject> {
	Functor<void, NullType> functor;

public:

	template<class Fun>
	Packet(NoObject&, Fun fun) {
		functor = Functor<void, NullType>(fun);
	}

	template<class Fun, class Parm1>
	Packet(NoObject&, Fun fun, Parm1 val1) {
		Functor<void, TYPELIST_1(Parm1)> baseFun(fun);
		PacketBinder<TYPELIST_1(Parm1)> bind(baseFun, val1);
		functor = bind.GetBind();
	}

	template<class Fun, class Parm1, class Parm2>
	Packet(NoObject&, Fun fun, Parm1 val1, Parm2 val2) {
		Functor<void, TYPELIST_2(Parm1, Parm2)> baseFun(fun);
		PacketBinder<TYPELIST_2(Parm1, Parm2)> bind(baseFun, val1, val2);
		functor = bind.GetBind();
	}

	template<class Fun, class Parm1, class Parm2, class Parm3>
	Packet(NoObject&, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3) {
		Functor<void, TYPELIST_3(Parm1, Parm2, Parm3)> baseFun(fun);
		PacketBinder<TYPELIST_3(Parm1, Parm2, Parm3)> bind(baseFun, val1, val2, val3);
		functor = bind.GetBind();
	}

	template<class Fun, class Parm1, class Parm2, class Parm3, class Parm4>
	Packet(NoObject&, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4) {
		Functor<void, TYPELIST_4(Parm1, Parm2, Parm3, Parm4)> baseFun(fun);
		PacketBinder<TYPELIST_4(Parm1, Parm2, Parm3, Parm4)> bind(baseFun, val1, val2, val3, val4);
		functor = bind.GetBind();
	}

	template<class Fun, class Parm1, class Parm2, class Parm3, class Parm4, class Parm5>
	Packet(NoObject&, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5) {
		Functor<void, TYPELIST_5(Parm1, Parm2, Parm3, Parm4, Parm5)> baseFun(fun);
		PacketBinder<TYPELIST_5(Parm1, Parm2, Parm3, Parm4, Parm5)> bind(baseFun, val1, val2, val3, val4, val5);
		functor = bind.GetBind();
	}

	template<class Fun, class Parm1, class Parm2, class Parm3, class Parm4, class Parm5, class Parm6>
	Packet(NoObject&, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5, Parm6 val6) {
		Functor<void, TYPELIST_6(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6)> baseFun(fun);
		PacketBinder<TYPELIST_6(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6)> bind(baseFun, val1, val2, val3, val4, val5, val6);
		functor = bind.GetBind();
	}

	template<class Fun, class Parm1, class Parm2, class Parm3, class Parm4, class Parm5, class Parm6, class Parm7>
	Packet(NoObject&, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5, Parm6 val6, Parm7 val7) {
		Functor<void, TYPELIST_7(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7)> baseFun(fun);
		PacketBinder<TYPELIST_7(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7)> bind(baseFun, val1, val2, val3, val4, val5, val6, val7);
		functor = bind.GetBind();
	}

	template<class Fun, class Parm1, class Parm2, class Parm3, class Parm4, class Parm5, class Parm6, class Parm7, class Parm8>
	Packet(NoObject&, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5, Parm6 val6, Parm7 val7, Parm8 val8) {
		Functor<void, TYPELIST_8(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7, Parm8)> baseFun(fun);
		PacketBinder<TYPELIST_8(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7, Parm8)> bind(baseFun, val1, val2, val3, val4, val5, val6, val7, val8);
		functor = bind.GetBind();
	}

	template<class Fun, class Parm1, class Parm2, class Parm3, class Parm4, class Parm5, class Parm6, class Parm7, class Parm8, class Parm9>
	Packet(NoObject&, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5, Parm6 val6, Parm7 val7, Parm8 val8, Parm9 val9) {
		Functor<void, TYPELIST_9(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7, Parm8, Parm9)> baseFun(fun);
		PacketBinder<TYPELIST_9(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7, Parm8, Parm9)> bind(baseFun, val1, val2, val3, val4, val5, val6, val7, val8, val9);
		functor = bind.GetBind();
	}

	template<class Fun, class Parm1, class Parm2, class Parm3, class Parm4, class Parm5, class Parm6, class Parm7, class Parm8, class Parm9, class Parm10>
	Packet(NoObject&, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5, Parm6 val6, Parm7 val7, Parm8 val8, Parm9 val9, Parm10 val10) {
		Functor<void, TYPELIST_10(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7, Parm8, Parm9, Parm10)> baseFun(fun);
		PacketBinder<TYPELIST_10(Parm1, Parm2, Parm3, Parm4, Parm5, Parm6, Parm7, Parm8, Parm9, Parm10)> bind(baseFun, val1, val2, val3, val4, val5, val6, val7, val8, val9, val10);
		functor = bind.GetBind();
	}

	Functor<void, NullType> GetFunctor() { return functor; }

};

class UniversalPacketImpl {
public:
	virtual UniversalPacketImpl* Clone() const = 0;

	virtual void operator()() = 0;

	virtual ~UniversalPacketImpl() {};
};

template<class Obj>
class UniversalPacketHandler: public UniversalPacketImpl {
	Functor<void, NullType> functor;
	Obj& obj;
public:
	UniversalPacketHandler(const Functor<void, NullType>& fun, Obj& obj_) :functor(fun), obj(obj_) {}

	UniversalPacketHandler* Clone() const {
		return new UniversalPacketHandler(functor, obj);
	}

	void operator()() {
		obj.ActionManager::AddAction(functor);
	}

	~UniversalPacketHandler() {}
};

template<>
class UniversalPacketHandler<NoObject>: public UniversalPacketImpl {
	Functor<void, NullType> functor;
public:
	UniversalPacketHandler(const Functor<void, NullType>& fun, const NoObject&) :functor(fun) {}

	UniversalPacketHandler* Clone() const {
		return new UniversalPacketHandler(functor, NoObject());
	}

	void operator()() {
		functor();
	}

	~UniversalPacketHandler() {}
};

class UniversalPacket {
	std::auto_ptr<UniversalPacketImpl> impl;
public:
	template<class Obj>
	UniversalPacket(const Functor<void, NullType>& functor_, Obj& obj): impl(new UniversalPacketHandler<Obj>(functor_,obj)) {}

	UniversalPacket(const UniversalPacket& packet) :impl(packet.impl->Clone()) {}

	void operator()() {
		(*impl)();
	}
};