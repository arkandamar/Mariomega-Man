#include "GameEngine.hpp"
#include "Scene_Menu.hpp"

int main(int argc, char* argv[])
{
	GameEngine game("config.txt");
	game.changeScene(MenuScene, std::make_shared<Scene_Menu>(&game), true);
	game.run();

	return 0;
}