#pragma once

#include "Scene_Play.hpp"

Scene_Play::Scene_Play(GameEngine* gameEngine, const std::string& levelPath)
	: Scene(gameEngine), m_levelPath(levelPath)
{
	init();
}

void Scene_Play::init()
{
	registerAction(sf::Keyboard::W, Jump);
	registerAction(sf::Keyboard::D, Right);
	registerAction(sf::Keyboard::A, Left);
	registerAction(sf::Keyboard::Space, Shoot);

	loadLevel(m_levelPath);
}

void Scene_Play::loadLevel(const std::string& filename)
{
	// load level from level config file
}

void Scene_Play::update()
{
	// update current frame
	m_currentFrame++;
}

void Scene_Play::onEnd()
{
	// do something when scene end
}

void Scene_Play::sDoAction(const Action& action)
{
	// action system
}

void Scene_Play::sLifespan()
{
	// lifespan system
}

void Scene_Play::sCollision()
{
	// collision system
}

void Scene_Play::sAnimation()
{
	// animation system
}

void Scene_Play::sMovement()
{
	// movement system
}

void Scene_Play::sRender()
{
	// render system
}

void Scene_Play::spawnPlayer()
{
	// spawn player
}

void Scene_Play::spawnBullet(std::shared_ptr<Entity> entity)
{
	// spawn bullet
}

void Scene_Play::doAction(const Action& action)
{
	// do action
}

Vec2 Scene_Play::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
	// convert grid to pixel
	return Vec2(0.0f, 0.0f);
}