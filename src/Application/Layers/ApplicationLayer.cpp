#include "ApplicationLayer.h"

ApplicationLayer::ApplicationLayer(Application* _app)
	: Layer(_app, 0)
{
    std::cout << "Appliation Layer Created" << std::endl;
    app->push_layer(new MenuLayer(app, 1));
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
