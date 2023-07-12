#pragma once

#include "Scene_Play.hpp"
#include "GameEngine.hpp"
#include "Scene_Menu.hpp"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

std::map<std::string, EnumAnimation> tableLevel =
{
	{"Ground", AniGround}, {"Brick", AniBrick}
};

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
	registerAction(sf::Keyboard::B, ShowCollision);
	registerAction(sf::Keyboard::W, Jump);
	registerAction(sf::Keyboard::D, Right);
	registerAction(sf::Keyboard::A, Left);
	registerAction(sf::Keyboard::Space, Shoot);
	registerAction(sf::Keyboard::BackSpace, Back);

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
	std::ifstream fin(filename);
	std::string temp;

	while (!fin.eof() && !fin.fail())
	{
		fin >> temp;
		if (temp == "Tile")
		{
			fin >> temp;
			std::string name = temp;

			fin >> temp;
			int fromX = std::stoi(temp);

			fin >> temp;
			int fromY = std::stoi(temp);

			fin >> temp;
			int toX = std::stoi(temp);

			fin >> temp;
			int toY = std::stoi(temp);

			auto it = tableLevel.find(name);
			if (it == tableLevel.end()) {
				// name not found
				cout << name << " not found in system" << endl;
			}
			else {
				// name found
				if (!((fromX & fromY & toX & toY) >= 0))
				{
					cout << "invalid coordinat, do not use negative value!" << endl;
				}
				else
				{
					for (int i = fromX; i <= toX; i++)
					{
						for (int j = fromY; j <= toY; j++)
						{
							auto tile = m_entityManager.addEntity(Tile);
							tile->addComponent<CAnimation>(m_game->assets().getAnimation(it->second), true);

							tile->addComponent<CTransform>(Vec2(0, 0));
							tile->getComponent<CTransform>().scale = m_gridSize / m_game->assets().getAnimation(it->second).getSize();

							tile->addComponent<CBoundingBox>(m_gridSize);

							gridToMidPixel(i, j, tile);

						}
					}
				}
			}
		}

		if (temp == "Dec")
		{
			fin >> temp;
			std::string name = temp;

			fin >> temp;
			int fromX = std::stoi(temp);

			fin >> temp;
			int fromY = std::stoi(temp);

			fin >> temp;
			int toX = std::stoi(temp);

			fin >> temp;
			int toY = std::stoi(temp);

			auto it = tableLevel.find(name);
			if (it == tableLevel.end()) {
				// name not found
				cout << name << " not found in system" << endl;
			}
			else 
			{
				// name found
				if (!((fromX & fromY & toX & toY) >= 0))
				{
					cout << "invalid coordinat, do not use negative value!" << endl;
				} 
				else
				{
					for (int i = fromX; i <= toX; i++)
					{
						for (int j = fromY; j <= toY; j++)
						{
							auto dec = m_entityManager.addEntity(Dec);
							dec->addComponent<CAnimation>(m_game->assets().getAnimation(it->second), true);
							dec->addComponent<CTransform>(Vec2(0, 0));
							dec->getComponent<CTransform>().scale = m_gridSize / m_game->assets().getAnimation(it->second).getSize();
							gridToMidPixel(i, j, dec);
						}
					}
				}
			}
		}
	}

	// spawn player when level has been loaded
	spawnPlayer();
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
			default: break;
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
	for (auto& e : m_entityManager.getEntities())
	{
		if (e->hasComponent<CTransform>() && e->hasComponent<CAnimation>())
		{
			e->getComponent<CAnimation>().animation.getSprite().setScale
			(
				e->getComponent<CTransform>().scale.x, 
				e->getComponent<CTransform>().scale.y
			);
			e->getComponent<CAnimation>().animation.getSprite().setPosition
			(
				e->getComponent<CTransform>().pos.x + e->getComponent<CTransform>().velocity.x,
				e->getComponent<CTransform>().pos.y + e->getComponent<CTransform>().velocity.y
			);
		}
	}
}

void Scene_Play::sRender()
{
	// render system
	m_game->window().clear(sf::Color(97, 133, 248));

	if (m_drawTextures)
	{
		for (auto& e : m_entityManager.getEntities())
		{
			if (e->hasComponent<CAnimation>())
			{
				m_game->window().draw(e->getComponent<CAnimation>().animation.getSprite());
			}
		}
	}

	if (m_drawBoundingBox)
	{
		for (auto& e : m_entityManager.getEntities())
		{
			if (e->hasComponent<CBoundingBox>())
			{
				sf::RectangleShape bb;
				bb.setOutlineColor(sf::Color::Red);
				bb.setFillColor(sf::Color::Transparent);
				bb.setOutlineThickness(1.2f);
				bb.setOrigin(e->getComponent<CBoundingBox>().halfSize.x, e->getComponent<CBoundingBox>().halfSize.y);
				bb.setPosition(sf::Vector2f(e->getComponent<CTransform>().pos.x, e->getComponent<CTransform>().pos.y));
				bb.setSize(sf::Vector2f(e->getComponent<CBoundingBox>().size.x, e->getComponent<CBoundingBox>().size.y));
				m_game->window().draw(bb);
			}
		}
	}

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
	auto p = m_entityManager.addEntity(Player);
	p->addComponent<CInput>();
	m_player = p;
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
	float yPixel = height() - m_gridSize.y / 2 - gridY * m_gridSize.y;
	float xPixel = m_gridSize.x / 2 + gridX * m_gridSize.x;

	// pixel position
	Vec2 pixelPos = Vec2(xPixel, yPixel);

	entity->getComponent<CTransform>().pos = pixelPos;

	return pixelPos;
}