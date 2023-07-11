#pragma once

#include "Scene_Play.hpp"
#include "GameEngine.hpp"
#include "Scene_Menu.hpp"

#include <iostream>

using std::cout;
using std::endl;

Scene_Play::Scene_Play(GameEngine* gameEngine, const std::string& levelPath)
	: Scene(gameEngine), m_levelPath(levelPath)
{
	init();
}

void Scene_Play::init()
{
	// register all game action in menu
	registerAction(sf::Keyboard::T, ShowTexture);
	registerAction(sf::Keyboard::G, ShowGrid);
	registerAction(sf::Keyboard::C, ShowCollision);
	registerAction(sf::Keyboard::W, Jump);
	registerAction(sf::Keyboard::D, Right);
	registerAction(sf::Keyboard::A, Left);
	registerAction(sf::Keyboard::Space, Shoot);
	registerAction(sf::Keyboard::Backspace, Back);

	m_gridText.setCharacterSize(12);
	m_gridText.setFont(m_game->assets().getFont(FontRoboto));

	// load level config
	loadLevel(m_levelPath);
}

void Scene_Play::loadLevel(const std::string& filename)
{
	// reset the entity manager every time level loaded
	m_entityManager = EntityManager();

	// load level from level config file

	// spawn player when file loaded
	spawnPlayer();

	// sample entities
	auto brick = m_entityManager.addEntity(Tile);
}

void Scene_Play::update()
{
	m_entityManager.update();

	sLifespan();
	sCollision();
	sAnimation();
	sMovement();
	sRender();

	// update current frame
	m_currentFrame++;
}

void Scene_Play::onEnd()
{
	// change scene to scene menu when end
	m_game->changeScene(MenuScene, std::make_shared<Scene_Menu>(m_game), true);
}

void Scene_Play::sDoAction(const Action& action)
{
	// action system
	if (action.actionType() == KeyPress)
	{
		switch (action.actionName())
		{
		case Back: onEnd(); break;
		case ShowTexture: m_drawTextures = !m_drawTextures; break;
		case ShowGrid: m_drawGrid = !m_drawGrid; break;
		case ShowCollision: m_drawBoundingBox = !m_drawBoundingBox; break;
		default:
			break;
		}
	}
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
	m_game->window().clear(sf::Color(97, 133, 248));

	if (m_drawGrid)
	{
		float leftX = m_game->window().getView().getCenter().x - width() / 2;
		float rightX = leftX + width() + m_gridSize.x;
		float nextGridX = leftX - ((int)leftX % (int)m_gridSize.x);
		
		for (float x = nextGridX; x < rightX; x += m_gridSize.x)
		{
			drawLine(Vec2(x, 0), Vec2(x, (float) height()));
		}

		for (float y = 0; y < height(); y += m_gridSize.y)
		{
			drawLine(Vec2(leftX, height() - y), Vec2(rightX, height() - y));

			for (float x = nextGridX; x < rightX; x += m_gridSize.x)
			{
				std::string xCell = std::to_string((int)x / (int)m_gridSize.x);
				std::string yCell = std::to_string((int)y / (int)m_gridSize.y);
				m_gridText.setString("(" + xCell + "," + yCell + ")");
				m_gridText.setPosition(
					x + (m_gridSize.x / 2) - (m_gridText.getLocalBounds().width / 2), 
					height() - y - m_gridSize.y + 8);
				m_game->window().draw(m_gridText);
			}
		}
	}

	m_game->window().display();
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
	sDoAction(action);
}

Vec2 Scene_Play::gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity)
{
	// convert grid to pixel
	return Vec2(0.0f, 0.0f);
}