#pragma once
#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include <string>
#include <raylib.h>

#include "asset_manager.h"
#include "game_object.h"

namespace bts
{
    class Background : public GameObject {
    public:
        Background();

        virtual void Draw() const override;
        virtual void Update(float dt) override;
        virtual void UnLoad() override {}


    private:
    };
}

#endif // !__BACKGROUND_H__
