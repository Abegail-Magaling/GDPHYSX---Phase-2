#include "Rod.h"

using namespace physics;

ParticleContact *Rod::GetContact()
{
    float currLen = CurrentLength();

    if (currLen == length) return nullptr;

    ParticleContact* ret = new ParticleContact();

    ret->particles[0] = particles[0];
    ret->particles[1] = particles[1];

    MyVector dir = particles[1]->Position - particles[0]->Position;
    dir = dir.direction();
    
    if (currLen > length)
    {
        ret->contactNormal = dir;
        //Positive depth to compute interpenetration
        ret->depth = currLen - length;
    }
    else
    {
        //ret->contactNormal = dir.ScalarMultiplication(-1);
        //ret->depth = length - currLen;
    }

    ret->restitution = restitution;
    return ret;
}