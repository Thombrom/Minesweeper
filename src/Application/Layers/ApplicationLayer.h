#pragma once

#include <iostream>
#include <functional>
#include <gtc/matrix_transform.hpp>

#include "Application/Application.h"
#include "Application/Layer.h"

#include "Render/Drawable/Text.h"

struct ApplicationData
{
	uint32_t game_size_x;
	uint32_t game_size_y;
	uint32_t game_mine_count;
};

class ApplicationLayer : public Layer
{
public:
	ApplicationLayer(Application* _app);
    ~ApplicationLayer();

	void on_update() override;
	void on_event(Event& _event) override;

	void on_push() override;
	void on_pop() override;

private:
	// Internal Event Functions
	void change_start_menu();
	void change_start_game();
	void change_start_settings();

private:
	bool handle_resize(WindowResizeEvent& _event);
};
