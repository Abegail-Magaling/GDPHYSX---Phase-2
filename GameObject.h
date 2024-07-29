#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "tiny_obj_loader.h"

#include "P6/PhysicsParticle.h"
#include "Randomization/RandomGen.h"
#include "Shader.h"
#include <iostream>
#include <fstream>
#include <sstream>


class GameObject
{
public:
	GLuint VAO;
	GLuint VBO;

	GLuint shaderProgram;

	glm::vec4 color;

	float scale;
	tinyobj::attrib_t attributes;
	std::vector<GLuint> mesh_indices;
	std::vector<GLfloat> fullVertexData;

	glm::mat4 IdentityMatrix;
protected:

	float x;
	float y;
	float z;

public:
	physics::MyVector Position;

public:
	GameObject();

	GameObject(std::string Mesh_Path, std::string Vert_Path, std::string Frag_Path);
	~GameObject();

	void Draw(glm::mat4 identity_matrix, glm::mat4 projection_matrix, glm::mat4 view_matrix, float scale);

	void LoadMesh(std::string Mesh_Path);
	void LoadVertices();

	inline GLuint GetVAO() { return VAO; }
	inline GLuint GetVBO() { return VBO; }
	inline GLuint GetShaderProgram() { return shaderProgram; }
	inline std::vector<GLuint> GetMeshIndices() { return mesh_indices; }
	inline std::vector<GLfloat> GetFullVertexData() { return fullVertexData; }

};