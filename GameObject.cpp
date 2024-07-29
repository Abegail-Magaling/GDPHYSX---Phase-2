#define TINYOBJLOADER_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION
#include "GameObject.h"

using namespace physics;

GameObject::GameObject(std::string Mesh_Path, std::string Vert_Path, std::string Frag_Path)
{
	Shader* shader = new Shader(Vert_Path, Frag_Path);
	LoadMesh(Mesh_Path);
	LoadVertices();
	this->shaderProgram = shader->getShaderProg();

	this->x = 0.0f;
	this->y = 180.0f;
	this->z = 0.0f;

	this->IdentityMatrix = glm::mat4(1.0f);
}

GameObject::~GameObject()
{

}

void GameObject::Draw(glm::mat4 identity_matrix, glm::mat4 projection_matrix, glm::mat4 view_matrix, float scale)
{
	glUseProgram(this->shaderProgram);

	glm::mat4 transformation_matrix = glm::translate(identity_matrix, (glm::vec3)Position);
	transformation_matrix = glm::scale(transformation_matrix, (glm::vec3)scale);
	transformation_matrix = glm::rotate(transformation_matrix, glm::radians(0.0f), glm::normalize(glm::vec3(0.0f, 1.0f, 0.0)));

	unsigned int projectionLoc = glGetUniformLocation(this->shaderProgram, "projection");
	glUniformMatrix4fv(projectionLoc, 1, GL_FALSE, glm::value_ptr(projection_matrix));

	unsigned int transformLoc = glGetUniformLocation(this->shaderProgram, "transform");
	glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(transformation_matrix));
	glBindVertexArray(this->VAO);

	unsigned int viewLoc = glGetUniformLocation(this->shaderProgram, "view");
	glUniformMatrix4fv(viewLoc, 1, GL_FALSE, glm::value_ptr(view_matrix));

	unsigned int colorLoc = glGetUniformLocation(this->shaderProgram, "color");
	glUniform4fv(colorLoc, 1, glm::value_ptr(this->color));

	glDrawArrays(GL_TRIANGLES, 0, this->fullVertexData.size() / 8);
}

void GameObject::LoadMesh(std::string Mesh_Path)
{
	std::string path = Mesh_Path;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> material;
	std::string warning, error;

	bool success = tinyobj::LoadObj(
		&this->attributes,
		&shapes,
		&material,
		&warning,
		&error,
		path.c_str());

	if (!success)
	{
		std::cout << "FAILED TO LOAD MESH: " << Mesh_Path << std::endl;
	}

	for (size_t i = 0; i < shapes[0].mesh.indices.size(); i++)
	{
		this->mesh_indices.push_back(shapes[0].mesh.indices[i].vertex_index);
	}

	for (size_t i = 0; i < shapes[0].mesh.indices.size(); i++)
	{
		tinyobj::index_t vData = shapes[0].mesh.indices[i];

		fullVertexData.push_back(attributes.vertices[vData.vertex_index * 3]);      // X pos
		fullVertexData.push_back(attributes.vertices[vData.vertex_index * 3 + 1]);  // Y pos
		fullVertexData.push_back(attributes.vertices[vData.vertex_index * 3 + 2]);  // Z pos

		fullVertexData.push_back(attributes.normals[vData.normal_index * 3]);       // R nor
		fullVertexData.push_back(attributes.normals[vData.normal_index * 3 + 1]);   // S nor
		fullVertexData.push_back(attributes.normals[vData.normal_index * 3 + 2]);   // T nor

		fullVertexData.push_back(attributes.texcoords[vData.texcoord_index * 2]);       // U tex
		fullVertexData.push_back(attributes.texcoords[vData.texcoord_index * 2 + 1]);   // V tex
	}
}

void GameObject::LoadVertices()
{
	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);

	glUseProgram(this->shaderProgram);

	glBindVertexArray(this->VAO);

	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(GL_FLOAT) * this->fullVertexData.size(), this->fullVertexData.data(), GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)0);

	GLuint normalsPtr = 3 * sizeof(GLfloat);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)normalsPtr);

	GLuint uvPtr = 6 * sizeof(GLfloat);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GL_FLOAT), (void*)uvPtr);

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

