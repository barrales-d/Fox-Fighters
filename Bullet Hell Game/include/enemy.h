#pragma once
#ifndef __ENEMY_H__
#define __ENEMY_H__

#include <raylib.h>
#include <raymath.h>

#include "constants.h"
#include "asset_manager.h"
#include "game_object.h"
#include "event_timer.h"

namespace bts
{
    class Enemy : public GameObject {
    public:
        Enemy() : GameObject(), switch_dir(0.0f) {}
        Enemy(Vector2 start_position);

        virtual void Draw() const override;
        virtual void Update(float dt) override;
        virtual void UnLoad() override {}
    private:
        Timer switch_dir;
        Texture2D current_texture;
    };
}

#endif // !__ENEMY_H__
