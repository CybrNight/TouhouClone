#pragma once

//TODO REPLACE WITH SDL EQUIVALENTS

//#include <QImage>
#include "tag.h"
#include "object.h"
//#include <QPainter>
//#include <QKeyEvent>
//#include <QRectF>
//#include <typeinfo>
//#include "game.h"
#include "Defs.h"
#include <memory>
#include <string>
#include <map>
#include <SDL.h>
#include <SDL_image.h>
#include <iterator>

/**
 * @brief Parent GameObject type. All GameObject types inherit from this
 * @include gameobject.h
 */
class GameObject: public virtual Object
{
    Tag tag;

protected:
    float x, y;
    SDL_Texture* sprite;
    SDL_Rect drawRect;
    std::string sprName;

    float width, height;
    float rotation;
    float speed;
    float direction;
    unsigned long long uuid;
    bool destroyed;

    void ClampX();
    void ClampY();
    void ClampPosition(char xy=' ');

public:

    virtual void Init();
    virtual void Render(SDL_Renderer* renderer);
    virtual void Start() = 0;
    virtual void Tick() = 0;
    virtual void TickSecond(){}
    virtual void Collision(GameObject* other) {}

    /** Move with GameObject speed and direction
     * @brief Move
     */
    virtual void Move();
    virtual void DestroyOutside();

    /** Move with custom speed and direction
     * @brief Move
     * @param speed
     * @param direction
     */
    void Move(float speed, float direction);

    /**
     * @brief GetBounds
     * @return QRectF with GameObject dimensions
     */
    virtual SDL_FRect GetBounds() const;
    virtual void DrawBounds(SDL_Renderer* renderer);

    GameObject(float x, float y, Tag id, float width = 0, float height = 0);
    virtual ~GameObject() = 0;

    inline float GetX() const {return x;}
    inline float GetY() const { return y; }
    inline float GetCenterX() const{return x + width / 2; }
    inline float GetCenterY() const {return y + height / 2; }
    inline float GetSpeed() const {return speed;}
    inline float GetDirection() const {return direction;}
    inline float GetWidth() const {return width;}
    inline float GetHeight() const {return height;}
    inline float GetRotation() const {return rotation; }
    inline std::string GetSpriteName() {return sprName;}
    
    void LoadSprite(SDL_Texture* sprite);
    inline void SetX(float x) {this->x = x;}
    inline void SetY(float y) { this->y = y;}
    inline void SetSpeed(float speed) {this->speed = speed;}
    inline void SetDirection(float direction) {this->direction = direction;}
    inline void SetWidth(float width) {this->width = width;}
    inline void SetHeight(float height) {this->height = height;}
    inline void SetRotation(float rotation){ this->rotation = rotation; };
    bool operator==(GameObject* other);
};

inline void Destroy(GameObject* obj) { obj->Destroy(); }
//inline void instantiate(GameObject* obj) { Handler::instance->instantiate(obj); }