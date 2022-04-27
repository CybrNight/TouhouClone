#include "GameObject.h"
#include "ObjectHandler.h"
#include <cmath>
#include <iostream>

void GameObject::Move(float speed, float direction)
{
    x += speed * std::cos(direction * M_PI / 180);
    y -= speed * std::sin(direction * M_PI / 180);
}

/*QRectF GameObject::GetBounds() const
{
    return QRectF(GetX(), GetY(), width, height);
}*/

void GameObject::Move()
{
    Move(this->speed, this->direction);
}

void GameObject::Render(SDL_Renderer* renderer) {

    if (sprite == NULL) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRectF(renderer, new SDL_FRect{ GetX(), GetY(), width, height });
    }
    else {
        SDL_RenderCopyExF(renderer, sprite, new SDL_Rect{0, 0, drawRect.w, drawRect.h}, new SDL_FRect{GetX(), GetY(), width, height}, rotation, NULL, SDL_FLIP_NONE);
    }
}

SDL_FRect GameObject::GetBounds() const {
    return SDL_FRect{x, y, width, height };
}

void GameObject::DrawBounds(SDL_Renderer* renderer)
{
    float radius = width / 2;
    float border = (radius*2) + 2;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    for (int w = 0; w <= border; w++)
    {
        for (int h = 0; h <= border; h++)
        {
            int dx = radius - w; // horizontal offset
            int dy = radius - h; // vertical offset
            float size = (dx * dx + dy * dy);
            if (size >= ((radius) * (radius)) && size <= ((border/2) * (border/2))) {
                SDL_RenderDrawPoint(renderer, GetCenterX() + dx, GetCenterY() + dy);
            }
        }
    }
}

void GameObject::ClampPosition(char xy)
{
    if (xy == 'x') {
        x = Clamp(x, MIN_X, MAX_X - width);
    }
    else if (xy == 'y') {
        y = Clamp(y, MIN_Y, MAX_Y - height);
    }
    else if (xy == ' ') {
        x = Clamp(x, MIN_X, MAX_X - width);
        y = Clamp(y, MIN_Y, MAX_Y - height);
    }
}

void GameObject::Init()
{
    rotation = 0;
    Start();
}

void GameObject::ClampX() {
    ClampPosition('x');
}

void GameObject::ClampY() {
    ClampPosition('y');
}

void GameObject::DestroyOutside()
{
    if (GetX() < MIN_X - width / 2 || GetY() < MIN_Y - height / 2 || GetX() > MAX_X + width / 2 || GetY() > MAX_Y + height / 2) {
        Destroy();
    }
}

GameObject::GameObject(float x, float y, Tag tag, float width, float height): Object(tag)
{
    destroyed = false;
    this->SetX(x);
    this->SetY(y);
    this->SetWidth(width);
    this->SetHeight(height);
    sprName = "none";
}

GameObject::~GameObject() {}


void GameObject::LoadSprite(SDL_Texture* sprite)
{
    this->sprite = sprite;
    int w, h;
    SDL_QueryTexture(sprite, NULL, NULL, &w, &h);
    drawRect = {0, 0, w, h};
    width = w;
    height = h;
}

bool GameObject::operator==(GameObject* other)
{
    if (this->GetUUID() == other->GetUUID()) {
        return true;
    }
    return false;
}