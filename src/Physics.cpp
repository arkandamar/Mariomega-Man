#pragma once

#include "Physics.hpp"

Vec2 Physics::GetOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{
	// return the overlap rectangle size of the bounding boxes of entity a and b
	Vec2 diff = a->getComponent<CTransform>().pos - b->getComponent<CTransform>().pos;
	Vec2 delta = Vec2(abs(diff.x), abs(diff.y));
	Vec2 result = a->getComponent<CBoundingBox>().halfSize + b->getComponent<CBoundingBox>().halfSize - delta;

	return result;
}


Vec2 Physics::GetPreviousOverlap(std::shared_ptr<Entity> a, std::shared_ptr<Entity> b)
{	
	// return the previous overlap rectangle size of the bounding boxes of entity a and b
	// previous overlap uses the entity's previous position
	Vec2 diff = a->getComponent<CTransform>().prevPos - b->getComponent<CTransform>().prevPos;
	Vec2 delta = Vec2(abs(diff.x), abs(diff.y));
	Vec2 result = a->getComponent<CBoundingBox>().halfSize + b->getComponent<CBoundingBox>().halfSize - delta;

	return result;
}