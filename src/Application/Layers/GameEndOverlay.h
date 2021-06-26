#pragma once
#include <string>
#include <glm.hpp>

#include "Application/Application.h"
#include "Application/Layer.h"

#include "Render/Drawable/Text.h"
#include "Render/Drawable/BorderRect.h"
#include "Render/Drawable/TextButton.h"

class GameEndOverlay : public Layer
{
public:
	GameEndOverlay(Application* _app, uint32_t _position, uint32_t _state);
	~GameEndOverlay();
    
	void on_update() override;
	void on_event(Event& _event) override;

	void on_push() override;
	void on_pop() override;

private:
    TextButton* menu_button;
    TextButton* redo_button;

    Text*       message;
    BorderRect* border;
};
