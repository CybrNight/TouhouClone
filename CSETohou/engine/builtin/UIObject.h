#pragma once
#include "Object.h"

class UIObject: public virtual Object
{
    int x, y;
    int width, height;

public:
    UIObject(int x, int y, int width, int height);
    virtual ~UIObject() = 0;
};

