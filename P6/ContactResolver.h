#pragma once
#include <vector>

namespace physics
{
	class ParticleContact;

	class ContactResolver
	{

	public:
		//Max numver of Resolve Calls
		unsigned max_iterations;
		//Constructor to assign the max iterationns on init
		ContactResolver(unsigned _maxInterations) : max_iterations(_maxInterations) {}
		//Resolve all assigned contacts
		void ResolveContacts(std::vector<ParticleContact*> contacts, float time);

	protected:
		//Current number of Resolve Calls
		unsigned current_iterations = 0;
	};
}


