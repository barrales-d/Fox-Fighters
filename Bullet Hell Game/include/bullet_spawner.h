#pragma once
#ifndef __BULLET_SPAWNER_H__
#define __BULLET_SPAWNER_H__

#include <string>

#include "bullet.h"
#include "spawner.h"

namespace bts
{
    class BulletSpawner : public Spawner<Bullet> {
    public:
        BulletSpawner(const std::string& file_path, float spawn_interval, const std::string& sound_path = std::string(), float sound_volume = 1.0f);

        virtual void Draw() const override;
        virtual void UnLoad() override;

    private:
        Texture2D texture;
    };
}

#endif // !__BULLET_SPAWNER_H__
