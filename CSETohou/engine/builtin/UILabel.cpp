#include "UILabel.h"
#include <iostream>

namespace UI {
    void UILabel::Render(SDL_Renderer* renderer){
        SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_RenderCopy(renderer, textTexture, NULL, &boundsRect);

        if (font == NULL) {
            std::cout << "NO FONT\n";
        }
    }

    void UILabel::Start()
    {
    }

    UILabel::UILabel(int x, int y, int width, int height, std::string text) : UIObject(x, y, width, height), Object(Tag::ObjectGeneric)
    {
        this->text = text;

        font = TTF_OpenFont("resource/font/font.ttf", 24);
        SDL_Color color = { 255, 255, 255 };
        surface = TTF_RenderText_Solid(font, text.c_str(), color);
    }

    void UILabel::Tick() {

    }
}