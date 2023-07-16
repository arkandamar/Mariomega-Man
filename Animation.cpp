#pragma once

#include "Animation.hpp"

#include <iostream>

Animation::Animation() {}

Animation::Animation(EnumAnimation name, const sf::Texture& t)
	: m_name(name), m_sprite(t) {}


Animation::Animation(EnumAnimation name, const sf::Texture& t, size_t frameCount, size_t frameDuration, Vec2 size)
	: m_name(name), m_sprite(t), m_frameCount(frameCount), m_frameDuration(frameDuration), m_currentFrame(0), m_size(size)
{
	m_sprite.setOrigin(m_size.x / 2.0f, m_size.y / 2.0f);
	m_sprite.setTextureRect(sf::IntRect(0, 0, m_size.x, m_size.y));
}

// setter
void Animation::setIntRect(int x, int y, int space)
{
	m_space = space;
	m_initPos = Vec2(x, y);
	m_sprite.setTextureRect(sf::IntRect(x, y, (int) m_size.x, (int) m_size.y));
}

void Animation::setIntRect(int x, int y, int sizeX, int sizeY, int space)
{
	m_space = space;
	m_initPos = Vec2(x, y);
	m_size = Vec2(sizeX, sizeY);
	m_sprite.setOrigin(m_size.x / 2, m_size.y / 2);
	m_sprite.setTextureRect(sf::IntRect(x, y, m_size.x, m_size.y));
}

// update the animation to show the next frame
void Animation::update()
{
	// calculate the correct frame of animation to play based on currentFrame and speed
	if (m_frameDuration != 0)
	{
		int indexTexture = (m_currentFrame / m_frameDuration) % m_frameCount;

		// set texture rectangle properly
		m_sprite.setTextureRect(sf::IntRect(m_initPos.x + (indexTexture * m_size.x + m_space), m_initPos.y, m_size.x, m_size.y));

		m_currentFrame++;
	}
}

const Vec2& Animation::getSize() const
{
	return m_size;
}

const EnumAnimation Animation::getName() const
{
	return m_name;
}

sf::Sprite& Animation::getSprite()
{
	return m_sprite;
}

bool Animation::hasEnded() const
{
	// detect when animation has ended
	if (m_frameDuration != 0)
	{
		if (m_currentFrame > m_frameCount * m_frameDuration)
		{
			return true;
		}
	}
}