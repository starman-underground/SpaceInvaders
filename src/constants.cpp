#include "constants.hpp"

namespace GameConstants {
	constexpr unsigned int SCREEN_WIDTH = 1024u;
	constexpr unsigned int SCREEN_HEIGHT = 896u;
	constexpr float WALL_LEFT = 5.0f;
	constexpr float WALL_RIGHT = 1019.0f;
	
	constexpr sf::IntRect[] PLAYER_FRAMES = { sf::IntRect(1, 49, 16, 8) };
	constexpr sf::IntRect[] PLAYER_PROJECTILE_FRAMES = { sf::IntRect(55, 49, 1, 8) };
	
	constexpr sf::IntRect[] ENEMY1_FRAMES = { sf::IntRect(1, 1, 16, 8), sf::IntRect(1, 11, 16, 8) };
	constexpr sf::IntRect[] ENEMY1_PROJECTILE_FRAMES = { sf::IntRect(1, 21, 3, 8), sf::IntRect(6, 21, 3, 8), sf::IntRect(11, 21, 3, 8), sf::IntRect(16, 21, 3, 8) };
										   
	constexpr sf::IntRect[] ENEMY2_FRAMES = { sf::IntRect(19, 1, 16, 8), sf::IntRect(19, 11, 16, 8) };
	constexpr sf::IntRect[] ENEMY2_PROJECTILE_FRAMES = { sf::IntRect(21, 21, 3, 8), sf::IntRect(26, 21, 3, 8), sf::IntRect(31, 21, 3, 8), sf::IntRect(36, 21, 3, 8) };

	constexpr sf::IntRect[] ENEMY3_FRAMES = { sf::IntRect(37, 1, 16, 8), sf::IntRect(37, 11, 16, 8) };
	constexpr sf::IntRect[] ENEMY3_PROJECTILE_FRAMES = { sf::IntRect(41, 21, 3, 8), sf::IntRect(46, 21, 3, 8), sf::IntRect(51, 21, 3, 8), sf::IntRect(56, 21, 3, 8), };
										   
}
