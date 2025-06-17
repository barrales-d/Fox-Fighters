#pragma once
#ifndef __BULLET_H__
#define __BULLET_H__

#include <raylib.h>
#include <raymath.h>

#include "constants.h"
#include "asset_manager.h"
#include "game_object.h"

namespace bts
{
    class Bullet : public GameObject {
    public:
        Bullet() : GameObject() {}
        Bullet(Vector2 start_position);

        virtual void Draw() const override;
        virtual void Update(float dt) override;
        virtual void UnLoad() override {}

    };
}

#endif // !__BULLET_H__
