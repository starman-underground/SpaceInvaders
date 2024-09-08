#pragma once

#include <SFML/Graphics.hpp>

#include <chrono>
#include <thread>
#include <optional>

#include "EnemyManager.hpp"
#include "Player.hpp"

using FrameDuration = std::chrono::duration<int, std::ratio<1, 60>>;
using Clock = std::chrono::steady_clock;

enum class GameState {
	Playing,
	Dying,
	Finished,
	Crashed
};

class Game {
	public:
		Game();
		int loop();

	private:
		void loadShaders();
		void shadeBackground();

		void handleInput(const sf::Event& event);
		void handleEvent(const sf::Event& event);
		
		void update();
		void updateProjectiles();
		
		void drawScore();
		void drawLives();
		void drawGUI();
		void drawGameOver();
		void render();
		
		GameState state;
		EnemyManager enemyManager;
		Player player;
		std::optional<Projectile> playerProjectile;
		std::vector<Projectile> enemyProjectiles;
		unsigned int score;
		unsigned int lives;
		sf::RenderWindow window;
		sf::Sprite background;
		sf::RectangleShape backgroundRect;

		sf::RenderTexture texBuffer1;
		sf::RenderTexture texBuffer2;

		sf::Shader vignetteShader;
		sf::Shader gaussianBlurShader;
		sf::Shader radialBlurShader;

		Clock::time_point lastTime;
		FrameDuration lag;
		unsigned int deathFrameAccumulator;
		unsigned int projectileFrameAccumulator;
};
