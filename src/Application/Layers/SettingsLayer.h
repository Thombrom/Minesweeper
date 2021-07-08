#pragma once
#include <string>
#include <glm.hpp>

#include "Application/Application.h"
#include "Application/Layer.h"

#include "Render/Drawable/Text.h"
#include "Render/Drawable/BorderRect.h"
#include "Render/Drawable/TextButton.h"


class SettingsLayer : public Layer
{
public:
	SettingsLayer(Application* _app, uint32_t _position);
    ~SettingsLayer();

	void on_update() override;
	void on_event(Event& _event) override;

	void on_push() override;
	void on_pop() override;

private:
    struct InputType {
        TextButton* button;
        Text*       text;
    };

    InputType input[3];

    TextButton* menu_btn;
    TextButton* play_btn;
    Text*       message;
    BorderRect* border;
};
