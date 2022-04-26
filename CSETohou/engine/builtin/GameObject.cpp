#include "GameObject.h"
#include "ObjectHandler.h"
#include <cmath>
#include <iostream>

void GameObject::move(float speed, float direction)
{
    x += speed * std::cos(direction * M_PI / 180);
    y -= speed * std::sin(direction * M_PI / 180);
}

/*QRectF GameObject::get_bounds() const
{
    return QRectF(get_x(), get_y(), width, height);
}*/

void GameObject::move()
{
    move(this->speed, this->direction);
}

void GameObject::render(SDL_Renderer* renderer) {

    if (sprite == NULL) {
        SDL_SetRenderDrawColor(renderer, 255, 0, 255, 255);
        SDL_RenderFillRectF(renderer, new SDL_FRect{ get_x(), get_y(), width, height });
    }
    else {
        SDL_RenderCopyExF(renderer, sprite, new SDL_Rect{0, 0, drawRect.w, drawRect.h}, new SDL_FRect{get_x(), get_y(), width, height}, rotation, NULL, SDL_FLIP_NONE);
    }
}

SDL_FRect GameObject::get_bounds() const {
    return SDL_FRect{x, y, width, height };
}

void GameObject::draw_bounds(SDL_Renderer* renderer)
{
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderDrawRectF(renderer, new SDL_FRect{x, y, width, height});
}

void GameObject::clamp_position(char xy)
{
    if (xy == 'x') {
        x = clamp(x, MIN_X, MAX_X - width);
    }
    else if (xy == 'y') {
        y = clamp(y, MIN_Y, MAX_Y - height);
    }
    else if (xy == ' ') {
        x = clamp(x, MIN_X, MAX_X - width);
        y = clamp(y, MIN_Y, MAX_Y - height);
    }
}

void GameObject::init()
{
    rotation = 0;
    start();
}

void GameObject::clamp_x() {
    clamp_position('x');
}

void GameObject::clamp_y() {
    clamp_position('y');
}

void GameObject::destroy_outside()
{
    if (get_x() < MIN_X - width / 2 || get_y() < MIN_Y - height / 2 || get_x() > MAX_X + width / 2 || get_y() > MAX_Y + height / 2) {
        destroy();
    }
}

GameObject::GameObject(float x, float y, Tag tag, float width, float height): Object(tag)
{
    destroyed = false;
    this->set_x(x);
    this->set_y(y);
    this->set_width(width);
    this->set_height(height);
    sprName = "none";
}

GameObject::~GameObject() {}


void GameObject::load_sprite(SDL_Texture* sprite)
{
    this->sprite = sprite;
    int w, h;
    SDL_QueryTexture(sprite, NULL, NULL, &w, &h);
    drawRect = {0, 0, w, h};
}

bool GameObject::operator==(GameObject* other)
{
    if (this->get_uuid() == other->get_uuid()) {
        return true;
    }
    return false;
}