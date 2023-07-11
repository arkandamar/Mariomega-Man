#pragma once

#include "Scene.hpp"

class Scene_Play : public Scene
{
	struct PlayerConfig
	{
		float X, Y, CX, CY, SPEED, MAXSPEED, JUMP, GRAVITY;
		std::string WEAPON;
	};

protected:
	std::shared_ptr<Entity> m_player;
	std::string m_levelPath;
	PlayerConfig m_playerConfig;
	bool m_drawTextures = true;
	bool m_drawBoundingBox = false;
	bool m_drawGrid = false;
	sf::Text m_gridText;
	Vec2 m_gridSize = { 64, 64 };

	void loadLevel(const std::string& filename);
	void init();
	void update();
	void onEnd();

	void sDoAction(const Action& action);
	void sLifespan();
	void sCollision();
	void sAnimation();
	void sMovement();
	void sRender();

	void spawnPlayer();
	void spawnBullet(std::shared_ptr<Entity> entity);

	Vec2 gridToMidPixel(float gridX, float gridY, std::shared_ptr<Entity> entity);

public:
	Scene_Play(GameEngine* gameEngine, const std::string& levelPath);

	void doAction(const Action& action);
};