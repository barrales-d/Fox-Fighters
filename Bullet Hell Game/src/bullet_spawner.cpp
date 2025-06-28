#include "bullet_spawner.h"

namespace bts
{
    BulletSpawner::BulletSpawner(SpawnFunc spawn_settings_func, float spawn_interval, const std::string& sound_path, float sound_volume)
        : Spawner(spawn_settings_func, spawn_interval, sound_path, sound_volume) {
    }
}