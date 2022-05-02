#pragma once
#include "Object.h"
#include <SDL.h>

namespace UI {
    class UIObject : public virtual Object
    {
    protected:
        int x, y;
        int width, height;
        SDL_Rect boundsRect;

    public:
        UIObject(int x, int y, int width, int height);
        virtual ~UIObject() = 0;
        
        virtual void Render(SDL_Renderer* renderer) = 0;
    };
}
