#pragma once

#include <cstring>

#include "../Primitive.h"

class Rectangle : public Primitive
{
public:
	Rectangle();
	Rectangle(float _x, float _y, float _w, float _h);

	void draw() override;

private:
	unsigned int VAO, VBO, EBO;
	Shader shader;

	float vertices[4 * 3];
	unsigned int indices[6];
};
