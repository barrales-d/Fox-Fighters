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
        EnemySpawner(const std::string& file_path, const std::string& sound_path = std::string());
        virtual void Draw() const override;

        virtual void UnLoad() override;
    private:
        Vector2 CreateEnemySpawnPosition();

        Texture2D texture;
    };
}

#endif // !__ENEMY_SPAWNER_H__
