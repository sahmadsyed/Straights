#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <vector>
#include <string>
#include <map>
#include "Card.h"
#include "Player.h"
#include "TableCards.h"

class GameController {
public:
	GameController(std::vector<Player*>*&, TableCards*&, int = 0);
	~GameController();
	void addPlayer(std::string);
	void deal();
	void newMove();
	void processLegalPlays();
	void quit() const;
	bool emptyDeck();
	void endOfRound();
	bool humanCheck() const;
	void pcTurn();
	void rageQuit();
	int getCurrentTurn();
	void select(Card);
	std::string getRank(int);
	std::string getSuit(int);
protected:
	void shuffle();
	Card* findCard(Suit, Rank);
	void play(Card);
	void discard(Card c);
private:
	std::vector<Player*>* players;
	Card* cards_[52];
	int current_turn;
	TableCards* table_cards; 
	static const std::string RANKS[13];
	static const std::string SUITS[4];
	static const int CARD_COUNT;
	bool empty_table;
	int cards_left;
	int seed;
	bool new_game;
};

#endif
