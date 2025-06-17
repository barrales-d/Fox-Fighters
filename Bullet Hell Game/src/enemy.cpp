#include "enemy.h"

static constexpr Color enemy_color = { 255, 50, 50, 255 };

static constexpr Vector2 default_velocity = { 300, 500 };
static constexpr int min_speed_x_range = 250;
static constexpr int max_speed_x_range = 350;
static constexpr int min_speed_y_range = 550;
static constexpr int max_speed_y_range = 750;
static constexpr float hitbox_radius = 35.0f;

namespace bts
{
    Enemy::Enemy(Vector2 start_position) : GameObject(start_position, default_velocity, Hitbox::CIRCLE, Hitbox::HBData(hitbox_radius)) {
        // Calculate the random speed of the Enemy
        velocity.x = static_cast<float>(GetRandomValue(min_speed_x_range, max_speed_x_range));
        velocity.y = static_cast<float>(GetRandomValue(min_speed_y_range, max_speed_y_range));

        // Pick a random direction [LEFT, STRAIGHT, RIGHT];
        velocity.x *= GetRandomValue(-1, 1);
        // TODO: Add Timer switch_dir(3.0f) and add logic to switch the x velocity on IsReady(); so the enemys have flight patterns
    }

    void Enemy::Draw() const {
        if (this->IsAlive()) {
            DrawCircleLinesV(position, hitbox.data.radius, enemy_color);
        }
    }

    void Enemy::Update(float dt) {
        if (this->IsAlive()) {
            position += velocity * dt;
        }

        if (position.y >= HEIGHT + SPAWN_PADDING) {
            this->Kill();
        }
        if (position.x >= WIDTH + SPAWN_PADDING || position.x <= -SPAWN_PADDING) {
            this->Kill();
        }
    }
}