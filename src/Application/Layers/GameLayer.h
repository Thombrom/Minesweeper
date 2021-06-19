#pragma once

#include <iostream>
#include <functional>
#include <gtc/matrix_transform.hpp>

#include "Application/Application.h"
#include "Application/Layer.h"

#include "Render/Drawable/Text.h"
//#include "Render/Drawable/Button.h"
#include "Render/Drawable/BorderRect.h"

#include "Game/Minesweeper.h"

class GameLayer : public Layer
{
public:
	GameLayer(Application* _app, uint32_t _position);
	~GameLayer();

	void on_update() override;
	void on_event(Event& _event) override;

	void on_push() override;
	void on_pop() override;

private:
	struct TextButton {
		BorderRect* rect;
		Text*		text;
	};
	
	// Graphics
	TextButton back_button;
	BorderRect* game_frame;

	// Game
	MineSweeper game;
};

