#pragma once

#include "Vec2.hpp"

#include <SFML/Graphics.hpp>

enum EnumAnimation { AniDefault = -1, AniWalk, AniBlockCoin, AniStand, ANI_COUNT = AniStand + 1 };

class Animation
{
	EnumAnimation m_name = AniDefault;
	sf::Sprite m_sprite;
	size_t m_frameCount = 0;
	size_t m_currentFrame = 0;
	size_t m_duration = 0;
	Vec2 m_size = Vec2(0.0f, 0.0f);

	void update();

public:
	Animation();
	Animation(EnumAnimation name, const sf::Texture& t);
	Animation(EnumAnimation name, const sf::Texture& t, size_t frameCount, size_t duration, Vec2 size);

	// getter
	const Vec2& getSize() const;
	const EnumAnimation getName() const;
	sf::Sprite& getSprite();
	bool hasEnded() const;
};