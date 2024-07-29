#include "bungee.h"

using namespace physics;

void bungee::UpdateForce(PhysicsParticle* particle, float time)
{
	//Get the current position of the particle
	MyVector pos = particle->Position;

	//Create a vector Pos -> Anchor Point
	MyVector force = pos - anchorPoint;

	//Get the magnitude of the vector above
	float mag = force.Magnitude();

	float springForce = -springConstant * abs(mag - restLength);

	//Get the direction from the particle to the anchor point
	if (mag < restLength) {
		springForce = 0;
	}

	//calculate the velocity of the particle
	MyVector velocity = particle->Velocity;

	//calculate the damping force
	float dampingForce = -dampingConst * velocity.Magnitude();

	MyVector dampingVec = velocity.direction();
	dampingVec = dampingVec.ScalarMultiplication(dampingForce);

	MyVector springforceVec = force.ScalarMultiplication(springForce);

	MyVector totalForce = springforceVec;

	//add force!

	particle->AddForce(totalForce);
}
