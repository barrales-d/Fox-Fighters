#pragma once
#ifndef __SPAWNER_H__
#define __SPAWNER_H__

#include <functional>
#include <optional>
#include <vector>
#include <string>

#include <raylib.h>
#include <raymath.h>
#include "event_timer.h"

namespace bts
{
    struct SpawnSettings {
        Vector2 position = { 0 };
        Vector2 velocity = { 0 };

        SpawnSettings() = default;
        SpawnSettings(Vector2 pos, Vector2 vel) : position(pos), velocity(vel) { }

    };
    template<class T>
    class Spawner : public ITimerListener {
    public:
        using SpawnFunc = std::function<SpawnSettings()>;
        Spawner(SpawnFunc spawn_func, float spawn_interval, const std::string& sound_path = std::string(), float sound_volume = 1.0f) :
            get_spawn_settings(spawn_func), spawn_timer(spawn_interval, this) {
            if (!sound_path.empty()) {
                sfx_spawn_sound = LoadSound(sound_path.c_str());
                SetSoundVolume(*sfx_spawn_sound, sound_volume);
            }
            else {
                sfx_spawn_sound = std::nullopt;
            }
        }

        virtual void Draw() const {
            for (const T& entity : entity_list) {
                entity.Draw();
            }
        }
        void Update(float dt) {
            spawn_timer.Update(dt);
            for (T& entity : entity_list) {
                entity.Update(dt);
            }
        }

        virtual void UnLoad() {
            if (sfx_spawn_sound) {
                UnloadSound(*sfx_spawn_sound);
            }
        }

        virtual void OnTimerFinished() override { CreateEntity(); }

        const std::vector<T>& GetEntities() const { return entity_list; }

        void SetSpawnFunction(SpawnFunc sf) { get_spawn_settings = sf; }

        void Start() { spawn_timer.Start(); }
        void Stop() { spawn_timer.Stop(); }

        void SetInterval(float new_interval) { spawn_timer.SetInterval(new_interval); }
        float GetInterval() const { return spawn_timer.GetInterval(); }

    private:
        std::vector<T> entity_list;
        EventTimer spawn_timer;

        SpawnFunc get_spawn_settings;

        std::optional<Sound> sfx_spawn_sound;

    protected:
        void CreateEntity() {
            SpawnSettings ss = get_spawn_settings();
            T entity(ss.position, ss.velocity);

            bool replaced_entity = false;
            for (auto& current_entity : entity_list) {
                if (!current_entity.IsAlive()) {
                    current_entity = entity;
                    replaced_entity = true;
                    break;
                }

            }

            if (!replaced_entity) {
                entity_list.push_back(entity);
            }

            if (sfx_spawn_sound) {
                PlaySound(*sfx_spawn_sound);
            }
        }
    };
}

#endif // !__SPAWNER_H__
