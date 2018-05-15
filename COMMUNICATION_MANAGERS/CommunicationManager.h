#pragma once
#include <vector>
#include "Packet.h"
#include "ActionManager.h"

class CommunicationManager {
	std::vector<UniversalPacket> packets;

	void AddPacket(const UniversalPacket& packet) {
		packets.push_back(packet);
	}

public:

	void DispatchPackets() {
		for (UniversalPacket& packet : packets)
			packet();
		packets.clear();
	}

	void SendPackets(CommunicationManager& manager) {
		for (const UniversalPacket& packet : packets)
			manager.AddPacket(packet);
		packets.clear();
	}

	template<class Obj, class Fun>
	void AddPacket(Obj& obj, Fun fun) {
		packets.push_back(UniversalPacket(Packet<Obj>(obj, fun).GetFunctor(),obj));
	}

	template<class Obj, class Fun, class Parm1>
	void AddPacket(Obj& obj, Fun fun, Parm1 val1) {
		packets.push_back(UniversalPacket(Packet<Obj>(obj, fun, val1).GetFunctor(), obj));
	}

	template<class Obj, class Fun, class Parm1, class Parm2>
	void AddPacket(Obj& obj, Fun fun, Parm1 val1, Parm2 val2) {
		packets.push_back(UniversalPacket(Packet<Obj>(obj, fun, val1, val2).GetFunctor(), obj));
	}

	template<class Obj, class Fun, class Parm1, class Parm2, class Parm3>
	void AddPacket(Obj& obj, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3) {
		packets.push_back(UniversalPacket(Packet<Obj>(obj, fun, val1, val2, val3).GetFunctor(), obj));
	}

	template<class Obj, class Fun, class Parm1, class Parm2, class Parm3, class Parm4>
	void AddPacket(Obj& obj, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4) {
		packets.push_back(UniversalPacket(Packet<Obj>(obj, fun, val1, val2, val3, val4).GetFunctor(), obj));
	}

	template<class Obj, class Fun, class Parm1, class Parm2, class Parm3, class Parm4, class Parm5>
	void AddPacket(Obj& obj, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5) {
		packets.push_back(UniversalPacket(Packet<Obj>(obj, fun, val1, val2, val3, val4, val5).GetFunctor(), obj));
	}

	template<class Obj, class Fun, class Parm1, class Parm2, class Parm3, class Parm4, class Parm5, class Parm6>
	void AddPacket(Obj& obj, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5, Parm6 val6) {
		packets.push_back(UniversalPacket(Packet<Obj>(obj, fun, val1, val2, val3, val4, val5, val6).GetFunctor(), obj));
	}

	template<class Obj, class Fun, class Parm1, class Parm2, class Parm3, class Parm4, class Parm5, class Parm6, class Parm7>
	void AddPacket(Obj& obj, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5, Parm6 val6, Parm7 val7) {
		packets.push_back(UniversalPacket(Packet<Obj>(obj, fun, val1, val2, val3, val4, val5, val6, val7).GetFunctor(), obj));
	}

	template<class Obj, class Fun, class Parm1, class Parm2, class Parm3, class Parm4, class Parm5, class Parm6, class Parm7, class Parm8>
	void AddPacket(Obj& obj, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5, Parm6 val6, Parm7 val7, Parm8 val8) {
		packets.push_back(UniversalPacket(Packet<Obj>(obj, fun, val1, val2, val3, val4, val5, val6, val7, val8).GetFunctor(), obj));
	}

	template<class Obj, class Fun, class Parm1, class Parm2, class Parm3, class Parm4, class Parm5, class Parm6, class Parm7, class Parm8, class Parm9>
	void AddPacket(Obj& obj, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5, Parm6 val6, Parm7 val7, Parm8 val8, Parm9 val9) {
		packets.push_back(UniversalPacket(Packet<Obj>(obj, fun, val1, val2, val3, val4, val5, val6, val7, val8, val9).GetFunctor(), obj));
	}

	template<class Obj, class Fun, class Parm1, class Parm2, class Parm3, class Parm4, class Parm5, class Parm6, class Parm7, class Parm8, class Parm9, class Parm10>
	void AddPacket(Obj& obj, Fun fun, Parm1 val1, Parm2 val2, Parm3 val3, Parm4 val4, Parm5 val5, Parm6 val6, Parm7 val7, Parm8 val8, Parm9 val9, Parm10 val10) {
		packets.push_back(UniversalPacket(Packet<Obj>(obj, fun, val1, val2, val3, val4, val5, val6, val7, val8, val9, val10).GetFunctor(), obj));
	}

};

