#include "asset_manager.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>
#include <stdexcept>

using json = nlohmann::json;

namespace bts
{
    static const TextureID TexIDFromString(const std::string& tex_str)
    {
        if (tex_str == "BACKGROUND") { return TextureID::BACKGROUND; }
        else if (tex_str == "PLAYER_LEFT") { return TextureID::PLAYER_LEFT; }
        else if (tex_str == "PLAYER_STRAIGHT") { return TextureID::PLAYER_STRAIGHT; }
        else if (tex_str == "PLAYER_RIGHT") { return TextureID::PLAYER_RIGHT; }
        else if (tex_str == "PLAYER_BULLET") { return TextureID::PLAYER_BULLET; }
        else if (tex_str == "ENEMY_STRAIGHT") { return TextureID::ENEMY_STRAIGHT; }
        else if (tex_str == "ENEMY_RIGHT") { return TextureID::ENEMY_RIGHT; }
        else if (tex_str == "ENEMY_LEFT") { return TextureID::ENEMY_LEFT; }
        else { throw std::runtime_error(R"(ERROR: Unknown TEXTURE ID: )" + tex_str); }
    }

    AssetManager& bts::AssetManager::GetInstance()
    {
        static AssetManager instance;
        return instance;
    }

    void bts::AssetManager::LoadTextures(const std::string& file_path)
    {
        std::ifstream file(file_path);
        json textureArray;

        file >> textureArray;
        for (const auto& item : textureArray) {
            for (auto it = item.begin(); it != item.end();++it) {
                const std::string& key = it.key();
                const std::string& file_path = it.value();

                TextureID texID = TexIDFromString(key);
                textures[static_cast<size_t>(texID)] = LoadTexture((ASSETS_PATH + file_path).c_str());
            }
        }
    }

    void bts::AssetManager::UnloadTextures()
    {
        for (auto& texture : textures)
            UnloadTexture(texture);
    }

    Texture2D bts::AssetManager::GetTexture(TextureID texID) const
    {
        return textures[static_cast<size_t>(texID)];
    }
}
