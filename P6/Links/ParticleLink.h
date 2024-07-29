#pragma once
#include "../ParticleContact.h"

namespace physics
{
    //Base class for all links
    class ParticleLink
    {
        public:
            //Particles that are linked
            PhysicsParticle* particles[2];
            //Returns a contact depending on condition
            virtual ParticleContact* GetContact() { return nullptr; };

        protected:
            //distance in bet 2 particles
            float CurrentLength();

    };
}



