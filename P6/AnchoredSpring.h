#pragma once
#include "Force/ForceGenerator.h"

namespace physics
{
	class AnchoredSpring :
		public ForceGenerator
	{
		public:
			//Point in the world where
			//the other end of the spring is
			MyVector anchorPoint;
			//Spring constant
			//How "stiff" this spring is
			float SpringConstant;
			//Rest length of the spring
			float restLength;

		public:
			//Constructor for spring
			AnchoredSpring(MyVector pos, float _springConst, float _restLen) :
				anchorPoint(pos), SpringConstant(_springConst), restLength(_restLen) {}

			//Override the Update Force of the Generator
			void UpdateForce(PhysicsParticle* particle, float time) override;
	};
}


