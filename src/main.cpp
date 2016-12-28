//https://semidtor.wordpress.com/2013/03/29/rapidxml-mini-tutorial/

#include "Game\Game.h"
#include <iostream>

const sf::Vector2i& getSize()
{
	return sf::Vector2i(5, 5);
}

int main()
{
	Game game;
	while (game.isRunning())
	{
		game.update();
		game.draw();
		game.lateUpdate();
	}

	const sf::Vector2i size = getSize();

	std::cout << size.x << "\n";
	std::cout << size.y << "\n";

	char c;
	std::cin >> c;

	return 0;
}