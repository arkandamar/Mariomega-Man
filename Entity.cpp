#pragma once

#include "Entity.hpp"

Entity::Entity(const Tag tag, size_t id) 
	: m_tag(tag), m_id(id),
	m_components(CTransform(), CLifespan(), CInput(), CBoundingBox(), CAnimation(), CGravity(), CState()) {};

void Entity::destroy()
{
	m_active = false;
}

bool Entity::isActive() const
{
	return m_active;
}

const Tag Entity::getTag() const
{
	return m_tag;
}

const size_t Entity::getId() const
{
	return m_id;
}

template <typename T>
T& Entity::getComponent()
{
	return std::get<T>(m_components);
}

template<typename T>
const T& Entity::getComponent() const
{
	return std::get<T>(m_components);
}

template<typename T>
bool Entity::hasComponent() const
{
	return getComponent<T>().has;
}

template<typename T, typename... TArgs>
T& Entity::addComponent(TArgs&&... mArgs)
{
	auto& component = getComponent<T>();
	component = T(std::forward<TArgs>(mArgs)...);
	component.has = true;
	return component;
}

template<typename T>
void Entity::removeComponent()
{
	auto& component = getComponent<T>();
	component = T();
	component.has = false;
}