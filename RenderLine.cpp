#include "RenderLine.h"

void RenderLine::Update(physics::MyVector p1, physics::MyVector p2, glm::mat4 projectionMatrix, glm::mat4 viewMatrix)
{
	P1 = p1;
	P2 = p2;
	this->ProjectionMatrix = projectionMatrix;
	this->ViewMatrix = viewMatrix;
}

void RenderLine::Draw()
{
	glUseProgram(0);

	glm::vec4 d1 = this->ProjectionMatrix * this->ViewMatrix * glm::vec4(P1.x, P1.y, P1.z, 1.0f);
	glm::vec4 d2 = this->ProjectionMatrix * this->ViewMatrix * glm::vec4(P2.x, P2.y, P2.z, 1.0f);


	d1 = normalizeByMaxComponent(d1);
	d2 = normalizeByMaxComponent(d2);

	glBegin(GL_LINES);
	glVertex3f(d1.x, d1.y, d1.z);
	glVertex3f(d2.x, d2.y, d2.z);
	glEnd();
}

glm::vec4 RenderLine::normalizeByMaxComponent(const glm::vec4& vec) {
	float maxComponent = std::max({ vec.x, vec.y, vec.z, vec.w });
	return vec / maxComponent;
}


