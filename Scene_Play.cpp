#pragma once

#include "Scene_Play.hpp"
#include "GameEngine.hpp"
#include "Scene_Menu.hpp"
#include "Physics.hpp"

#include <iostream>
#include <fstream>

using std::cout;
using std::endl;

namespace utl {
	int extractValue(const std::string& s, const std::string& del)
	{
		size_t del_pos = s.find(del);
		return stoi(s.substr(del_pos + del.size(), s.size() - del_pos));
	}

	std::string extractValueStr(const std::string& s, const std::string& del)
	{
		size_t del_pos = s.find(del);
		return s.substr(del_pos + del.size(), s.size() - del_pos);
	}
}

std::map<std::string, EnumAnimation> tableLevel =
{
	{"Ground", AniGround}, {"Brick", AniBrick}, {"BlockCoin", AniBlockCoin}, {"Block", AniBlock},
	{"BrickIns", AniBrickIns}
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
	m_gridSize = Vec2(64, 64);

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

		if (temp == "Pipe")
		{
			fin >> temp;
			int height = utl::extractValue(temp, "=");

			fin >> temp;
			int x = utl::extractValue(temp, "=");

			fin >> temp;
			int y = utl::extractValue(temp, "=");

			for (int h = y; h <= height; h++)
			{
				int width = x + 1;
				if (h < height)
				{
					for (int w = x; w <= width; w++)
					{
						EnumAnimation animationName = AniDefault;
						if (w == width)
						{
							// ani 4
							animationName = AniPipe4;
						}
						else
						{
							// ani 3
							animationName = AniPipe3;
						}
						auto p = m_entityManager.addEntity(Tile);
						p->addComponent<CAnimation>(m_game->assets().getAnimation(animationName), true);
						p->addComponent<CTransform>(Vec2(0, 0));
						p->getComponent<CTransform>().scale = m_gridSize / m_game->assets().getAnimation(animationName).getSize();
						p->addComponent<CBoundingBox>(m_gridSize);
						gridToMidPixel(w, h, p);
					}
				}
				else
				{
					for (int w = x; w <= width; w++)
					{
						EnumAnimation animationName = AniDefault;
						if (w == width)
						{
							// ani 2
							animationName = AniPipe2;
						}
						else
						{
							// ani 1
							animationName = AniPipe1;
						}
						auto p = m_entityManager.addEntity(Tile);
						p->addComponent<CAnimation>(m_game->assets().getAnimation(animationName), true);
						p->addComponent<CTransform>(Vec2(0, 0));
						p->getComponent<CTransform>().scale = m_gridSize / m_game->assets().getAnimation(animationName).getSize();
						p->addComponent<CBoundingBox>(m_gridSize);
						gridToMidPixel(w, h, p);
					}
				}
			}
		}

		if (temp == "Pole")
		{
			fin >> temp;
			int height = utl::extractValue(temp, "=");

			fin >> temp;
			int x = utl::extractValue(temp, "=");

			fin >> temp;
			int y = utl::extractValue(temp, "=");

			for (int h = y; h <= height; h++)
			{
				EnumAnimation animationName = AniDefault;
				if (h == y)
				{
					animationName = AniBlock;
				}
				else if (h == height)
				{
					animationName = AniPeak;
				}
				else 
				{
					animationName = AniPole;
				}

				auto p = m_entityManager.addEntity(Tile);
				p->addComponent<CAnimation>(m_game->assets().getAnimation(animationName), true);
				p->addComponent<CTransform>(Vec2(0, 0));
				p->getComponent<CTransform>().scale = m_gridSize / m_game->assets().getAnimation(animationName).getSize();
				p->addComponent<CBoundingBox>(m_gridSize);
				gridToMidPixel(x, h, p);
			}
		}
	}

	// spawn player when level has been loaded
	spawnPlayer();
}

void Scene_Play::update()
{
	m_entityManager.update();

	sMovement();
	sLifespan();
	sAnimation();
	sCollision();
	sRender();

	// update current frame
	m_currentFrame++;
}

void Scene_Play::onEnd()
{
	// change to default view
	m_game->window().setView(m_game->window().getDefaultView());

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
			case Jump: m_player->getComponent<CInput>().up = true; break;
			case Right: m_player->getComponent<CInput>().right = true; break;
			case Left: m_player->getComponent<CInput>().left = true; break;
			case Shoot: 
				if (m_player->getComponent<CInput>().canShoot)
				{
					spawnBullet(m_player);

					if (m_player->getComponent<CState>().state == onGround)
						m_player->getComponent<CState>().state = onShoot;

					if (m_player->getComponent<CState>().state == onAir)
						m_player->getComponent<CState>().state = onShootAir;

					m_player->getComponent<CInput>().canShoot = false; break;
				}
			default: break;
		}
	}

	if (action.actionType() == KeyRelease)
	{
		switch (action.actionName())
		{
			case Jump: m_player->getComponent<CInput>().up = false; break;
			case Right: m_player->getComponent<CInput>().right = false; break;
			case Left: m_player->getComponent<CInput>().left = false; break;
			case Shoot: 
				m_player->getComponent<CState>().state = onAir;
				m_player->getComponent<CInput>().canShoot = true; break;
			default: break;
		}
	}
}

void Scene_Play::sLifespan()
{
	// lifespan system
	for (auto& e : m_entityManager.getEntities())
	{
		if (e->hasComponent<CLifespan>())
		{
			if (e->getComponent<CLifespan>().remaining <= 0)
			{
				e->destroy();
			}
			e->getComponent<CLifespan>().remaining--;
		}
	}
}

void Scene_Play::sCollision()
{
	// collision system
	for (auto& e : m_entityManager.getEntities(Tile))
	{
		// grap animation name for checking
		EnumAnimation animatioName = e->getComponent<CAnimation>().animation.getName();

		// collision to player
		if (e->hasComponent<CBoundingBox>() && e->hasComponent<CTransform>())
		{
			Vec2 sumHalf = m_player->getComponent<CBoundingBox>().halfSize + e->getComponent<CBoundingBox>().halfSize;
			Vec2 diff = m_player->getComponent<CTransform>().pos - e->getComponent<CTransform>().pos;
			Vec2 absDiff = Vec2(abs(diff.x), abs(diff.y));

			Physics overlap;

			if (absDiff.y < sumHalf.y && absDiff.x < sumHalf.x)
			{
				if (animatioName == AniPole || animatioName == AniPeak)
				{
					gridToMidPixel(0, 3, m_player);
					break;
				}
				
				Vec2 prevSumHalf = m_player->getComponent<CBoundingBox>().halfSize + e->getComponent<CBoundingBox>().halfSize;
				Vec2 prevDiff = m_player->getComponent<CTransform>().prevPos - e->getComponent<CTransform>().prevPos;
				Vec2 absPrevDiff = Vec2(abs(prevDiff.x), abs(prevDiff.y));

				Vec2 ol = overlap.GetOverlap(m_player, e);

				if (absPrevDiff.x < prevSumHalf.x)
				{
					// when player collide from up
					if (prevDiff.y < 0)
					{
						if (m_player->getComponent<CState>().state != onShoot && m_player->getComponent<CInput>().canShoot)
							m_player->getComponent<CState>().state = onGround;

						if (m_player->getComponent<CState>().state == onShootAir)
							m_player->getComponent<CState>().state = onShoot;

						m_player->getComponent<CTransform>().pos.y -= ol.y;
						m_player->getComponent<CTransform>().velocity.y -= ol.y;
					}
					// when player collide from below
					else
					{
						if (animatioName == AniBlockCoin)
						{
							e->addComponent<CAnimation>(m_game->assets().getAnimation(AniUsedBlockCoin), true);

							auto coin = m_entityManager.addEntity(Dec);
							coin->addComponent<CAnimation>(m_game->assets().getAnimation(AniCoinArise), true);
							coin->addComponent<CTransform>(Vec2(e->getComponent<CTransform>().pos.x, e->getComponent<CTransform>().pos.y - 64));
							coin->getComponent<CTransform>().scale = m_gridSize / e->getComponent<CAnimation>().animation.getSize();
							coin->addComponent<CLifespan>(30);
						}

						if (animatioName == AniBrick || animatioName == AniBrickIns)
						{
							e->addComponent<CAnimation>(m_game->assets().getAnimation(AniExplosion), false);
							e->removeComponent<CBoundingBox>();

							m_player->getComponent<CTransform>().velocity.y = 0;
						}

						m_player->getComponent<CTransform>().pos.y += ol.y;
						m_player->getComponent<CTransform>().velocity.y += ol.y;
					}
				} 
				else if (absPrevDiff.y < prevSumHalf.y)
				{
					// when player collide from left
					if (prevDiff.x < 0)
					{
						m_player->getComponent<CTransform>().pos.x -= ol.x;
						m_player->getComponent<CTransform>().velocity.x -= ol.x;
					}

					// when player collide from right
					else
					{
						m_player->getComponent<CTransform>().pos.x += ol.x;
						m_player->getComponent<CTransform>().velocity.x += ol.x;
					}
				}
			}

			if (m_player->getComponent<CTransform>().pos.x < m_player->getComponent<CBoundingBox>().halfSize.x)
			{
				m_player->getComponent<CTransform>().pos.x = m_player->getComponent<CBoundingBox>().halfSize.x;
			}

			// collision with bullet
			for (auto& b : m_entityManager.getEntities(Bullet))
			{
				if (b->hasComponent<CBoundingBox>() && b->hasComponent<CTransform>())
				{
					Vec2 sumHalf = b->getComponent<CBoundingBox>().halfSize + e->getComponent<CBoundingBox>().halfSize;
					Vec2 diff = b->getComponent<CTransform>().pos - e->getComponent<CTransform>().pos;
					Vec2 absDiff = Vec2(abs(diff.x), abs(diff.y));

					// collision with bullet occur
					if (absDiff.x < sumHalf.x && absDiff.y < sumHalf.y)
					{
						// if bullet is getting brick entity
						if (animatioName == AniBrick || animatioName == AniBrickIns)
						{
							e->addComponent<CAnimation>(m_game->assets().getAnimation(AniExplosion), false);
							e->removeComponent<CBoundingBox>();
						}

						// destroyed bullet animation
						b->getComponent<CTransform>().velocity = Vec2(0, 0);
						b->addComponent<CAnimation>(m_game->assets().getAnimation(AniSplash), false);
						b->removeComponent<CBoundingBox>();
					}
				}
			}
		}
	}

	// if player fall, go back to start
	if (m_player->getComponent<CTransform>().pos.y > height() - m_player->getComponent<CBoundingBox>().halfSize.y)
	{
		gridToMidPixel(0, 3, m_player);
	}
}

void Scene_Play::sAnimation()
{
	// animation system
	for (auto& e : m_entityManager.getEntities())
	{
		if (e->hasComponent<CAnimation>())
		{
			if (e->getComponent<CAnimation>().animation.hasEnded())
			{
				e->destroy();
			}

			e->getComponent<CAnimation>().animation.update();
		}
	}

	EnumAnimation animationName = m_player->getComponent<CAnimation>().animation.getName();

	switch (m_player->getComponent<CState>().state)
	{
	case onAir: 
		if (animationName != AniJump)
			m_player->addComponent<CAnimation>(m_game->assets().getAnimation(AniJump), true);
		break;

	case onGround:
		if (animationName != AniStand)
			m_player->addComponent<CAnimation>(m_game->assets().getAnimation(AniStand), true);
		break;

	case onWalk:
		if (animationName != AniWalk)
			m_player->addComponent<CAnimation>(m_game->assets().getAnimation(AniWalk), true);
		break;

	case onShoot:
		if (animationName != AniShoot)
			m_player->addComponent<CAnimation>(m_game->assets().getAnimation(AniShoot), true);
		break;

	case onShootAir:
		if (animationName != AniShootAir)
			m_player->addComponent<CAnimation>(m_game->assets().getAnimation(AniShootAir), true);
		break;

	case onShootWalk:
		if (animationName != AniShootWalk)
			m_player->addComponent<CAnimation>(m_game->assets().getAnimation(AniShootWalk), true);
		break;

	default:
		break;
	}
}

void Scene_Play::sMovement()
{
	// movement system
	for (auto& e : m_entityManager.getEntities())
	{
		if (e->hasComponent<CTransform>() && e->hasComponent<CAnimation>())
		{
			if (e->hasComponent<CGravity>())
			{
				e->getComponent<CTransform>().velocity.y += e->getComponent<CGravity>().accel;
			}

			e->getComponent<CAnimation>().animation.getSprite().setScale
			(
				e->getComponent<CTransform>().scale.x, 
				e->getComponent<CTransform>().scale.y
			);

			e->getComponent<CTransform>().prevPos = e->getComponent<CTransform>().pos;

			e->getComponent<CAnimation>().animation.getSprite().setPosition
			(
				e->getComponent<CTransform>().pos.x += e->getComponent<CTransform>().velocity.x,
				e->getComponent<CTransform>().pos.y += e->getComponent<CTransform>().velocity.y
			);
		}
	}

	if (m_player->getComponent<CInput>().up && (m_player->getComponent<CState>().state == onGround))
	{
		m_player->getComponent<CState>().state = onAir;
		m_player->getComponent<CTransform>().velocity.y -= 8;
	}

	if (!m_player->getComponent<CInput>().right && !m_player->getComponent<CInput>().left)
	{
		m_player->getComponent<CTransform>().velocity.x = 0;
	} 
	else
	{
		if (m_player->getComponent<CState>().state == onShoot)
			m_player->getComponent<CState>().state = onShootWalk;

		if (m_player->getComponent<CState>().state == onGround)
			m_player->getComponent<CState>().state = onWalk;

		if (m_player->getComponent<CInput>().right && m_player->getComponent<CTransform>().velocity.x < 10)
		{
			m_player->getComponent<CTransform>().velocity.x += 1;

			if (m_player->getComponent<CTransform>().scale.x > 0)
			{
				m_player->getComponent<CTransform>().scale.x *= -1;
			}
		}

		if (m_player->getComponent<CInput>().left && m_player->getComponent<CTransform>().velocity.x > -10)
		{
			m_player->getComponent<CTransform>().velocity.x -= 1;

			if (m_player->getComponent<CTransform>().scale.x < 0)
			{
				m_player->getComponent<CTransform>().scale.x *= -1;
			}
		}
	}
}

void Scene_Play::sRender()
{
	// set viewport if window far enough right
	auto& pPos = m_player->getComponent<CTransform>().pos;
	float windowCenterX = std::max(m_game->window().getSize().x / 2.0f, pPos.x);
	sf::View view = m_game->window().getView();
	view.setCenter(windowCenterX, m_game->window().getSize().y - view.getCenter().y);
	m_game->window().setView(view);

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
		float leftX = m_game->window().getView().getCenter().x - (float) width() / 2;
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

	// add animation
	p->addComponent<CAnimation>(m_game->assets().getAnimation(AniStand), true);

	// add transform
	p->addComponent<CTransform>(Vec2(0, 0));
	p->getComponent<CTransform>().scale = m_gridSize / m_game->assets().getAnimation(AniStand).getSize();
	p->getComponent<CTransform>().velocity = Vec2(0, 1);

	// add bounding box
	p->addComponent<CBoundingBox>(Vec2(56, 64));

	// add gravity
	p->addComponent<CGravity>(0.5f);

	// add input
	p->addComponent<CInput>();

	// add state
	p->addComponent<CState>(onAir);

	// rotate
	p->getComponent<CTransform>().scale.x *= -1;

	gridToMidPixel(0, 3, p);
	m_player = p;
}

void Scene_Play::spawnBullet(std::shared_ptr<Entity> entity)
{
	// spawn bullet
	auto b = m_entityManager.addEntity(Bullet);

	// add animation
	b->addComponent<CAnimation>(m_game->assets().getAnimation(AniBullet), true);

	// add transform
	b->addComponent<CTransform>(Vec2(entity->getComponent<CTransform>().pos.x + entity->getComponent<CBoundingBox>().halfSize.x, entity->getComponent<CTransform>().pos.y));

	// add velocity
	b->getComponent<CTransform>().velocity = Vec2(15, 0);

	// add scale
	b->getComponent<CTransform>().scale = m_gridSize / m_game->assets().getAnimation(AniBullet).getSize();

	// change velocity based on entity scale
	if (entity->getComponent<CTransform>().scale.x > 0) b->getComponent<CTransform>().velocity.x *= -1;

	// add bounding box
	b->addComponent<CBoundingBox>(Vec2(32, 32));

	// add lifespan
	b->addComponent<CLifespan>(60);
}

void Scene_Play::doAction(const Action& action)
{
	// do action
	sDoAction(action);
}

Vec2 Scene_Play::gridToMidPixel(int gridX, int gridY, std::shared_ptr<Entity> entity)
{
	// convert grid to pixel
	float yPixel = height() - m_gridSize.y / 2 - gridY * m_gridSize.y;
	float xPixel = m_gridSize.x / 2 + gridX * m_gridSize.x;

	// pixel position
	Vec2 pixelPos = Vec2(xPixel, yPixel);

	entity->getComponent<CTransform>().pos = pixelPos;

	return pixelPos;
}