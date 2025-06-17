#include "enemy_spawner.h"

constexpr float enemy_spawn_rate = 1.75f;

namespace bts
{

    EnemySpawner::EnemySpawner(const std::string& sound_path, float sfx_volume)
        : Spawner([&]() { return CreateEnemySpawnPosition(); }, enemy_spawn_rate, sound_path, sfx_volume) { }

    Vector2 EnemySpawner::CreateEnemySpawnPosition() {
        int spawn_offset = static_cast<int>(SPAWN_PADDING);
        float random_x_position = static_cast<float>(GetRandomValue(spawn_offset, WIDTH - spawn_offset));
        return { random_x_position, -SPAWN_PADDING };
    }
}