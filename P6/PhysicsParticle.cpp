#include "PhysicsParticle.h"
#include <random>
#include <iostream>

using namespace physics;

physics::PhysicsParticle::PhysicsParticle()
{
	this->lifespan = 0;
	//this->AddLifeSpan();
	
}

void PhysicsParticle::UpdatePosition(float time)
{
	float newTime = time * time;
	this->Position = this->Position + (this->Velocity.ScalarMultiplication(time)) + ((this->Acceleration.ScalarMultiplication(newTime)).ScalarMultiplication(0.5f));
}

void PhysicsParticle::UpdateVelocity(float time)
{
	this->Acceleration += accumulatedForce.ScalarMultiplication(1 / mass);
	this->Velocity = this->Velocity + (this->Acceleration.ScalarMultiplication(time));

	this->Velocity = this->Velocity.ScalarMultiplication(powf(damping, time));
}

void PhysicsParticle::AddForce(MyVector force)
{
	this->accumulatedForce += force;
}

void physics::PhysicsParticle::ResetForce()
{
	this->accumulatedForce = MyVector(0, 0, 0);
	this->Acceleration = MyVector(0, 0, 0);
}

void PhysicsParticle::update(float time)
{
	if (this->affectedByForce == false) return;
	this->UpdatePosition(time);
	this->UpdateVelocity(time);
	//this->UpdateLifeSpan(time);

	this->ResetForce();
}

void PhysicsParticle::AddLifeSpan()
{
	std::random_device rd;

	// Use Mersenne Twister engine
	std::mt19937 gen(rd());

	// Define the range [1, 10]
	std::uniform_int_distribution<> dis(1.f, 10.f);

	// Generate and print a random number in the range [1, 10]
	//std::cout << dis(gen) << ' ';
	this->lifespan = dis(gen);

}

void physics::PhysicsParticle::UpdateLifeSpan(float time)
{
	this->lifespan -= 1 * time;
	//std::cout << lifespan << std::endl;
	//std::cout << time << std::endl;

	if (this->lifespan <= 0) {
		this->Destroy();
	}
}

void PhysicsParticle::Destroy()
{
	this->isDestroyed = true;
}

bool PhysicsParticle::GetAffectedByForce()
{
	return this->affectedByForce;
}
