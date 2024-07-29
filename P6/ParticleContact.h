#pragma once
#include "PhysicsParticle.h"

namespace physics 
{
	class ParticleContact
	{
	public:
		float depth;

	public:
		//The particles in contact
		PhysicsParticle* particles[2];
		//Holds the coefficient of restitution
		float restitution;
		//Contact normal of this collision
		MyVector contactNormal;
		//Resolve this contact
		void Resolve(float time);

	protected:
		void ResolveInterpenetration(float time);

	public:
		//Get the seperating speed of this collision
		float GetSeparatingSpeed();
		//Calculates the nnew velocities of thhe objects
		void ResolveVelocity(float time);
	};
}



