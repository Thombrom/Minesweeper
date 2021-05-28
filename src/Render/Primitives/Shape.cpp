#include "Shape.h"

Shape::Shape()
{
	// Nothing
}

Shape::Shape(ShapeProperty& _prop)
{
	load_prop(_prop);
}

Shape::~Shape()
{
	delete prop.indices;
	delete prop.vertices;

	glDeleteBuffers(1, &VBO);
	glDeleteBuffers(1, &EBO);
	glDeleteVertexArrays(1, &VAO);
}

void Shape::load_prop(const ShapeProperty& _prop)
{
	if (VBO) glDeleteBuffers(1, &VBO);
	if (EBO) glDeleteBuffers(1, &EBO);
	if (VAO) glDeleteVertexArrays(1, &VAO);

	prop.indices_size = _prop.indices_size;
	prop.vertices_size = _prop.vertices_size;

	prop.indices = new (unsigned int)(_prop.indices_size);
	prop.vertices = new (float)(_prop.vertices_size);

	memcpy(prop.indices, _prop.indices, sizeof(unsigned int) * prop.indices_size);
	memcpy(prop.vertices, _prop.vertices, sizeof(float) * prop.vertices_size);
	setup_gl();
}

void Shape::setup_gl()
{
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glGenVertexArrays(1, &VAO);
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * prop.vertices_size, prop.vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * prop.indices_size, prop.indices, GL_STATIC_DRAW);
	glBindVertexArray(0);

	shader = ShaderLibrary::Retrieve(ShaderType::ShapeType);
}

void Shape::draw()
{
	glBindVertexArray(VAO);
	shader.use();
	shader.set_vec3("color", color.x, color.y, color.z);
	glDrawElements(GL_TRIANGLES, prop.vertices_size, GL_UNSIGNED_INT, 0);
}
