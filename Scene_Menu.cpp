#pragma once

#include "Scene_Menu.hpp"
#include "GameEngine.hpp"

#include <iostream>

Scene_Menu::Scene_Menu(GameEngine* gameEngine)
	: Scene(gameEngine)
{
	init();
}

void Scene_Menu::init()
{
	// load level path to Scene_Menu
	

	// register action in menu scene
	registerAction(sf::Keyboard::W, Up);
	registerAction(sf::Keyboard::S, Down);
	registerAction(sf::Keyboard::D, Play);
	registerAction(sf::Keyboard::B, Back);

	// set text used in scene
	m_menuText.setCharacterSize(24);
	m_menuText.setFont(m_game->assets().getFont(FontMario));
}

void Scene_Menu::update()
{
	// update frame if there're changes
	sRender();
	m_currentFrame++;
}

void Scene_Menu::onEnd()
{
	// if menu has ended
}

void Scene_Menu::sDoAction(const Action& action)
{
	// do action system
}

void Scene_Menu::sRender()
{
	// rendering system
	m_game->window().clear(sf::Color(97, 133, 248));
	m_menuText.setString("Megamario-Man");
	m_game->window().draw(m_menuText);
	m_game->window().display();
}

void Scene_Menu::doAction(const Action& action)
{
	// doing action based on Action given and pass to system
	if (action.actionType() == KeyPress)
	{
		switch (action.actionName())
		{
		case Up:
			std::cout << "up pressed" << std::endl;
			break;
		case Down:
			std::cout << "down pressed" << std::endl;
			break;
		case Play:
			std::cout << "play pressed" << std::endl;
			break;
		case Back:
			std::cout << "back pressed" << std::endl;
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