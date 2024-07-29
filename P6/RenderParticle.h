#pragma once
#include "PhysicsWorld.h"
#include "../GameObject.h"
using namespace physics;

class RenderParticle
{
public:
	physics::PhysicsParticle* PhysicsParticle;

	GameObject* RenderObject;

	glm::vec4 Color;

	float scale;

	RenderParticle(physics::PhysicsParticle* p, GameObject* obj, glm::vec4 c, float scale) : PhysicsParticle(p), RenderObject(obj), Color(c), scale(scale) {};

	void Draw(glm::mat4 identity_matrix, glm::mat4 projection_matrix, glm::mat4 view_matrix);
};

