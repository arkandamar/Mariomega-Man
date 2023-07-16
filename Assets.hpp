#pragma once

#include "Animation.hpp"

#include <array>
#include <SFML/Audio.hpp>

enum EnumTexture { TexMegaman, TexMegamanShoot, TexPipeScenery, TexCoinArise, TexCoinObtain, TexBlockCoin, TextCloud, TexBlock, TEX_COUNT = TexBlock + 1 };
enum EnumFont { FontMario, FontRoboto, FontMegaman, FONT_COUNT = FontMegaman + 1 };
enum EnumSound { DeathSound, SOUND_COUNT = DeathSound + 1 };

struct AniType
{
	EnumAnimation name;
	EnumTexture texture;
	int frameCount;
	int frameDuration;
};

class Assets
{
	std::array<sf::Texture, EnumTexture::TEX_COUNT> m_textures;
	std::array<Animation, EnumAnimation::ANI_COUNT> m_animations;
	std::array<sf::Font, EnumFont::FONT_COUNT> m_fonts;
	std::array<sf::Sound, EnumSound::SOUND_COUNT> m_sounds;
	std::array<AniType, EnumAnimation::ANI_COUNT> m_aniType;

public:
	// setter
	void addTexture(EnumTexture name, const std::string& path);
	void addAnimation(EnumAnimation name, Animation animation);
	void addFont(EnumFont name, const std::string& path);
	void addSound(EnumSound name, const std::string& path);
	void registerAnimation(EnumAnimation name, EnumTexture texture, int frameCount, int duration, Vec2 size);

	// getter
	sf::Texture& getTexture(EnumTexture name);
	Animation& getAnimation(EnumAnimation name);
	sf::Font& getFont(EnumFont name);
	sf::Sound& getSound(EnumSound name);
	AniType& getAniType(EnumAnimation name);
};