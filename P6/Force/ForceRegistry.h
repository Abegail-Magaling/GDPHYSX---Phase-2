#pragma once
#include <list>
#include "ForceGenerator.h"

class ForceRegistry
{
	protected:
		struct ParticleForceRegistry
		{
			PhysicsParticle* particle;
			ForceGenerator* generator;
		};

		std::list<ParticleForceRegistry> Registry;

	public:
		void Add(PhysicsParticle* particle, ForceGenerator* generator);

		void Remove(PhysicsParticle* particle, ForceGenerator* generator);

		void Clear();

		void UpdateForces(float time);
};

