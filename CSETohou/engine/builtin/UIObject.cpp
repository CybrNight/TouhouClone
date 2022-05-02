#include "UIObject.h"

namespace UI {
    UIObject::UIObject(int x, int y, int width, int height)
    {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;

        boundsRect = { x, y, width, height };
    }

    UIObject::~UIObject()
    {
    }
}