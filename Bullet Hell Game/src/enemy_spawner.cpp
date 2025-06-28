#include "enemy_spawner.h"

static constexpr float enemy_spawn_rate = 1.75f;
static constexpr Vector2 default_velocity = { 300, 500 };

namespace bts
{

    EnemySpawner::EnemySpawner(const std::string& sound_path, float sfx_volume)
        : Spawner([&]() { return CreateEnemySpawnSettings(); }, enemy_spawn_rate, sound_path, sfx_volume) {
    }

    SpawnSettings EnemySpawner::CreateEnemySpawnSettings() {
        int spawn_offset = static_cast<int>(SPAWN_PADDING);
        float random_x_position = static_cast<float>(GetRandomValue(spawn_offset, WIDTH - spawn_offset));
        return SpawnSettings({ random_x_position, -SPAWN_PADDING }, default_velocity);
    }
}