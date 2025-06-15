#include "bullet.h"

static constexpr Color bullet_color = { 100, 255, 200, 255 };

static constexpr Vector2 default_velocity = { 0, 500 };
static constexpr float hitbox_radius = 8.0f;

namespace bts
{
    Bullet::Bullet(Vector2 start_position) : GameObject(start_position, default_velocity, Hitbox::CIRCLE, Hitbox::HBData(hitbox_radius)) {}

    void Bullet::Draw() const
    {

        DrawCircleLines(static_cast<int>(position.x), static_cast<int>(position.y), hitbox.data.radius, bullet_color);
    }

    void Bullet::Update(float dt)
    {
        position -= Vector2UnitY * velocity * dt;

        if (position.y < -SPAWN_PADDING) {
            this->Kill();
        }
    }
}