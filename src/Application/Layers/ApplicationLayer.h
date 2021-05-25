#pragma once

#include <iostream>
#include <functional>

#include "Application/Layer.h"
#include "Render/Font.h"

class ApplicationLayer : public Layer
{
public:
	ApplicationLayer(Application* _app);

	void on_update() override;
	void on_event(Event& _event) override;

	void on_push() override;
	void on_pop() override;

private:
	bool handle_resize(WindowResizeEvent& _event); 

	unsigned int VBO, EBO, VAO;
	float vertices[3 * 4];
	unsigned int indices[6];

private:
	Font font;
	Shader shader;

};