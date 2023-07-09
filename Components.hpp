#pragma once

#include "Vec2.hpp"
#include "Animation.hpp"

#include <SFML/Graphics.hpp>

class Component 
{
public:
	bool has = false;
};

class CTransform : public Component
{
public:
	Vec2 pos = { 0.0, 0.0 };
	Vec2 prevPos = { 0.0, 0.0 };
	Vec2 velocity = { 0.0, 0.0 };
	Vec2 scale = { 0.0, 0.0 };
	float angle = 0;

	CTransform();
	CTransform(const Vec2& p);
};

class CShape : public Component
{
public:
	sf::CircleShape circle;
	CShape(float radius, int points, const sf::Color& fill, const sf::Color& outline, float thickness);
};

class CCollision : public Component
{
public:
	float radius = 0;
	CCollision(float rad);
};

class CScore : public Component
{

public:
	int score = 0;
	CScore(int s);
};

class CLifespan : public Component
{
public:
	int remaining = 0; // remaining amount of lifespan
	int total = 0; // total inital amount of lifespan
	CLifespan(int total);
};

class CInput : public Component
{
public:
	bool up = false;
	bool left = false;
	bool right = false;
	bool down = false;
	bool shoot = false;

	CInput();
};

class CAnimation : public Component
{
public:
	Animation animation;
	bool isLoop;
	CAnimation(Animation animation, bool loop);
};

class CGravity : public Component
{
public:
	size_t accel;
	CGravity(size_t accel);
};

class CState : public Component
{
public:
	bool onGround;
	bool inAir;
	CState(bool groundState, bool airState);
};

class CBoundingBox : public Component
{
public:
	Vec2 size;
	Vec2 halfSize;
	CBoundingBox(Vec2 size);
};