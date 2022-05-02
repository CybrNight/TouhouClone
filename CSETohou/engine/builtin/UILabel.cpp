#include "UILabel.h"
#include "ObjectHandler.h"
#include <iostream>

namespace UI {
    void UILabel::Render(SDL_Renderer* renderer){
        SDL_QueryTexture(textTexture, NULL, NULL, &width, &height);
        boundsRect = { x, y, width, height };

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

        font = TTF_OpenFont("resource/font/font2.ttf", 26);
    }

    void UILabel::Tick() {

    }

    void UILabel::SetText(std::string text) {
        SDL_Color color = { 255, 255, 255 };
        SDL_DestroyTexture(textTexture);
        SDL_FreeSurface(surface);
        surface = TTF_RenderText_Blended(font, text.c_str(), color);
        textTexture = SDL_CreateTextureFromSurface(EngineCore::ObjectHandler::GetInstance()->GetRenderer(), surface);
    }
}