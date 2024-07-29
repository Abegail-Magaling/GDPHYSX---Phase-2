#pragma once
#include "ParticleLink.h"

namespace physics
{
    class Rod : public ParticleLink
    {
    public:
        //Length of the ROd (In Meters)
        float length = 1;
        //Always set restituion to 0
        //Since a rod has no bounciness
        float restitution = 0;

        //Override the link's GetContact
        ParticleContact* GetContact() override;
    };
}