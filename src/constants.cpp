#include <stdexcept>

#include "Constants.hpp"

namespace GameConstants {

	constexpr float RATIO = 5.0;

	constexpr unsigned int SCREEN_WIDTH = 1280u;
	constexpr unsigned int SCREEN_HEIGHT = 1120u;

	constexpr float WALL_LEFT = RATIO;
	constexpr float WALL_RIGHT = SCREEN_WIDTH - RATIO;
	constexpr float WALL_BOTTOM = SCREEN_HEIGHT - RATIO;
	constexpr float WALL_TOP = 80.0f;

	sf::Texture& getSpriteSheet() {
		static sf::Texture spriteSheet;
		static bool loaded = false;
		if (!loaded) {
			if(!spriteSheet.loadFromFile("assets/SpriteSheet.png")) {
				throw std::runtime_error("Could not load sprite sheet");
			}
		}
		return spriteSheet;
	};

	const sf::Color PLAYER_COLOR = sf::Color(117, 251, 76);
	const sf::Color BONUS_ENEMY_COLOR = sf::Color(234, 51, 35);

	const sf::IntRect PLAYER_FRAMES[] { sf::IntRect(1, 49, 16, 8) };
	const sf::IntRect PLAYER_DEATH_FRAMES[] { sf::IntRect(19, 49, 16, 8), sf::IntRect(37, 49, 16, 8) };
	const sf::IntRect PLAYER_PROJECTILE_FRAMES[] { sf::IntRect(55, 49, 1, 8) };

	const sf::IntRect ENEMY1_FRAMES[] { sf::IntRect(1, 1, 16, 8), sf::IntRect(1, 11, 16, 8) };
	const sf::IntRect ENEMY1_PROJECTILE_FRAMES[] { sf::IntRect(1, 21, 3, 8), sf::IntRect(6, 21, 3, 8), sf::IntRect(11, 21, 3, 8), sf::IntRect(16, 21, 3, 8) };
		    		  			   
	const sf::IntRect ENEMY2_FRAMES[] { sf::IntRect(19, 1, 16, 8), sf::IntRect(19, 11, 16, 8) };
	const sf::IntRect ENEMY2_PROJECTILE_FRAMES[] { sf::IntRect(21, 21, 3, 8), sf::IntRect(26, 21, 3, 8), sf::IntRect(31, 21, 3, 8), sf::IntRect(36, 21, 3, 8) };

	const sf::IntRect ENEMY3_FRAMES[] { sf::IntRect(37, 1, 16, 8), sf::IntRect(37, 11, 16, 8) };
	const sf::IntRect ENEMY3_PROJECTILE_FRAMES[] { sf::IntRect(41, 21, 3, 8), sf::IntRect(46, 21, 3, 8), sf::IntRect(51, 21, 3, 8), sf::IntRect(56, 21, 3, 8), };

	const unsigned int FRAMES_PER_PROJECTILE_ANIMATION = 15;
	const unsigned int FRAMES_PER_DEATH_ANIMATION = 15;

	const unsigned int NUM_DEATH_FRAMES = 120;

	const sf::IntRect S { 21, 89, 8, 8 };
	const sf::IntRect C { 21, 69, 8, 8 };
	const sf::IntRect O { 61, 79, 8, 8 };
	const sf::IntRect R { 11, 89, 8, 8 };
	const sf::IntRect E { 41, 69, 8, 8 };

	const sf::IntRect L { 31, 79, 8, 8 };
	const sf::IntRect I { 1, 79, 8, 8 };
	const sf::IntRect V { 51, 89, 8, 8 };

	const sf::IntRect ZERO { 21, 99, 8, 8 };
	const sf::IntRect ONE { 31, 99, 8, 8 };
	const sf::IntRect TWO { 41, 99, 8, 8 };
	const sf::IntRect THREE { 51, 99, 8, 8 };
	const sf::IntRect FOUR { 61, 99, 8, 8 };
	const sf::IntRect FIVE { 71, 99, 8, 8 };
	const sf::IntRect SIX { 1, 109, 8, 8 };
	const sf::IntRect SEVEN { 11, 109, 8, 8 };
	const sf::IntRect EIGHT { 21, 109, 8, 8 };
	const sf::IntRect NINE { 31, 109, 8, 8 };
}

