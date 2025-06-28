#include "player.h"

static constexpr Color player_color = { 255, 50, 50, 255 };

static constexpr Vector2 start_position = { WIDTH / 2, HEIGHT - (HEIGHT / 3) };
static constexpr Vector2 start_velocity = { 350, 350 };
static constexpr Vector2 bullet_velocity = { 0, -500 };
static constexpr float hitbox_radius = 25;
static constexpr float bullet_fire_rate = 0.05f;

static constexpr int PLAYER_ASSET_DEFAULT = 0;
static constexpr int PLAYER_ASSET_LEAN_LEFT = 1;
static constexpr int PLAYER_ASSET_LEAN_RIGHT = 2;

namespace bts
{
    Player::Player(const std::string& bullet_sound_path, float bullet_sound_volume) :
        GameObject(start_position, start_velocity, Hitbox::CIRCLE, Hitbox::HBData(hitbox_radius)),
        bullet_spawner([&]() { return SpawnNextBullet(); }, bullet_fire_rate, bullet_sound_path, bullet_sound_volume) {

        current_texture = AssetManager::GetInstance().GetTexture(TextureID::PLAYER_STRAIGHT);
    }

    void Player::Draw() const
    {
        if (!this->IsAlive())
            return;

        bullet_spawner.Draw();

        int center_x = static_cast<int>(position.x - (float)current_texture.width / 2);
        int center_y = static_cast<int>(position.y - (float)current_texture.height / 2);

        DrawTexture(current_texture, center_x + SHADOW_OFFSET_X, center_y + SHADOW_OFFSET_Y, Fade(BLACK, SHADOW_ALPHA));
        DrawTexture(current_texture, center_x, center_y, WHITE);
        //DrawCircleLines(static_cast<int>(position.x), static_cast<int>(position.y), hitbox.data.radius, player_color);
    }

    void Player::Update(float dt)
    {
        if (!this->IsAlive())
            return;

        this->HandleMovement(dt);

        if (!on_cooldown) {
            this->FireBullet(dt);
        }
        else {
            this->HandleCooldown(dt);
        }

        bullet_spawner.Update(dt);
    }
    void Player::UnLoad() {
        bullet_spawner.UnLoad();
    }


    void Player::HandleMovement(float dt)
    {
        current_texture = AssetManager::GetInstance().GetTexture(TextureID::PLAYER_STRAIGHT);

        Vector2 direction = { 0 };
        if (IsKeyDown(KEY_W)) {
            direction.y = -1;
        }
        else if (IsKeyDown(KEY_S)) {
            direction.y = 1;
        }

        if (IsKeyDown(KEY_A)) {
            direction.x = -1;
            current_texture = AssetManager::GetInstance().GetTexture(TextureID::PLAYER_LEFT);
        }
        else if (IsKeyDown(KEY_D)) {
            direction.x = 1;
            current_texture = AssetManager::GetInstance().GetTexture(TextureID::PLAYER_RIGHT);

        }

        Vector2 old_position = position;
        position += direction * velocity * dt;

        if (position.x <= 0 || position.x > WIDTH) { position.x = old_position.x; }
        if (position.y <= 0 || position.y > HEIGHT) { position.y = old_position.y; }
    }

    void Player::FireBullet(float dt)
    {
        if (bullet_gauge >= bullet_gauge_limit) {
            // Player Reached Bullet limit, go on cooldown
            on_cooldown = true;
            bullet_spawner.Stop();
            return;
        }

        if (bullet_gauge < bullet_gauge_limit && IsKeyDown(KEY_SPACE)) {
            // Player can shoot
            bullet_spawner.Start();
            bullet_gauge += dt;
        }
        else {
            // Player is not hold the fire button
            bullet_spawner.Stop();
            bullet_gauge -= dt;
            if (bullet_gauge < 0) bullet_gauge = 0;
        }

    }

    void Player::HandleCooldown(float dt)
    {
        if (cooldown_timer.IsReady()) {
            bullet_gauge -= dt;
            on_cooldown = false;
        }

        cooldown_timer.Update(dt);
    }

    SpawnSettings Player::SpawnNextBullet()
    {
        return SpawnSettings(GetPosition(), bullet_velocity);
    }
}