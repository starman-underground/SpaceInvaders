#include <SFML/Graphics.hpp>

#include <chrono>
#include <thread>

#include "Player.hpp"

using FrameDuration = std::chrono::duration<int, std::ratio<1, 60>>;
using Clock = std::chrono::steady_clock;

enum class GameState {
	Playing,
	Respawning,
	Finished,
	Crashed
};

class Game {
	public:
		Game();
		int loop();

	private:
		void update();

		void drawGUI();
		void render();
		
		void handleInput(const sf::Event& event);
		void handleEvent(const sf::Event& event);

		GameState state;
		Player player;

		sf::RenderWindow window;
		
		Clock::time_point lastTime;
		FrameDuration lag;
		unsigned int enemyLag;
};
