#pragma once
#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

#include <string>
#include <raylib.h>

#include "game_object.h"

namespace bts
{
    class Background : public GameObject {
    public:
        Background(const std::string& file_path);

        virtual void Draw() const override;
        virtual void Update(float dt) override;
        virtual void UnLoad() override;


    private:
        Texture2D texture;
    };
}

#endif // !__BACKGROUND_H__
