#pragma once

#include"../Force/ForceGenerator.h"


/*
	Chains are when a force is instantly added to the object at the end of the chain towards the anchor point
	when the chain reached its max length
*/
namespace physics {
	class Chain : public ForceGenerator
	{
	public:
		//point in the world where the other end of the spring is
		MyVector anchorPoint;

		//spring constant
		//How "stiff" the spring is
		float springConstant;

		//rest length of the spring
		float restLength;


	public:
		Chain(MyVector pos, float _springConst, float _restLen) : anchorPoint(pos), springConstant(_springConst), restLength(_restLen) {}

		void UpdateForce(PhysicsParticle* particle, float time) override;

	};
}

