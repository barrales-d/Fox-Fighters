#include "enemy_spawner.h"

constexpr float enemy_spawn_rate = 1.75f;

namespace bts
{

    EnemySpawner::EnemySpawner(const std::string& file_path, const std::string& sound_path)
        : Spawner([&]() { return CreateEnemySpawnPosition(); }, enemy_spawn_rate, sound_path) {
        texture = LoadTexture(file_path.c_str());
    }

    void EnemySpawner::Draw() const
    {
        auto& enemies = this->GetEntities();
        for (auto& e : enemies) {
            if (!e.IsAlive())
                continue;

            Vector2 position = e.GetPosition();

            int center_x = static_cast<int>(position.x) - texture.width / 2;
            int center_y = static_cast<int>(position.y) - texture.height / 2;

            DrawTexture(texture, center_x + SHADOW_OFFSET_X, center_y + SHADOW_OFFSET_Y, Fade(BLACK, SHADOW_ALPHA));
            DrawTexture(texture, center_x, center_y, WHITE);
        }

        //Spawner::Draw();
    }
    void EnemySpawner::UnLoad() {
        Spawner::UnLoad();
        UnloadTexture(texture);
    }


    Vector2 EnemySpawner::CreateEnemySpawnPosition() {
        int spawn_offset = static_cast<int>(SPAWN_PADDING);
        float random_x_position = static_cast<float>(GetRandomValue(spawn_offset, WIDTH - spawn_offset));
        return { random_x_position, -SPAWN_PADDING };
    }
}