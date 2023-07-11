#pragma once

#include "Scene_Menu.hpp"
#include "GameEngine.hpp"
#include "Scene_Play.hpp"

#include <iostream>

using std::cout;
using std::endl;

enum EnumString { StrTitle, StrLevel = 1 };

Scene_Menu::Scene_Menu(GameEngine* gameEngine)
	: Scene(gameEngine)
{
	init();
}

void Scene_Menu::init()
{
	std::string baseName = "level";
	std::string extension = ".txt";
	int numFiles = 3; // Number of files to read

	for (int i = 1; i <= numFiles; i++) {
		std::string fileName = baseName + std::to_string(i) + extension;
		m_levelPaths.push_back(fileName);
		m_menuStrings.push_back("Level " + std::to_string(i));
	}

	// set title
	m_title = "Megamario-Man";

	// set text used in scene
	m_menuText.setFont(m_game->assets().getFont(FontMegaman));

	// register action in menu scene
	registerAction(sf::Keyboard::W, Up);
	registerAction(sf::Keyboard::S, Down);
	registerAction(sf::Keyboard::D, Play);
	registerAction(sf::Keyboard::B, Back);
}

void Scene_Menu::update()
{
	// update frame if there're changes
	sRender();
	m_currentFrame++;
}

void Scene_Menu::onEnd()
{
	// if menu has ended do this
	m_game->window().close();
}

void Scene_Menu::sDoAction(const Action& action)
{
	// do action system
	// doing action based on Action given and pass to system
	if (action.actionType() == KeyPress)
	{
		switch (action.actionName())
		{
		case Up:
			(m_selectedMenuIndex > 0)? m_selectedMenuIndex-- : m_selectedMenuIndex = m_menuStrings.size() - 1;
			break;
		case Down:
			(m_selectedMenuIndex < m_menuStrings.size() - 1) ? m_selectedMenuIndex++ : m_selectedMenuIndex = 0;
			break;
		case Play:
			m_game->changeScene(PlayScene, std::make_shared<Scene_Play>
				(m_game, m_levelPaths.at(m_selectedMenuIndex)), true);
			break;
		case Back:
			onEnd();
			break;
		default:
			break;
		}
	}

	if (action.actionType() == KeyRelease)
	{
		switch (action.actionName())
		{
		case Up: 
			std::cout << "up release" << std::endl; 
			break;
		case Down: 
			std::cout << "down release" << std::endl; 
			break;
		case Play:
			std::cout << "play release" << std::endl;
			break;
		case Back:
			std::cout << "back release" << std::endl;
			break;
		default:
			break;
		}
	}
}

void Scene_Menu::sRender()
{
	int padding = 75;

	// rendering system
	m_game->window().clear(sf::Color(97, 133, 248));

	m_menuText.setString(m_title);
	m_menuText.setCharacterSize(38);
	m_menuText.setPosition(m_game->window().getSize().x / 2 - m_menuText.getLocalBounds().width / 2, (float) padding);
	m_menuText.setFillColor(sf::Color(255, 255, 255));
	m_game->window().draw(m_menuText);

	int i = 1;
	int space = 100;
	for (auto& s : m_menuStrings)
	{
		m_menuText.setString(s);
		if (i - 1 == m_selectedMenuIndex)
		{
			m_menuText.setFillColor(sf::Color(0, 0, 0));
			m_menuText.setCharacterSize(34);
		}
		else 
		{
			m_menuText.setFillColor(sf::Color(255, 255, 255)) ;
			m_menuText.setCharacterSize(30);
		}
		m_menuText.setPosition(m_game->window().getSize().x / 2 - m_menuText.getLocalBounds().width / 2, (float) ++i * space);
		m_game->window().draw(m_menuText);
	}

	m_menuText.setString("Up : W\tDown : S\tPlay : D\tBack : B");
	m_menuText.setCharacterSize(20);
	m_menuText.setPosition(
		m_game->window().getSize().x / 2 - m_menuText.getLocalBounds().width / 2, 
		(float) m_game->window().getSize().y - (float)(padding + m_menuText.getLocalBounds().height));
	m_menuText.setFillColor(sf::Color(255, 255, 255)) ;
	m_game->window().draw(m_menuText);

	m_game->window().display();
}

void Scene_Menu::doAction(const Action& action)
{
	sDoAction(action);
}