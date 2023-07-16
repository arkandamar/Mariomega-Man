#pragma once

#include "Vec2.hpp"

#include <SFML/Graphics.hpp>

enum EnumAnimation { AniDefault = -1, AniWalk, AniBlockCoin, AniShootAir, AniGround, AniShoot, AniShootWalk, AniJump, AniBrick, AniStand, ANI_COUNT = AniStand + 1 };

class Animation
{
	EnumAnimation m_name = AniDefault;
	sf::Sprite m_sprite;
	size_t m_frameCount = 0;
	size_t m_currentFrame = 0;
	size_t m_frameDuration = 0;
	size_t m_space = 0;
	Vec2 m_size = Vec2(0.0f, 0.0f);
	Vec2 m_initPos = Vec2(0.0f, 0.0f);


public:
	Animation();
	Animation(EnumAnimation name, const sf::Texture& t);
	Animation(EnumAnimation name, const sf::Texture& t, size_t frameCount, size_t duration, Vec2 size);

	void update();

	// setter
	void setIntRect(int x, int y, int space = 0);
	void setIntRect(int x, int y, int sizeX, int sizeY, int space = 0);

	// getter
	const Vec2& getSize() const;
	const EnumAnimation getName() const;
	sf::Sprite& getSprite();
	bool hasEnded() const;
};