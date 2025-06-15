#pragma once
#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <vector>
#include <string>

#include <raylib.h>
#include <raymath.h>

#include "constants.h"
#include "game_object.h"
#include "event_timer.h"
#include "bullet_spawner.h"

namespace bts {
    class Player : public GameObject {
    public:
        Player(const std::string player_paths[PLAYER_ASSET_LENGTH], const std::string& bullet_path, const std::string& bullet_sound_path = std::string(), float bullet_sound_volume = 1.0f);

        virtual void Draw() const override;
        virtual void Update(float dt) override;
        virtual void UnLoad() override;

    public:
        BulletSpawner bullet_spawner;
        int score = 0;

        Vector2 GetGaugeData() const { return { bullet_gauge, bullet_gauge_limit }; }

    private:
        void HandleMovement(float dt);
        void FireBullet(float dt);
        void HandleCooldown(float dt);

    private:
        Timer cooldown_timer = Timer(0.5f);
        bool on_cooldown = false;

        // The player can hold the fire key for 2 seconds
        float bullet_gauge = 0.0f;
        static constexpr float bullet_gauge_limit = 2.0f;

        std::vector<Texture2D> textures;
        Texture2D* current_texture;

    };
}

#endif // !__PLAYER_H__
