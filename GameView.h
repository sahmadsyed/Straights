#include "GameController.h"

class GameController;

class GameView {
public:
	GameView(int = 0);
	~GameView();
	void start();
	void invitePlayers();
	void startRound();
	void humanMove();
	void pcMove();
private:
	GameController* controller;
};
