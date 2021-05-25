#include "ApplicationLayer.h"

ApplicationLayer::ApplicationLayer(Application* _app)
	: Layer(_app, 0)
{
	std::cout << "Created Application Layer" << std::endl;
	font.load("resources/fonts/arial.ttf");

	shader.set_vertex_shader("resources/shaders/vertex_shader.vs");
	shader.set_fragment_shader("resources/shaders/fragment_shader.fs");
	shader.compile();


	float vert[] = {
		0.5f, 0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f
	};
	memcpy(vertices, vert, sizeof(float) * 12);

	unsigned int ind[] = {
		0, 1, 2, 0, 2, 3
	};
	memcpy(indices, ind, sizeof(unsigned int) * 6);

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &EBO);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

void ApplicationLayer::on_event(Event& _event)
{
	EventDispatcher dispatcher(_event);
	dispatcher.execute<WindowResizeEvent>(BIND_EVENT_FN(ApplicationLayer::handle_resize));
}

void ApplicationLayer::on_update()
{
	glBindVertexArray(VAO);
	shader.use();
	shader.set_vec3("color", 0.3f, 1.0f, 0.2f);
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

	font.render_text("This is a test", 25.0f, 25.0f, 1.0f, glm::vec3(0.5f, 0.8f, 0.2f));
}

void ApplicationLayer::on_push()
{
	std::cout << "Layer Pushed" << std::endl;
}

void ApplicationLayer::on_pop()
{
	std::cout << "Layer Popped" << std::endl;
}

bool ApplicationLayer::handle_resize(WindowResizeEvent& _event)
{
	// Update viewport to correct settings
	glViewport(0, 0, _event.get_width(), _event.get_height());
	return true;
}