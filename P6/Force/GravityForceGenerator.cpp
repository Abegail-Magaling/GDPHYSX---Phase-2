#include "GravityForceGenerator.h"

void GravityForceGenerator::UpdateForce(PhysicsParticle* particle, float time)
{
	//Do nothing if mass is 0 below
	if (particle->mass <= 0) return;

	MyVector force = Gravity.ScalarMultiplication(particle->mass);
	particle->AddForce(force);
}
