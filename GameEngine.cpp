#pragma once

#include "GameEngine.hpp"
#include "Utils.hpp"

#include <fstream>
#include <iostream>

using std::cout;
using std::endl;

// map the string value when reading config.txt to enum defining assets
static std::map<std::string, EnumFont> const fontTable = 
{ 
	{"Mario", EnumFont::FontMario}, {"Megaman", EnumFont::FontMegaman}, { "Roboto", EnumFont::FontRoboto }
};
static std::map<std::string, EnumTexture> const textureTable =
{
	{"TexBlock", EnumTexture::TexBlock}, {"TexCloud", EnumTexture::TextCloud}, {"TexBlockCoin", EnumTexture::TexBlockCoin},
	{"TexCoinObtain", EnumTexture::TexCoinObtain}, {"TexCoinArise", EnumTexture::TexCoinArise}, {"TexExplosion", EnumTexture::TexExplosion},
	{"TexPipeScenery", EnumTexture::TexPipeScenery}, {"TexMegaman", EnumTexture::TexMegaman}, {"TexMegamanShoot", EnumTexture::TexMegamanShoot}
};

static std::map<std::string, EnumAnimation> const animTable =
{
	{"AniGround", EnumAnimation::AniGround}, {"AniBrick", EnumAnimation::AniBrick},
	{"AniBlockCoin", EnumAnimation::AniBlockCoin}, {"AniStand", EnumAnimation::AniStand},
	{"AniWalk", EnumAnimation::AniWalk}, {"AniJump", EnumAnimation::AniJump},
	{"AniShoot", EnumAnimation::AniShoot}, {"AniShootWalk", EnumAnimation::AniShootWalk},
	{"AniShootAir", EnumAnimation::AniShootAir}, {"AniBullet", EnumAnimation::AniBullet},
	{"AniExplosion", EnumAnimation::AniExplosion}, {"AniCoinArise", EnumAnimation::AniCoinArise},
};

GameEngine::GameEngine(const std::string& path)
{
	init(path);
}

void GameEngine::init(const std::string& path)
{
	std::ifstream fin(path);
	std::string temp;

	while (!fin.eof() && !fin.fail())
	{
		// read init config.txt
		fin >> temp;
		if (temp == "Window")
		{
			fin >> temp;
			int width = utils::extractValue(temp, "=");

			fin >> temp;
			int height = utils::extractValue(temp, "=");

			fin >> temp;
			bool fullscreen = utils::extractValue(temp, "=");

			fin >> temp;
			int frame = utils::extractValue(temp, "=");

			if (fullscreen)
			{
				m_window.create(sf::VideoMode(width, height), "Megamario-Man", sf::Style::Fullscreen);
			}
			else
			{
				m_window.create(sf::VideoMode(width, height), "Megamario-Man");
			}

			m_window.setFramerateLimit(frame);
		}

		if (temp == "Font")
		{
			fin >> temp;
			std::string name = utils::extractValueStr(temp, "=");

			fin >> temp;
			std::string path = utils::extractValueStr(temp, "=");

			auto it = fontTable.find(name);
			if (it == fontTable.end()) {
				// font not found
				cout << name << " not found in system" << endl;
			}
			else {
				// font found
				m_assets.addFont(it->second, path);
				cout << path << " loaded" << endl;
			}
		}

		if (temp == "Texture")
		{
			fin >> temp;
			std::string name = utils::extractValueStr(temp, "=");

			fin >> temp;
			std::string path = utils::extractValueStr(temp, "=");

			auto it = textureTable.find(name);
			if (it == textureTable.end()) {
				// font not found
				cout << name << " not found in system" << endl;
			}
			else {
				// font found
				m_assets.addTexture(it->second, path);
				cout << path << " loaded" << endl;
			}
		}

		if (temp == "Animation")
		{
			fin >> temp;
			std::string name = utils::extractValueStr(temp, "=");

			fin >> temp;
			std::string texture = utils::extractValueStr(temp, "=");

			fin >> temp;
			int frameCout = utils::extractValue(temp, "=");

			fin >> temp;
			int duration = utils::extractValue(temp, "=");

			auto it = animTable.find(name);
			if (it == animTable.end()) {
				// ani not found
				cout << name << " not found in system" << endl;
			}
			else {
				// ani found
				auto ut = textureTable.find(texture);
				if (ut == textureTable.end())
				{
					// ani texture not found
					cout << "cannot find texture associated with " << texture << endl;
				}
				else {
					// register animation to texture
					m_assets.registerAnimation(it->second, ut->second, frameCout, duration, Vec2(16, 16));
					cout << name << " loaded" << endl;
				}
			}
		}
	}

	// init animation
	m_assets.getAnimation(AniBrick).setIntRect(17, 0);
	m_assets.getAnimation(AniGround).setIntRect(0, 0);
	m_assets.getAnimation(AniStand).setIntRect(3, 22, 21, 23);
	m_assets.getAnimation(AniWalk).setIntRect(92, 21, 24, 24);
	m_assets.getAnimation(AniJump).setIntRect(177, 13, 26, 30);
	m_assets.getAnimation(AniShoot).setIntRect(1, 78, 31, 24);
	m_assets.getAnimation(AniShootAir).setIntRect(141, 70, 30, 30);
	m_assets.getAnimation(AniShootWalk).setIntRect(38, 78, 30, 24);
	m_assets.getAnimation(AniBullet).setIntRect(0, 0, 24, 24);
	m_assets.getAnimation(AniExplosion).setIntRect(0, 0, 16, 16);
	m_assets.getAnimation(AniCoinArise).setIntRect(0, 0, 8, 16);

	// register dead animation seperately
	m_assets.registerAnimation(AniSplash, TexMegamanShoot, 1, 5, Vec2(24, 24));
	m_assets.getAnimation(AniSplash).setIntRect(144, 0);
	m_assets.registerAnimation(AniUsedBlockCoin, TexBlockCoin, 1, 0, Vec2(16, 16));
	m_assets.getAnimation(AniUsedBlockCoin).setIntRect(48, 0);
}

void GameEngine::run()
{
	while (isRunning())
	{
		sUserInput();
		update();
	}
}

void GameEngine::sUserInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			quit();
		}

		if (event.type == sf::Event::KeyPressed || event.type == sf::Event::KeyReleased)
		{
			// check if key code is registered in key name enum
			if (currentScene()->getActionMap().find(event.key.code) == currentScene()->getActionMap().end()) { continue; }

			// determine whether key type is press or release
			EnumKeyType key_type = (event.type == sf::Event::KeyPressed) ? KeyPress : KeyRelease;

			// compute the action based on action name and key type then pass to the scene
			currentScene()->doAction(Action(currentScene()->getActionMap().at(event.key.code), key_type));
		}
	}
}

// updating previous game state 
void GameEngine::update()
{
	currentScene()->update();
}

std::shared_ptr<Scene> GameEngine::currentScene()
{
	return m_sceneArr[m_currentScene];
}

void GameEngine::changeScene(EnumScene sceneName, std::shared_ptr<Scene> scene, bool endCurrentScene)
{
	m_sceneArr[sceneName] = scene;

	if (endCurrentScene) m_currentScene = sceneName;
}

void GameEngine::quit()
{
	m_running = false;
}

sf::RenderWindow& GameEngine::window()
{
	return m_window;
}

Assets& GameEngine::assets()
{
	return m_assets;
}

const Assets& GameEngine::assets() const
{
	return m_assets;
}

bool GameEngine::isRunning()
{
	return m_running && m_window.isOpen();
}