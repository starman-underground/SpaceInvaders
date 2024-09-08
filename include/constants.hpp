#pragma once

#include <SFML/Graphics.hpp>

namespace GameConstants {

	extern const float RATIO;	

	extern const unsigned int SCREEN_WIDTH;
	extern const unsigned int SCREEN_HEIGHT;

	extern const float WALL_LEFT;
	extern const float WALL_RIGHT;

	extern const float WALL_TOP;
	extern const float WALL_BOTTOM;

	extern sf::Texture& getSpriteSheet();

	extern const sf::Color PLAYER_COLOR;
	extern const sf::Color BONUS_ENEMY_COLOR;

	extern const sf::IntRect PLAYER_FRAMES[];
	extern const sf::IntRect PLAYER_DEATH_FRAMES[];
	extern const sf::IntRect PLAYER_PROJECTILE_FRAMES[];
	
	extern const sf::IntRect ENEMY1_FRAMES[];
	extern const sf::IntRect ENEMY1_PROJECTILE_FRAMES[];

	extern const sf::IntRect ENEMY2_FRAMES[];
	extern const sf::IntRect ENEMY2_PROJECTILE_FRAMES[];

	extern const sf::IntRect ENEMY3_FRAMES[];
	extern const sf::IntRect ENEMY3_PROJECTILE_FRAMES[];

	extern const sf::IntRect ENEMY4_FRAMES[];
	extern const sf::IntRect ENEMY4_PROJECTILE_FRAMES[];

	extern const unsigned int FRAMES_PER_PROJECTILE_ANIMATION;
	extern const unsigned int FRAMES_PER_DEATH_ANIMATION;
	extern const unsigned int NUM_DEATH_FRAMES;

	extern const sf::IntRect S;
	extern const sf::IntRect C;
	extern const sf::IntRect O;
	extern const sf::IntRect R;
	extern const sf::IntRect E;

	extern const sf::IntRect L;
	extern const sf::IntRect I;
	extern const sf::IntRect V;

	extern const sf::IntRect ZERO;
	extern const sf::IntRect ONE;
	extern const sf::IntRect TWO;
	extern const sf::IntRect THREE;
	extern const sf::IntRect FOUR;
	extern const sf::IntRect FIVE;
	extern const sf::IntRect SIX;
	extern const sf::IntRect SEVEN;
	extern const sf::IntRect EIGHT;
	extern const sf::IntRect NINE;
}
