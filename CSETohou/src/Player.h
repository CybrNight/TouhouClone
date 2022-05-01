#pragma once

#include "GameObject.h"
#include "IDamagable.h"

class Player : public virtual GameObject, public virtual IDamagable{
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

public:
    //void Damage() override;
    void DrawBounds(SDL_Renderer* painter) override;

    Player(float x, float y, Tag id = Tag::ObjectPlayer);
    ~Player(){}

    SDL_FRect GetBounds() const override;
    inline static Player* GetPlayer() { return instance; }
    inline const SDL_Color GetBulletColor() const {return bulletColor;}

    //Called when other Collider overlaps
    void Collision(GameObject* other) override;
    void Damage() override;
};