#include <SFML/Graphics.hpp>

#include <iostream>
#include <chrono>
#include <thread>

#include "Game.hpp"

int main() {

	Game game = Game();
	game.loop();

	return EXIT_SUCCESS;
}
