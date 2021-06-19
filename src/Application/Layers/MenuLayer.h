#pragma once

#include <iostream>
#include <functional>
#include <gtc/matrix_transform.hpp>

#include "Application/Application.h"
#include "Application/Layer.h"

#include "Render/Drawable/Text.h"
#include "Render/Drawable/BorderRect.h"
//#include "Render/Drawable/Button.h"

class MenuLayer : public Layer
{
public:
	MenuLayer(Application* _app, uint32_t _position);
    ~MenuLayer();

	void on_update() override;
	void on_event(Event& _event) override;

	void on_push() override;
	void on_pop() override;

private:
	struct TextButton {
		BorderRect* rect;
		Text*		text;
	};

	TextButton			button_panel[3];
	InternalEventType	button_click_event[3];
};
