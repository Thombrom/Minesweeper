#pragma once

#include <iostream>
#include <functional>

#include "Application/Layer.h"

#include "Render/Shader/ShaderLibrary.h"
#include "Render/Font.h"

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
	bool handle_resize(WindowResizeEvent& _event); 

private:
	Font font;
};
