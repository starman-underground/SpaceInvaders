#pragma once
#include <SFML/Graphics.hpp>

class Player {
	public:

		bool movingLeft = false;
		bool movingRight = false;


		Player(const sf::Texture& spriteSheet);
		void draw(sf::RenderTarget& window);
		void move();
		
	private:
		sf::Sprite sprite;
		const sf::IntRect sprite_location = sf::IntRect(1, 49, 16, 8);
		static constexpr float SPEED = 2.0f;
};
