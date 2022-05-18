#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include "../engine/AbstractGame.h"
#include "../engine/custom/MyEngineSystem.h"
#include "../engine/AudioEngine.h"


struct GameKey {
	Point2 pos;
	bool isAlive;
};

class MyGame : public AbstractGame {
	private:
		MyEngineSystem myEngineSystem;

		Vector2i velocity;

		std::vector<std::shared_ptr<GameKey>> gameKeys;

		/* GAMEPLAY */
		int score;
		bool gameWin;

		void handleKeyEvents();
		void update();
		void render();
		void renderUI();

		Player* player;

		bool portalFail;

		bool easterEgg;

		Mix_Chunk* deathSound;

		bool deathSoundCheck;

	public:
        MyGame();
		~MyGame();
};

#endif