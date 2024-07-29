#pragma once
#include <list>

#include "Links/ParticleLink.h"
#include "Force/ForceRegistry.h"
#include "Force/GravityForceGenerator.h"
#include "ContactResolver.h"
#include <vector>


namespace physics {
	class ParticleContact;

	class PhysicsWorld
	{
	public:
		//The list of all links
		std::list<ParticleLink*> Links;

		//The list of ALL our particles
		std::list<PhysicsParticle*> Particles;

		//Function to add particles to the list
		void AddParticle(PhysicsParticle* toAdd);

		//Universal update function to call the updates of All
		void Update(float time);

		ForceRegistry forceRegistry;

	private:
		//Updates the particle list
		void UpdateParticleList();

		// Gravity force generator
		GravityForceGenerator Gravity;

	public:
		//Create a Dynamic Array of Contacts
		//You can use the vector cass for this
		std::vector<ParticleContact*> Contacts;
		//Function to easily add contacts
		void AddContact(PhysicsParticle* p1, PhysicsParticle* p2, float restitution, MyVector contactNormal, float depth);

	protected:
		ContactResolver contactResolver = ContactResolver(20);

	public:
		// Constructor to initialize gravity with user input
		PhysicsWorld(const MyVector& gravity)
			: Gravity(GravityForceGenerator(gravity)), gravity(gravity) {}

		void GetOverlaps();

		void GenerateContacts();

		MyVector gravity;
	};
}


