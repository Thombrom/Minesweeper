#include "GameLayer.h"

GameLayer::GameLayer(Application* _app, uint32_t _position)
	: Layer(_app, _position){
	std::cout << "GameLayer Constructed" << std::endl;
}

GameLayer::~GameLayer()
{

}

void GameLayer::on_pop() 
{
	std::cout << "GameLayer Popped" << std::endl;
}

void GameLayer::on_push()
{
	std::cout << "GameLayer Pushed" << std::endl;
}

void GameLayer::on_event(Event& _event)
{
	std::cout << "GameLayer Event Received" << std::endl;
}

void GameLayer::on_update()
{
	
}