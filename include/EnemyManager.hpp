#pragma once

#include <SFML/Graphics.hpp>

#include <optional>

#include "Constants.hpp"
#include "Enemy.hpp"

class EnemyManager {
	public:
		EnemyManager();
		void update();
		std::vector<Projectile> shootEnemies();
		void draw(sf::RenderTarget& window);
		unsigned int checkCollision(const sf::FloatRect& projectileBox);
	private:
		
		void loadSprites();
		void placeEnemies();
		void moveEnemies();


		unsigned int frameAccumulator = 0;
		unsigned int enemyFrameIdx = 0;

		bool movingRight = true;

		static constexpr unsigned int FRAMES_PER_UPDATE = 40;
		static constexpr float HORIZONTAL_SPACE = 80.0f;
		static constexpr float VERTICAL_SPACE = 80.0f;
		
		std::vector<Enemy> enemies;

		sf::Sprite enemy1Frames[2];
		sf::Sprite enemy2Frames[2];
		sf::Sprite enemy3Frames[2];
};
