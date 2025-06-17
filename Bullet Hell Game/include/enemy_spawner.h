#pragma once
#ifndef __ENEMY_SPAWNER_H__
#define __ENEMY_SPAWNER_H__

#include <string>

#include "enemy.h"
#include "spawner.h"

namespace bts
{
    class EnemySpawner : public Spawner<Enemy> {
    public:
        EnemySpawner(const std::string& sound_path = std::string(), float sfx_volume = 1.0f);
    private:
        Vector2 CreateEnemySpawnPosition();
    };
}

#endif // !__ENEMY_SPAWNER_H__
