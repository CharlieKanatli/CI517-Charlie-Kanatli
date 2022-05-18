#ifndef __PLAYER_H__
#define __PLAYER_H__

#include "../engine/AbstractGame.h"
#include "../engine/custom/Entity.h"

class Player :public Entity {
public:
	Player();
	~Player();
	virtual void handleKeyEvents()override;
	virtual void update()override;

	void setScore(int score) { this->score = score; };
	int getScore() { return score; };

	void setFailPortal(bool failPortal) { this->failPortal = failPortal; };
	bool getFailPortal() { return failPortal; };

	void setGameWin(bool gameWin) { this->gameWin = gameWin; };
	bool getGameWin() { return gameWin; };

	void setEasterEgg(bool easterEgg) { this->easterEgg = easterEgg; };
	bool getEasterEgg() { return easterEgg; };

protected:
	int score;
	bool failPortal;
	bool gameWin;
	bool easterEgg;
	Mix_Chunk* coinSound;
};
#endif