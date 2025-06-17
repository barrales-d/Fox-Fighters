#include "bullet_spawner.h"

namespace bts
{
    BulletSpawner::BulletSpawner(float spawn_interval, const std::string& sound_path, float sound_volume)
        : Spawner([]() { return Vector2Zero(); }, spawn_interval, sound_path, sound_volume) {
    }
}