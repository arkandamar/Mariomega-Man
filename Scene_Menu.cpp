#pragma once

#include "Scene_Menu.hpp"

Scene_Menu::Scene_Menu(GameEngine* gameEngine)
	: Scene(gameEngine)
{
	init();
}

void Scene_Menu::init()
{
	// load level path to Scene_Menu
	

	// register action in menu scene
	registerAction(sf::Keyboard::A, Up);
	registerAction(sf::Keyboard::S, Down);
	registerAction(sf::Keyboard::D, Play);
	registerAction(sf::Keyboard::B, Back);
}

void Scene_Menu::update()
{
	// update frame if there're changes
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
}

void Scene_Menu::doAction(const Action& action)
{
	// doing action based on Action given and pass to system
	switch (action.actionName())
	{
	case Up:
		break;
	case Down:
		break;
	case Play:
		break;
	case Back:
		break;
	default:
		break;
	}
}