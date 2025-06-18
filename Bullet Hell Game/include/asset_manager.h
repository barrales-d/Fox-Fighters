#pragma once
#ifndef __ASSET_MANAGER_H__
#define __ASSET_MANAGER_H__

#include <array>
#include <string>
#include <raylib.h>

namespace bts
{
	enum class TextureID : size_t
	{
		BACKGROUND,
		PLAYER_LEFT,
		PLAYER_STRAIGHT,
		PLAYER_RIGHT,
		PLAYER_BULLET,
		ENEMY_STRAIGHT,
		ENEMY_RIGHT,
		ENEMY_LEFT,

		COUNT,
	};

	class AssetManager
	{
	public:
		static AssetManager& GetInstance();
		void LoadTextures(const std::string& file_path);
		void UnloadTextures();

		Texture2D GetTexture(TextureID texID) const;
	private:
		AssetManager() = default;
		~AssetManager() = default;
	private:
		std::array<Texture2D, static_cast<size_t>(TextureID::COUNT)> textures;
	};

}

#endif // !__ASSET_MANAGER_H__
