#pragma once

#include "Components.hpp"

#include <memory>
#include <tuple>
#include <optional>

class EntityManager;

typedef std::tuple<
	CTransform,
	CLifespan,
	CInput,
	CBoundingBox,
	CAnimation,
	CGravity,
	CState
> ComponentTuple;

enum Tag { DefaultTag = -1, Player, Enemy, Tile, Dec, TAG_COUNT = Dec + 1 };

class Entity
{
	// make constructor private so entity cannot be created directly
	friend class EntityManager;

	size_t m_id = 0;
	Tag m_tag = DefaultTag;
	bool m_active = true;
	ComponentTuple m_components;

	Entity(const Tag tag, size_t id);

public:
	// private member access
	void destroy();
	bool isActive() const;
	const Tag getTag() const;
	const size_t getId() const;

	// component function
	template <typename T>
	T& getComponent();

	template<typename T>
	const T& getComponent() const;

	template<typename T>
	bool hasComponent() const;

	template<typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs);

	template<typename T>
	void removeComponent();
};
