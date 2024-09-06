#include <SFML/Graphics.hpp>

#include "Projectile.hpp"
#include "Constants.hpp"

Projectile::Projectile(ProjectileType type, const sf::FloatRect& playerPos, float speed) : speed{speed}, type{type} {
	switch(type) {
		case ProjectileType::Player:
			numFrames = 1;
			frameIdx = 0;
			sprite = sf::Sprite(GameConstants::getSpriteSheet(), GameConstants::PLAYER_PROJECTILE_FRAMES[frameIdx]);
			sprite.setPosition(playerPos.left + playerPos.width / 2.0f, playerPos.top - GameConstants::PLAYER_PROJECTILE_FRAMES[frameIdx].height);
			sprite.setScale(4.0f, 4.0f);
	};
}

void Projectile::draw(sf::RenderTarget& window) const {
	window.draw(sprite);
}

void Projectile::move() {
	if (type == ProjectileType::Player) {
		sprite.move(0.0f, -1.0f * speed);	
	} else {
		sprite.move(0.0f, 1.0f * speed);
	}
}

sf::FloatRect Projectile::getCollisionBox() const {
	return sprite.getGlobalBounds();
}
