#pragma once

#include <map>
#include "Shader.h"

enum class ShaderType
{
	Shape, Font
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
};
