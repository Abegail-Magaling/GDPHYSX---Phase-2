#include "RenderParticle.h"

void RenderParticle::Draw(glm::mat4 identity_matrix, glm::mat4 projection_matrix, glm::mat4 view_matrix)
{
	if (!PhysicsParticle->IsDestroyed()) {
		RenderObject->Position = PhysicsParticle->Position;

		RenderObject->color = Color;

		RenderObject->Draw(identity_matrix, projection_matrix, view_matrix, scale);
	}
}
