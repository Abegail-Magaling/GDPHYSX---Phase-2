#pragma once
#include "../Force/ForceGenerator.h"

/*
	bungees are basically chains in a way that they also add force to the object towards the anchor point
	but its of an instant force, it gradually adds force
*/
namespace physics {
	class bungee : public ForceGenerator
	{
	public:
		//point in the world where the other end of the spring is
		MyVector anchorPoint;

		//spring constant
		//How "stiff" the spring is
		float springConstant;

		//rest length of the spring
		float restLength;

		float dampingConst = 0.5f;

	public:
		bungee(MyVector pos, float _springConst, float _restLen) : anchorPoint(pos), springConstant(_springConst), restLength(_restLen) {}

		void UpdateForce(PhysicsParticle* particle, float time) override;

	};
}


