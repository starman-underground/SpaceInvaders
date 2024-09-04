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
		Projectile(ProjectileType type, const sf::FloatRect& startPos, float speed);
		void move();
		void draw(sf::RenderTarget& window) const;
		sf::FloatRect getCollisionBox() const;
	private:
		sf::Sprite sprite;
		unsigned int numFrames;
		unsigned int frameIdx;
		float speed;
		ProjectileType type;
};

