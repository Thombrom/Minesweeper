#include "ApplicationLayer.h"

ApplicationLayer::ApplicationLayer(Application* _app)
	: Layer(_app, 0)
{
	std::cout << "Created Application Layer" << std::endl;
	font.load("resources/fonts/arial.ttf");

	Shader shader;

	shader.set_vertex_shader("resources/shaders/vertex_shader.vs");
	shader.set_fragment_shader("resources/shaders/fragment_shader.fs");
	shader.compile();
	ShaderLibrary::Load(shader, ShaderType::ShapeType);

	float vert[12] = {
		+0.5f, +0.5f, 0.0f,
		+0.5f, -0.5f, 0.0f,
		-0.5f, -0.5f, 0.0f,
		-0.5f, +0.5f, 0.0f,
	};
	unsigned int indices[6] = {
		0, 1, 2, 0, 2, 3
	};

	shape.load_prop(ShapeProperty{
		vert, sizeof(vert) / sizeof(float), indices, sizeof(indices) / sizeof(unsigned int)
	});
	shape.set_color(glm::vec3(0.5f, 0.7f, 0.1f));
}

void ApplicationLayer::on_event(Event& _event)
{
	EventDispatcher dispatcher(_event);
	dispatcher.execute<WindowResizeEvent>(BIND_EVENT_FN(ApplicationLayer::handle_resize));
	dispatcher.execute<MouseMovedEvent>([this](MouseMovedEvent& _event)->bool {
		float x = _event.get_x();
		float y = _event.get_y();

		if ((x > 1280 / 4 && x < 3 * 1280 / 4) && (y > 720 / 4 && y < 3 * 720 / 4)) {
			shape.set_color(glm::vec3(0.2f, 0.2f, 0.8f));
			return true;
		}
		else
		{
			shape.set_color(glm::vec3(0.5f, 0.7f, 0.1f));
			return false;
		}
	});
}

void ApplicationLayer::on_update()
{
	shape.draw();
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