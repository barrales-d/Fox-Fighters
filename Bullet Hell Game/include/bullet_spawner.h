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
        BulletSpawner(SpawnFunc spawn_settings_func, float spawn_interval, const std::string& sound_path = std::string(), float sound_volume = 1.0f);
    private:
    };
}

#endif // !__BULLET_SPAWNER_H__
