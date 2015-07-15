#include "GameController.h"

class GameController;

class GameView : public Observer{
public:
	GameView(int = 0);
	~GameView();
	void start();
	void invitePlayers();
	void startRound();
	void humanMove();
	void pcMove();
	void update(); //TO-DO
private:
	GameController* controller;
	std::vector<Player*>* players;
	std::map<Suit, std::map<Rank, Card*>* >* table_cards; 
};
