#include "background.h"

static constexpr Vector2 default_position = { 0, 0 };
static constexpr Vector2 default_velocity = { 0, 525 };

static constexpr float time_of_day = 0.57f;

namespace bts
{
    Background::Background(const std::string& file_path)
        : GameObject(default_position, default_velocity) {
        texture = LoadTexture(file_path.c_str());
        GameObject::SetHitbox(Hitbox::RECT, Hitbox::HBData((float)texture.width, (float)texture.height));

        position.y = -hitbox.data.rect.y / 2;
    }

    void Background::Draw() const
    {
        DrawTexture(texture, static_cast<int>(position.x), static_cast<int>(position.y), Fade(WHITE, time_of_day));
    }

    void Background::Update(float dt)
    {
        if (position.y >= 0) {
            position.y = -hitbox.data.rect.y / 2;
        }
        position += velocity * dt;
    }

    void Background::UnLoad() {
        UnloadTexture(texture);
    }

}