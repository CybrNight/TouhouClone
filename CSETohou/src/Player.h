#pragma once

#include "GameObject.h"
#include "IControllable.h"
#include "IDamagable.h"

class Player : public virtual GameObject, public virtual IControllable, public virtual IDamagable{
    float speed = 0;
    bool keysDown[4];
    float velX = 0, velY = 0;
    float fireRate = 15;
    bool shoot = false;
    float shootTimer = 0;

    SDL_Color bulletColor{255, 0, 255};

    static Player* instance;

protected:
    void Start() override;
    void Tick() override;

    void KeyPress(SDL_Keycode key) override;
    void KeyRelease(SDL_Keycode key) override;
    void KeyHeld(SDL_Keycode key) override;

public:
    //void Damage() override;
    void DrawBounds(SDL_Renderer* painter) override;

    Player(float x, float y, Tag id = Tag::ObjectPlayer);
    ~Player(){}

    SDL_FRect GetBounds() const override;
    inline static Player* get_player() { return instance; }
    inline const SDL_Color get_bullet_color() const {return bulletColor;}

    //Called when other Collider overlaps
    void Collision(GameObject* other) override;
    void Damage() override;
};