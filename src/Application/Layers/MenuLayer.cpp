#include "MenuLayer.h"

MenuLayer::MenuLayer(Application* _app, uint32_t _position)
    : Layer(_app, _position) {
    std::cout << "Menu Layer Created" << std::endl;
}

MenuLayer::~MenuLayer()
{
    std::cout << "Menu Layer destroyed" << std::endl;
}

void MenuLayer::on_push()
{
    std::cout << "Menu Layer Pushed" << std::endl;
}

void MenuLayer::on_pop()
{
    std::cout << "Menu Layer Popped" << std::endl;
}

void MenuLayer::on_update()
{

}

void MenuLayer::on_event(Event& _event)
{
    std::cout << "Menu Layer Recieved Event" << std::endl;
}




