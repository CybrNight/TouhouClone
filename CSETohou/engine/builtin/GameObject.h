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

    void clamp_x();
    void clamp_y();
    void clamp_position(char xy=' ');

public:

    virtual void init();
    virtual void render(SDL_Renderer* renderer);
    virtual void start() = 0;
    virtual void tick() = 0;
    virtual void tick_second(){}
    virtual void collision(GameObject* other) {}

    /** Move with GameObject speed and direction
     * @brief move
     */
    virtual void move();
    void destroy_outside();

    /** Move with custom speed and direction
     * @brief move
     * @param speed
     * @param direction
     */
    void move(float speed, float direction);

    /**
     * @brief get_bounds
     * @return QRectF with GameObject dimensions
     */
    virtual SDL_FRect get_bounds() const;
    virtual void draw_bounds(SDL_Renderer* renderer);

    GameObject(float x, float y, Tag id, float width = 0, float height = 0);
    virtual ~GameObject() = 0;

    inline float get_x() const {return x;}
    inline float get_y() const { return y; }
    inline float get_center_x() const{return get_x() + width / 2; }
    inline float get_center_y() const {return get_y() + height / 2; }
    inline float get_speed() const {return speed;}
    inline float get_direction() const {return direction;}
    inline float get_width() const {return width;}
    inline float get_height() const {return height;}
    inline float get_rotation() const {return rotation; }
    inline std::string get_sprite_path() {return sprName;}
    
    void load_sprite(SDL_Texture* sprite);
    inline void set_x(float x) {this->x = x;}
    inline void set_y(float y) { this->y = y;}
    inline void set_speed(float speed) {this->speed = speed;}
    inline void set_direction(float direction) {this->direction = direction;}
    inline void set_width(float width) {this->width = width;}
    inline void set_height(float height) {this->height = height;}
    inline void set_rotation(float rotation){ this->rotation = rotation; };
    bool operator==(GameObject* other);
};

inline void destroy(GameObject* obj) { obj->destroy(); }
//inline void instantiate(GameObject* obj) { Handler::instance->instantiate(obj); }