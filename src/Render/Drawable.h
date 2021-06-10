#pragma once
#include <glm.hpp>

/*
 * Interface class for all drawable objects
 */

class Drawable
{
public:
    virtual void draw(const glm::mat4& _view) = 0;
};
