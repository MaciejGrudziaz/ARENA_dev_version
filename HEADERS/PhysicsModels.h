#pragma once
#include "StandardCollision.h"
#include "BulletCollision.h"

class PhysicsModels {
	PhysicsModels() {}
	PhysicsModels(const PhysicsModels&) {}
	PhysicsModels& operator=(const PhysicsModels&) {}

public:
	enum AvailableModels {StandardCollision,BulletCollision};

	template<class Model>
	static PhysicsModelImpl* CreateModel() { return new Model(); }
};