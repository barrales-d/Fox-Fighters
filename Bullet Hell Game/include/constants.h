#pragma once
#ifndef __CONSTANTS_H__
#define __CONSTANTS_H__

#include <string>

constexpr int WIDTH = 600;
constexpr int HEIGHT = 800;

constexpr int TARGET_FPS = 60;

constexpr float BACKGROUND_MUSIC_VOLUME = 0.15f;
constexpr float BULLET_SFX_VOLUME = 0.2f;
constexpr float ENEMY_SFX_VOLUME = 0.35f;

// Allow game objects to go outside of the screen by this much
constexpr float SPAWN_PADDING = 50;

constexpr float MAX_SPAWN_RATE = 0.2f;
constexpr float INCREASE_SPAWN_RATE_BY = 0.12f;
constexpr float LEVEL_LENGTH = 60.0f;

constexpr int LEVEL_SCORE_INCREASE = 10;

constexpr float LEVEL_INCREASE_PLAYER_SPEED_X = 0.75f;
constexpr float LEVEL_INCREASE_PLAYER_SPEED_Y = 0.65f;

constexpr float MAX_BULLET_RATE = 0.025f;
constexpr float INCREASE_BULLET_RATE_BY = 0.01f;

constexpr float LEVEL_INCREASE_BACKGROUND_SPEED_Y = 50.0f;
constexpr float MAX_BACKGROUND_SPEED = 800.0f;

constexpr int SHADOW_OFFSET_X = 10;
constexpr int SHADOW_OFFSET_Y = 50;
constexpr float SHADOW_ALPHA = 0.3f;

#endif // !__CONSTANTS_H__
