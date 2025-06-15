#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <raylib.h>
#include <raymath.h>

#include "constants.h"
#include "game_object.h"

namespace bts
{
    class Enemy : public GameObject {
    public:
        Enemy() : GameObject() {}
        Enemy(Vector2 start_position);

        virtual void Draw() const override;
        virtual void Update(float dt) override;
        virtual void UnLoad() override {}
    private:
    };
}

#endif // !__ENEMY_H__
