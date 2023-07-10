#pragma once

#include "Scene.hpp"

// private member function
void Scene::setPaused(bool paused)
{
	m_paused = paused;
}

// public member function
Scene::Scene() {}

Scene::Scene(GameEngine* gameEngine) : m_game(gameEngine) {}

void Scene::simulate(const size_t frames)
{
	// simulate things
}

void Scene::registerAction(int inputKey, EnumAction actionName)
{
	// register input key -> action in m_actionMap
	m_actionMap[inputKey] = actionName;
}

size_t Scene::width() const
{
	// return window width
	return 0;
}

size_t Scene::height() const
{
	// return window height
	return 0;
}

size_t Scene::currentFrame() const
{
	return m_currentFrame;
}

bool Scene::hasEnded() const
{
	return m_hasEnded;
}

const ActionMap& Scene::getActionMap() const
{
	return m_actionMap;
}

void Scene::drawLine(const Vec2& p1, const Vec2& p2)
{
	// draw gird line
}