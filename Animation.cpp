#pragma once

#include "Animation.hpp"

Animation::Animation() {}

Animation::Animation(EnumAnimation name, const sf::Texture& t)
	: m_name(name), m_sprite(t) {}


Animation::Animation(EnumAnimation name, const sf::Texture& t, size_t frameCount, size_t frameDuration, Vec2 size)
	: m_name(name), m_sprite(t), m_frameCount(frameCount), m_frameDuration(frameDuration), m_currentFrame(0), m_size(size)
{
	m_sprite.setOrigin(m_size.x / 2.0f, m_size.y / 2.0f);
}

// setter
void Animation::setIntRect(int x, int y)
{
	m_sprite.setTextureRect(sf::IntRect(x, y, (int) m_size.x, (int) m_size.y));
}

// update the animation to show the next frame
void Animation::update()
{
	// add speed variable to the current frame
	m_currentFrame++;
	// calculate the correct frame of animation to play based on currentFrame and speed
	// set texture rectangle properly
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
	return false;
}