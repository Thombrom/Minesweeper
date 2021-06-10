#include "ApplicationLayer.h"

ApplicationLayer::ApplicationLayer(Application* _app)
	: Layer(_app, 0)
{
	std::cout << "Created Application Layer" << std::endl;
	font.load("resources/fonts/arial.ttf");
}

ApplicationLayer::~ApplicationLayer()
{
    ShaderLibrary::Destroy();
}

void ApplicationLayer::on_event(Event& _event)
{
	EventDispatcher dispatcher(_event);
	dispatcher.execute<WindowResizeEvent>(BIND_EVENT_FN(ApplicationLayer::handle_resize));
	dispatcher.execute<MouseMovedEvent>([this](MouseMovedEvent& _event)->bool {
		/*float x = _event.get_x();
		float y = _event.get_y();

		if ((x > 1280 / 4 && x < 3 * 1280 / 4) && (y > 720 / 4 && y < 3 * 720 / 4)) {
			shape.set_color(glm::vec3(0.2f, 0.2f, 0.8f));
			return true;
		}
		else
		{
			shape.set_color(glm::vec3(0.5f, 0.7f, 0.1f));
			return false;
		}*/
        return true;
	});
}

void ApplicationLayer::on_update()
{
	//shape.draw();
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
