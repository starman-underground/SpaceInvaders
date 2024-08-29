#include "player.hpp"
#include "constants.hpp"

Player::Player(const sf::Texture& spriteSheet) {
		sprite.setTexture(spriteSheet);
		sprite.setTextureRect(sprite_location);
		sprite.setScale(4.0f, 4.0f);
		sprite.setPosition((static_cast<float>(GameConstants::SCREEN_WIDTH) - sprite.getGlobalBounds().width) / 2.0, static_cast<float>(GameConstants::SCREEN_HEIGHT) - sprite.getGlobalBounds().height - 20.0f);
}

void Player::draw(sf::RenderTarget& window) {
	window.draw(sprite);
}

void Player::move() {
	if (movingLeft && !movingRight && sprite.getPosition().x > GameConstants::WALL_LEFT) {
		sprite.move(-1.0 * Player::SPEED, 0.0);
	} else if (!movingLeft && movingRight && sprite.getPosition().x + sprite.getGlobalBounds().width < GameConstants::WALL_RIGHT) {
		sprite.move(1.0 * Player::SPEED, 0.0);
	}
}
