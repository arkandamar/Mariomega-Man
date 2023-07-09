#pragma once

#include "Components.hpp"

CTransform::CTransform() {};
CTransform::CTransform(const Vec2& p) : pos(p) {};

CShape::CShape(float radius, int points, const sf::Color& fill
	, const sf::Color& outline, float thickness)
	: circle(radius, points)
{
	circle.setFillColor(fill);
	circle.setOutlineColor(outline);
	circle.setOutlineThickness(thickness);
	circle.setOrigin(radius, radius);
};

CCollision::CCollision(float rad) : radius(rad) {};

CScore::CScore(int s) : score(s) {};

CLifespan::CLifespan(int total) : remaining(total), total(total) {};

CInput::CInput() {};

CAnimation::CAnimation(Animation animation, bool loop) : animation(animation), isLoop(loop) {};

CGravity::CGravity(size_t accel) : accel(accel) {};

CState::CState(bool groundState, bool airState) : onGround(groundState), inAir(airState) {};

CBoundingBox::CBoundingBox(Vec2 size) : size(size), halfSize(size / 2.0f) {};

