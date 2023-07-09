#pragma once

#include "Components.hpp"

#include <memory>

enum Tag { Player, Enemy, Tile, Dec, TAG_COUNT = Dec + 1 };

class Entity
{
	size_t m_id = 0;
	Tag m_tag;
	bool m_active = true;

	// make constructor private so entity cannot be created directly
	Entity(const Tag tag, size_t id);

	friend class EntityManager;

public:
	// private member access
	void destroy();
	bool isActive() const;
	const Tag getTag() const;
	const size_t getId() const;

	// component pointers
	std::shared_ptr<CTransform> cTransform;
	std::shared_ptr<CShape> cShape;
	std::shared_ptr<CCollision> cCollision;
	std::shared_ptr<CScore> cScore;
	std::shared_ptr<CLifespan> cLifespan;
	std::shared_ptr<CInput> cInput;
};
