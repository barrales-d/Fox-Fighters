#include "bullet.h"

static constexpr Color bullet_color = { 100, 255, 200, 255 };

static constexpr float hitbox_radius = 8.0f;

namespace bts
{
    Bullet::Bullet(Vector2 start_position, Vector2 velocity) : GameObject(start_position, velocity, Hitbox::CIRCLE, Hitbox::HBData(hitbox_radius)) {}

    void Bullet::Draw() const
    {
        if (IsAlive()) {
            //DrawCircleLines(static_cast<int>(position.x), static_cast<int>(position.y), hitbox.data.radius, bullet_color);
            Texture2D texture = AssetManager::GetInstance().GetTexture(TextureID::PLAYER_BULLET);

            int center_x = static_cast<int>(position.x - (float)texture.width / 2);
            int center_y = static_cast<int>(position.y - (float)texture.height / 2);
            DrawTexture(texture, center_x, center_y, WHITE);
        }
    }

    void Bullet::Update(float dt)
    {
        position += Vector2UnitY * velocity * dt;

        if (position.y < -SPAWN_PADDING) {
            this->Kill();
        }
    }
}