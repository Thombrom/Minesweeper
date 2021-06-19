#pragma once

#include <map>
#include "Shader.h"

enum class ShaderType
{
	TEXT, BORDER_RECT
};

class ShaderLibrary
{
public:
	ShaderLibrary() = default;
	
	static void Load(Shader& _shader, ShaderType _key) { 
		library.insert(std::pair<ShaderType, Shader>(_key, _shader)); 
	};

	static Shader Retrieve(ShaderType _key) {
		return library[_key]; 
	}

    static void Destroy() {
        for (auto [key, value] : library)
            value.destroy();
    }

private:
	static std::map<ShaderType, Shader> library;

public:
    static void Initialize()
    {
        Shader shader;

        // Initialize font shader
        shader.set_vertex_shader("resources/shaders/text.vs");
        shader.set_fragment_shader("resources/shaders/text.fs");
        shader.compile();
        ShaderLibrary::Load(shader, ShaderType::TEXT);

        // Initialize button shader
        shader.set_vertex_shader("resources/shaders/border_rect.vs");
        shader.set_fragment_shader("resources/shaders/border_rect.fs");
        shader.compile();
        ShaderLibrary::Load(shader, ShaderType::BORDER_RECT);
    }
};

