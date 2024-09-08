#pragma once

#include <SFML/Graphics.hpp>

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
		Projectile shoot();
		const sf::FloatRect getCollisionBox() const;
		PlayerState state = PlayerState::Alive;
		unsigned int deathAnimationAccumulator = 0;
	private:
		sf::Sprite sprite;
		static constexpr float SPEED = 6.0f;
		float deadTime = 0.0f;
};
