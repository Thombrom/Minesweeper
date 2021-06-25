#include "ApplicationLayer.h"

ApplicationLayer::ApplicationLayer(Application* _app)
	: Layer(_app, 0)
{
	// Set application data
	ApplicationData* appdata = new ApplicationData{
		10, 10, 10
	};
	app->set_data(appdata);

    // Initialize menu
	app->event_callback(new InternalEvent(InternalEventType::CHANGE_START_GAME, 0));
}

ApplicationLayer::~ApplicationLayer()
{
	std::cout << "ApplicationLayer Destroyed" << std::endl;
}

void ApplicationLayer::on_event(Event& _event)
{
	EventDispatcher dispatcher(_event);
	dispatcher.execute<WindowResizeEvent>(BIND_EVENT_FN(ApplicationLayer::handle_resize));
	dispatcher.execute<MouseMovedEvent>([this](MouseMovedEvent& _event)->bool {
        return true;
	});

	dispatcher.execute<InternalEvent>([this](InternalEvent& _event)->bool {
		std::cout << "Received Internal Event in ApplicationLayer" << std::endl;

		if (_event.get_type() == InternalEventType::EXIT_APP) {
			app->shutdown();
			return true;
		}

		if (_event.get_type() == InternalEventType::CHANGE_START_MENU) {
			change_start_menu();
			return true;
		}

		if (_event.get_type() == InternalEventType::CHANGE_START_GAME) {
			change_start_game();
			return true;
		}
		
		return false;
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


/*
	------------- INTERNAL EVENT FUNCTIONS ------------
*/
void ApplicationLayer::change_start_menu()
{
	app->pop_after(1);						    // Purge all layers above 1
	app->push_layer(new MenuLayer(app, 1));		// Change to the menu layer
}

void ApplicationLayer::change_start_game()
{
	app->pop_after(1);						    // Purge all layers above 1
	app->push_layer(new GameLayer(app, 1));		// Change to the menu layer
}

/*void ApplicationLayer::change_start_settings()
{
	app->pop_layer_all(1);						// Purge all layers above 1
	app->push_layer(new MenuLayer(app, 1));		// Change to the menu layer
}*/


