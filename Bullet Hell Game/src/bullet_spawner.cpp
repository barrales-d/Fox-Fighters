#include "bullet_spawner.h"

namespace bts
{
    BulletSpawner::BulletSpawner(const std::string& file_path, float spawn_interval, const std::string& sound_path, float sound_volume)
        : Spawner([]() { return Vector2Zero(); }, spawn_interval, sound_path, sound_volume) {
        texture = LoadTexture(file_path.c_str());
    }

    void BulletSpawner::Draw() const
    {
        //Spawner::Draw();
        auto& bullets = this->GetEntities();
        for (auto& b : bullets) {
            if (!b.IsAlive())
                continue;

            Vector2 position = b.GetPosition();

            int center_x = static_cast<int>(position.x - (float)texture.width / 2);
            int center_y = static_cast<int>(position.y - (float)texture.height / 2);

            DrawTexture(texture, center_x, center_y, WHITE);
        }
    }

    void BulletSpawner::UnLoad() {
        Spawner::UnLoad();
        UnloadTexture(texture);
    }
}