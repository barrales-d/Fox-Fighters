// main.cpp : Defines the entry point for the application.
//

#include "bullet_game.h"

#include <raylib.h>
#include <imgui.h>
#include <rlImGui.h>

#include <array>
#include <vector>
#include <memory>
#include <string>

#ifndef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
int main()
{
    SetTraceLogLevel(LOG_NONE);
#else
int main()
{
#endif

    InitWindow(WIDTH, HEIGHT, "Fox Fighters");
    SetTargetFPS(TARGET_FPS);
    InitAudioDevice();
    rlImGuiSetup(true);

    Image icon = LoadImage(ASSETS_PATH"graphics/icon.png");
    SetWindowIcon(icon);

    ImGuiIO& io = ImGui::GetIO();
    io.Fonts->AddFontFromFileTTF(ASSETS_PATH"fonts/Pixel Game Extrude.otf", FONT_SIZE_LG);
    io.Fonts->AddFontFromFileTTF(ASSETS_PATH"fonts/Pixel Game.otf", FONT_SIZE_SM);
    io.Fonts->Build();

    Music music_background = LoadMusicStream(ASSETS_PATH"music/background/Raining Bits.ogg");
    Sound sfx_explosion = LoadSound(ASSETS_PATH"music/sfx/Explosion3.wav");

    SetMusicVolume(music_background, BACKGROUND_MUSIC_VOLUME);
    PlayMusicStream(music_background);

    bts::Player player(PLAYER_ASSETS, ASSETS_PATH"graphics/bullet.png", ASSETS_PATH"music/sfx/LaserShot9.mp3", BULLET_SFX_VOLUME);
    bts::EnemySpawner enemies(ASSETS_PATH"graphics/dog_plane.png");
    bts::Background background(ASSETS_PATH"graphics/background.png");
    bts::Timer level_timer(LEVEL_LENGTH);
    int wave_count = 1;

    Color background_color = { 10, 10, 10, 255 };

    while (!WindowShouldClose() && player.IsAlive())
    {
        float delta_time = GetFrameTime();
        background.Update(delta_time);
        player.Update(delta_time);
        enemies.Update(delta_time);
        UpdateMusicStream(music_background);

        auto& bullet_list = player.bullet_spawner.GetEntities();
        auto& enemy_list = enemies.GetEntities();

        // Bullet, Enemy Collision
        for (auto& bullet : bullet_list) {
            bts::GameObject* bullet_obj = (bts::GameObject*)(&bullet);
            for (auto& enemy : enemy_list) {
                bts::GameObject* enemy_obj = (bts::GameObject*)(&enemy);
                if (bullet_obj->collidesWith(enemy_obj)) {
                    PlaySound(sfx_explosion);
                    bullet_obj->Kill();
                    enemy_obj->Kill();
                    player.score++;
                }
            }
        }

        // Player, Enemy Collision
        for (auto& enemy : enemy_list) {
            bts::GameObject* enemy_obj = (bts::GameObject*)(&enemy);
            if (player.collidesWith(enemy_obj)) {
                player.Kill();
                enemy_obj->Kill();
            }
        }

        if (level_timer.IsReady()) {
            // Increases Difficulty by increasing the amount of enemies that spawn
            wave_count++;

            float current_spawn_rate = enemies.GetInterval();
            if (current_spawn_rate > MAX_SPAWN_RATE)
                enemies.SetInterval(current_spawn_rate - INCREASE_SPAWN_RATE_BY);

            player.score += LEVEL_SCORE_INCREASE;
            player.IncreaseVelocity({ LEVEL_INCREASE_PLAYER_SPEED_X, LEVEL_INCREASE_PLAYER_SPEED_Y });

            float current_bullet_rate = player.bullet_spawner.GetInterval();
            if (current_bullet_rate > MAX_BULLET_RATE)
                player.bullet_spawner.SetInterval(current_bullet_rate - INCREASE_BULLET_RATE_BY);

            if (background.GetVelocity().y < MAX_BACKGROUND_SPEED)
                background.IncreaseVelocity({ 0, LEVEL_INCREASE_BACKGROUND_SPEED_Y });

        }
        level_timer.Update(delta_time);

        BeginDrawing();

        ClearBackground(background_color);
        background.Draw();
        player.Draw();
        enemies.Draw();

        rlImGuiBegin();

        ImGui::SetNextWindowBgAlpha(GUI_WINDOW_ALPHA);
        ImGui::SetNextWindowPos(ImVec2(0, 0)); // Position at top-left corner
        ImGui::SetNextWindowSize(ImVec2((float)GetScreenWidth(), (float)GetScreenHeight())); // Fullscreen size


        ImGui::Begin("Overlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);

        ImGui::PushFont(io.Fonts->Fonts[1]);
        ImVec2 text_size = ImGui::CalcTextSize("Wave 000");
        ImGui::PopFont();

        bts::ui::PrintImGuiText(io, ImVec2(GUI_PADDING, HEIGHT - text_size.y - GUI_PADDING), GUI_TEXT_COL, "Wave %03d", wave_count);

        ImGui::PushFont(io.Fonts->Fonts[1]);
        text_size = ImGui::CalcTextSize("000");
        ImGui::PopFont();

        bts::ui::PrintImGuiText(io, ImVec2(WIDTH - text_size.x - GUI_PADDING, GUI_PADDING), GUI_TEXT_COL, "%03d", player.score);

        bts::ui::DisplayGauge(player.GetGaugeData());


        ImGui::End();
        rlImGuiEnd();

        EndDrawing();
    }

    while (!WindowShouldClose()) {
        UpdateMusicStream(music_background);

        BeginDrawing();
        ClearBackground(background_color);
        background.Draw();
        rlImGuiBegin();

        ImGui::SetNextWindowBgAlpha(GUI_WINDOW_ALPHA);
        ImGui::SetNextWindowPos(ImVec2(0, 0)); // Position at top-left corner
        ImGui::SetNextWindowSize(ImVec2((float)GetScreenWidth(), (float)GetScreenHeight())); // Fullscreen size

        ImGui::Begin("Overlay", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoCollapse);

        ImGui::PushFont(io.Fonts->Fonts[1]);
        ImVec2 text_size = ImGui::CalcTextSize("Final Score: 000");
        ImGui::PopFont();

        bts::ui::PrintImGuiText(io, ImVec2(WIDTH / 2 - text_size.x / 2, HEIGHT / 2 - text_size.y / 2), GUI_TEXT_COL, "Final Score: %03d", player.score);

        ImGui::End();
        rlImGuiEnd();
        EndDrawing();
    }

    player.UnLoad();
    background.UnLoad();
    enemies.UnLoad();

    UnloadSound(sfx_explosion);
    UnloadMusicStream(music_background);
    UnloadImage(icon);
    CloseAudioDevice();
    rlImGuiShutdown();
    CloseWindow();

}