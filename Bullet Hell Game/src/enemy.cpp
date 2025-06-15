#include "enemy.h"

static constexpr Color enemy_color = { 255, 50, 50, 255 };

static constexpr Vector2 default_velocity = { 0, 500 };
static constexpr int min_velocity_range = 550;
static constexpr int max_velocity_range = 750;
static constexpr float hitbox_radius = 35.0f;

namespace bts
{
    Enemy::Enemy(Vector2 start_position) : GameObject(start_position, default_velocity, Hitbox::CIRCLE, Hitbox::HBData(hitbox_radius)) {
        velocity.y = static_cast<float>(GetRandomValue(min_velocity_range, max_velocity_range));
    }

    void Enemy::Draw() const {
        if (this->IsAlive()) {
            DrawCircleLinesV(position, hitbox.data.radius, enemy_color);
        }
    }

    void Enemy::Update(float dt) {
        if (this->IsAlive()) {
            position += Vector2UnitY * velocity * dt;
        }

        if (position.y >= HEIGHT + SPAWN_PADDING) {
            this->Kill();
        }
    }
}