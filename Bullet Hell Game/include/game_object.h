#pragma once
#ifndef __GAME_OBJECT_H__
#define __GAME_OBJECT_H__

#include <iostream>
#include <raylib.h>
#include <raymath.h>

namespace bts {

    struct Hitbox {
        enum HBType {
            RECT,
            CIRCLE,
            POINT
        };

        union HBData {
            Vector2 rect;
            float radius;
            Vector2 pt;

            HBData() {}

            HBData(float width, float height) : rect({ width, height }) {}
            HBData(float radius) : radius(radius) {}
            HBData(Vector2 p) : pt(p) {}
        };

        HBType type;
        HBData data;

    };

    class GameObject {
    public:
        GameObject() = default;
        GameObject(Vector2 pos, Vector2 vel, Hitbox::HBType type, Hitbox::HBData data) :
            position(pos), velocity(vel), is_alive(true) {
            hitbox.type = type;
            hitbox.data = data;
        }
        GameObject(Vector2 pos, Vector2 vel) : position(pos), velocity(vel), is_alive(true) {
            hitbox.data = { };
        }

        virtual void Draw() const = 0;
        virtual void Update(float dt) = 0;
        virtual void UnLoad() = 0;

        bool IsAlive() const { return is_alive; };
        Vector2 GetPosition() const { return position; }

        void Kill() { is_alive = false; }


        void IncreaseVelocity(Vector2 new_velocity) { this->velocity += new_velocity; }
        Vector2 GetVelocity() const { return this->velocity; }

        void SetHitbox(Hitbox::HBType type, Hitbox::HBData data) {
            hitbox.type = type;
            hitbox.data = data;
        }

        bool collidesWith(const GameObject* other) {
            if (!this->IsAlive() || !other->IsAlive()) {
                return false;
            }
            if (hitbox.type == Hitbox::HBType::RECT && other->hitbox.type == Hitbox::HBType::RECT) {
                return CheckCollisionRecs(
                    { position.x, position.y, hitbox.data.rect.x, hitbox.data.rect.y },
                    { other->position.x, other->position.y, other->hitbox.data.rect.x, other->hitbox.data.rect.y });
            }
            else if (hitbox.type == Hitbox::HBType::CIRCLE && other->hitbox.type == Hitbox::HBType::CIRCLE) {
                return CheckCollisionCircles(position, hitbox.data.radius, other->position, other->hitbox.data.radius);
            }
            else if (hitbox.type == Hitbox::HBType::CIRCLE && other->hitbox.type == Hitbox::HBType::RECT) {
                return CheckCollisionCircleRec(position, hitbox.data.radius,
                    { other->position.x, other->position.y, other->hitbox.data.rect.x, other->hitbox.data.rect.y });
            }
            else {
                TraceLog(LOG_WARNING, "Have not implement this collision check");
                return false;
            }
        }

    protected:
        Vector2 position = { 0 };
        Vector2 velocity = { 0 };
        Hitbox hitbox = { };

    private:
        bool is_alive = true;
    };
}

#endif // !__GAME_OBJECT_H__
