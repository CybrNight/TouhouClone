#pragma once
#include <string>
#include "UIObject.h"
#include <SDL_ttf.h>

namespace UI {
    class UILabel : public virtual UIObject
    {
    protected:
        std::string text;
        TTF_Font* font;
        SDL_Surface* surface;

    public:
        UILabel(int x, int y, int width, int height, std::string text);
        ~UILabel(){}
    
        void Tick();
        void Render(SDL_Renderer* renderer);
        void Start();
    };
}
