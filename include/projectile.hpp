#pragma once
#include <SFML/Graphics.hpp>

class Projectile {
	public:
		Projectile(sf::Texture& spriteSheet);
		void move();
		sf::IntRect getCollisionBox();
	private:
		sf::Sprite sprite;
		unsigned int numFrames;
		sf::IntRect frame_locations[numFrames];
		bool fromPlayer;
};
