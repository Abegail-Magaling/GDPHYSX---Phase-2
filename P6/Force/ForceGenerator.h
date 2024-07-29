#pragma once
#include "../PhysicsParticle.h"
using namespace physics;

class ForceGenerator
{
	public:
		virtual void UpdateForce(physics::PhysicsParticle* p, float time) {
			p->AddForce(MyVector(0, 0, 0));
		}

};

