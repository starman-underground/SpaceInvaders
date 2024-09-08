#pragma once

#include <SFML/Graphics.hpp>


enum class ProjectileType {
	Player,
	Enemy1,
	Enemy2,
	Enemy3
};

class Projectile {
	public:
		Projectile(ProjectileType type, const sf::FloatRect& startPos);

		void update();
		void move();
		void draw(sf::RenderTarget& window) const;
		bool outOfBounds() const;
		sf::FloatRect getCollisionBox() const;

	private:
		void updateSprite();
	
		sf::Sprite sprite;
		unsigned int numFrames;
		unsigned int frameIdx;
		static constexpr float SPEED = 6.0f;
		ProjectileType type;
};

