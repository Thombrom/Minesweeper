#include "Rectangle.h"

Rectangle::Rectangle()
	: Primitive()
{
	// Empty
}

Rectangle::Rectangle(float _x, float _y, float _w, float _h)
	: Primitive() {
	float vert[4 * 3] = {
		_x + _w / 2, _y + _h / 2, 0.0f,
		_x - _w / 2, _y + _h / 2, 0.0f,
		_x + _w / 2, _y - _h / 2, 0.0f,
		_x - _w / 2, _y - _h / 2, 0.0f,
	};
	memcpy(vertices, vert, sizeof(float) * 12);

	unsigned int indi[6] = {
		0, 1, 2, 1, 2, 3
	};
	memcpy(indices, indi, sizeof(unsigned int) * 6);
	shader = ShaderLibrary::Retrieve(ShaderType::ShapeType);

	std::cout << "Creating Rectangle" << std::endl;

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	glBindVertexArray(0);
}

void Rectangle::draw()
{
	glBindVertexArray(VAO);
	shader.use();
	shader.set_vec3("color", 0.4f, 0.8f, 0.2f);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
}