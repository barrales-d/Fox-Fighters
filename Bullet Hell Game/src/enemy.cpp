#include "enemy.h"

static constexpr Color enemy_color = { 255, 50, 50, 255 };

static constexpr Vector2 default_velocity = { 300, 500 };
static constexpr int min_speed_x_range = 250;
static constexpr int max_speed_x_range = 350;
static constexpr int min_speed_y_range = 550;
static constexpr int max_speed_y_range = 750;
static constexpr float hitbox_radius = 35.0f;
static constexpr float switch_interval = 0.4f;

namespace bts
{
    Enemy::Enemy(Vector2 start_position)
        : GameObject(start_position, default_velocity, Hitbox::CIRCLE, Hitbox::HBData(hitbox_radius)),
        switch_dir(switch_interval) {
        // Calculate the random speed of the Enemy
        velocity.x = static_cast<float>(GetRandomValue(min_speed_x_range, max_speed_x_range));
        velocity.y = static_cast<float>(GetRandomValue(min_speed_y_range, max_speed_y_range));

        // Pick a random direction [LEFT, STRAIGHT, RIGHT];
        velocity.x *= GetRandomValue(-1, 1);
    }

    void Enemy::Draw() const {
        if (this->IsAlive()) {
            //DrawCircleLinesV(position, hitbox.data.radius, enemy_color);
            Texture2D texture = AssetManager::GetInstance().GetTexture(TextureID::ENEMY_STRAIGHT);
            int center_x = static_cast<int>(position.x) - texture.width / 2;
            int center_y = static_cast<int>(position.y) - texture.height / 2;

            DrawTexture(texture, center_x + SHADOW_OFFSET_X, center_y + SHADOW_OFFSET_Y, Fade(BLACK, SHADOW_ALPHA));
            DrawTexture(texture, center_x, center_y, WHITE);
        }
    }

    void Enemy::Update(float dt) {
        if (this->IsAlive()) {
            position += velocity * dt;
            if (switch_dir.IsReady()) {
                velocity.x *= GetRandomValue(-1, 1);
            }
            switch_dir.Update(dt);
        }

        if (position.y >= HEIGHT + SPAWN_PADDING) {
            this->Kill();
        }

        if (position.x <= SPAWN_PADDING) {

            position.x = SPAWN_PADDING;
        }
        else if (position.x >= WIDTH - SPAWN_PADDING) {
            position.x = WIDTH - SPAWN_PADDING;
        }
    }
}