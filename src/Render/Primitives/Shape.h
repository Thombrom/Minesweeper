#pragma once
#include "../Primitive.h"

#include <cstring>

struct ShapeProperty
{
	float* vertices;
	uint32_t vertices_size;

	unsigned int* indices;
	uint32_t indices_size;
};

class Shape : public Primitive
{
public:
	Shape();
	Shape(ShapeProperty& _prop);
	~Shape();

	void load_prop(const ShapeProperty& _prop);
	void draw() override;

	void set_color(const glm::vec3& _color) { color = _color; };
	void set_color(glm::vec3& _color) { color = _color; };

private:
	void setup_gl();

private:
	ShapeProperty prop;
	glm::vec3 color;

	unsigned int VAO, VBO, EBO;
	Shader shader;
};
