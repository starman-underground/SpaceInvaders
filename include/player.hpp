#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>

#include "Projectile.hpp"

enum class PlayerState {
	Alive,
	Dead
};

class Player {
	public:

		unsigned int movingLeft = 0;
		unsigned int movingRight = 0;


		Player();
		void draw(sf::RenderTarget& window);
		void update();
		void shoot();
		
	private:
		sf::Sprite sprite;
		static constexpr float SPEED = 6.0f;
		static constexpr float PROJECTILE_SPEED = 6.0f;
		float deadTime = 0.0f;
		PlayerState state = PlayerState::Alive;
		std::optional<Projectile> projectile;	
};
