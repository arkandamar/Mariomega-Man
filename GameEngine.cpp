#pragma once

#include "GameEngine.hpp"
#include "Utils.hpp"

#include <fstream>
#include <iostream>

using std::cout;
using std::endl;

static std::map<std::string, EnumFont> const fontTable = { {"Mario", EnumFont::FontMario}, {"Megaman", EnumFont::FontMegaman} };
static std::map<std::string, EnumTexture> const textureTable =
{
	{"TexBlock", EnumTexture::TexBlock}, {"TexCloud", EnumTexture::TextCloud}, {"TexBlockCoin", EnumTexture::TexBlockCoin},
	{"TexCoinObtain", EnumTexture::TexCoinObtain}, {"TexCoinArise", EnumTexture::TexCoinArise},
	{"TexPipeScenery", EnumTexture::TexPipeScenery}, {"TexMegaman", EnumTexture::TexMegaman}, {"TexMegamanShoot", EnumTexture::TexMegamanShoot}
};

GameEngine::GameEngine(const std::string& path)
{
	init(path);
}

void GameEngine::init(const std::string& path)
{
	std::ifstream fin(path);
	std::string temp;

	while (!fin.eof())
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
			}
		}
	}
}

void GameEngine::run()
{
	while (isRunning())
	{
		sUserInput();
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

const Assets& GameEngine::assets() const
{
	return m_assets;
}

bool GameEngine::isRunning()
{
	return m_running && m_window.isOpen();
}