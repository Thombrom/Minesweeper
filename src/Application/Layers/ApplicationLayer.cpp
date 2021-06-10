#include "ApplicationLayer.h"

ApplicationLayer::ApplicationLayer(Application* _app)
	: Layer(_app, 0)
{
	std::cout << "Created Application Layer" << std::endl;
    text = Text::Create("This is a test!", FontType::ARIAL);
    text->set_center(glm::vec3(1280.0f / 2, 720.0f / 2, 0));

    button = Button::Create(glm::vec2(200.0f, 200.0f), glm::vec2(100.0f, 100.0f), "Test", 2);
    button->set_border_color(glm::vec3(0.0f, 1.0f, 0.0f));
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
        return true;
	});
}

void ApplicationLayer::on_update()
{
    text->draw(glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f));
    button->draw(glm::ortho(0.0f, 1280.0f, 0.0f, 720.0f));
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
