#include "ParticleContact.h"

using namespace physics;

void ParticleContact::Resolve(float time)
{
    //Call resolve velocity for now
    ResolveVelocity(time);

    ResolveInterpenetration(time);
}

void ParticleContact::ResolveInterpenetration(float time)
{
    if (depth <= 0) return;

    float totalMass = (float)1 / particles[0]->mass;
    if (particles[1]) totalMass += (float)1 / particles[1]->mass;

    if (totalMass <= 0) return;

    float totalMoveByMass = depth / totalMass;

    MyVector moveByMass = contactNormal * totalMoveByMass;

    MyVector P_a = moveByMass * ((float)1 / particles[0]->mass);
    //               Vf    =   Vi
    particles[0]->Position += P_a;

    if (particles[1]) {
        //Apply impulse in the oppisite direction for B
        MyVector P_b = moveByMass * ((float)1 / particles[0]->mass);
        //               Vf    =   Vi
        particles[0]->Position += P_b;
    }

    depth = 0;
}

float ParticleContact::GetSeparatingSpeed()
{
    MyVector velocity = particles[0]->Velocity;

    if (particles[1]) velocity -= particles[1]->Velocity;

    return velocity.DotProd(contactNormal);
}

void ParticleContact::ResolveVelocity(float time)
{
    float separatingSpeed = GetSeparatingSpeed();

    //If the object is already movig away from each other, Skip
    if (separatingSpeed > 0) {
        return;
    }

    // SAfter = -c * sS
    float newSS = -restitution * separatingSpeed;
    //Magnitude of our delta velocity
    float deltaSpeed = newSS - separatingSpeed;

    //Get the total inverse mass of the colliding particles
    //We'll apply impulse based on thhis later
    float totalMass = (float)1 / particles[0]->mass;
    if (particles[1]) totalMass += (float)1 / particles[1]->mass;

    //Invalid collision if total mass is 0 or less
    if (totalMass <= 0) return;

    //Magnitude of impusle needed to apply in this collision
    //          i     =     mass    * delta speed
    float impulse_mag = deltaSpeed / totalMass;
    //Get the impulse vector using the contact normal
    MyVector Impulse = contactNormal * impulse_mag;

    //Change in V for Particle A
    //        V  =  I      /    M
    MyVector V_a = Impulse * ((float)1 / particles[0]->mass);
    //               Vf    =   Vi
    particles[0]->Velocity = particles[0]->Velocity + V_a;

    if (particles[1]) {
        //Apply impulse in the oppisite direction for B
        MyVector V_b = Impulse * ((float)-1 / particles[1]->mass);
        //              Vf     =    Vi                  +  I/m
        particles[1]->Velocity = particles[1]->Velocity + V_b;
    }
}
