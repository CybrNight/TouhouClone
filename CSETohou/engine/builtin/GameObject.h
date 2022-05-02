#pragma once

//TODO REPLACE WITH SDL EQUIVALENTS

//#include <QImage>
#include "Tag.h"
#include "Object.h"
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
    std::shared_ptr<SDL_Texture> sprite;
    SDL_Rect drawRect;
    std::string sprName;

    float width, height;
    float rotation;
    float speed;
    float direction;
    unsigned long long uuid;
    bool destroyed;
    
    /// <summary>
    /// Clamp GameObject x position to bounds of play area (if called from GameObject Tick()).
    /// Calls ClampPosition with xy = 'x'
    /// </summary>
    void ClampX();

    /// <summary>
    /// Clamp GameObject x position to bounds of play area (if called from GameObject Tick()).
    /// Calls ClampPosition with xy = 'y'
    /// </summary>
    void ClampY();

    /// <summary>
    /// Clamps x and y position.
    /// Default xy value (' ') clamps both x and y
    /// </summary>
    /// <param name="xy"></param>
    void ClampPosition(char xy=' ');

public:

    //Initializes values that all GameObjects need (not implemented by children)
    virtual void Init();

    //Draws SDL_Texture at object positon
    virtual void Render(SDL_Renderer* renderer);

    //Called when GameObject is first created in the game
    virtual void Start() = 0;

    //Called every frame
    virtual void Tick() = 0;

    //REMOVE ME I AM USELESS
    virtual void TickSecond(){}

    /// <summary>
    /// Handles collison checks sent from Handler
    /// </summary>
    /// <param name="other"></param>
    virtual void Collision(GameObject* other) {}

    /// <summary>
    /// Moves GameObject based on direction and speed (default behavior)
    /// </summary>
    virtual void Move();

    /// <summary>
    /// Checks if GameObject is outside play area. Destroys the object if so
    /// </summary>
    void DestroyOutside();

    /// <summary>
    /// Moves with set speed and direction separate from GameObject's local values
    /// </summary>
    /// <param name="speed"></param>
    /// <param name="direction"></param>
    void Move(float speed, float direction);

    /// <summary>
    /// Returns the bounds of a given GameObject as an SDL_FRect based on GameObject width, height
    /// </summary>
    /// <returns></returns>
    virtual SDL_FRect GetBounds() const;


    /// <summary>
    /// Draws a circle render of GameObject hitbox based on width
    /// </summary>
    /// <param name="renderer"></param>
    virtual void DrawBounds(SDL_Renderer* renderer);

    GameObject(float x, float y, Tag tag, float width = 0, float height = 0);
    virtual ~GameObject() = 0;

    GameObject* FindWithTag(Tag tag);

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
    
    void LoadSprite(std::shared_ptr<SDL_Texture> sprite);
    inline void SetX(float x) {this->x = x;}
    inline void SetY(float y) { this->y = y;}
    inline void SetSpeed(float speed) {this->speed = speed;}
    inline void SetDirection(float direction) {this->direction = direction;}
    inline void SetWidth(float width) {this->width = width;}
    inline void SetHeight(float height) {this->height = height;}
    inline void SetRotation(float rotation){ this->rotation = rotation; };
    bool operator==(GameObject* other);
};