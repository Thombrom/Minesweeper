#pragma once

#include <stdio.h>

#include "Shader/Shader.h"
#include "Shader/ShaderLibrary.h"

/*
	An interface for primitive shapes
	that we might want to render
*/

class Primitive
{
public:
	Primitive() { std::cout << "Primitiv Created" << std::endl; };
	~Primitive() { std::cout << "Primitive Destroyed" << std::endl; };

	virtual void draw() = 0;
};

#include "Primitives/Shape.h"