#include "AnchoredSpring.h"
#include <iostream>
void AnchoredSpring::UpdateForce(PhysicsParticle* particle, float time)
{
	//Get the current position of the particle
	MyVector pos = particle->Position;

	//Create a vector Pos -> Anchor Point
	MyVector force = pos - anchorPoint;

	std::cout << pos.y << std::endl;
	//Get the magnitude of the vector above
	float mag = force.Magnitude();

	float springForce = -SpringConstant * abs(mag - restLength);

	//Get the direction from the
	//Particle to the anchor Point
	force = force.direction();
		
	//Apply the force using the direction above
	force = force.ScalarMultiplication(springForce);

	if (pos.y < -50)
	{
		//particle->SetAffectedByForce(false);
	}
	else
	{
		//Add Force!
		particle->AddForce(force);
		
	}


}
