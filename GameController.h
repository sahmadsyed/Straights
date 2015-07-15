#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

#include <vector>
#include <string>
#include <map>
#include "Card.h"
#include "Player.h"

class GameController {
public:
	GameController(int);
	~GameController();
	void addPlayer(std::string);
	void deal(int&);
	void shuffle();
	void newMove();
	void printTableCards();
	void printPlayerHand() const;
	void processLegalPlays(bool = true);
	void play(Card);
	Card* findCard(Suit, Rank);
	void addToTable(Card*);
	void discard(Card c);
	void printDeck() const;
	void quit() const;
	bool emptyDeck();
	void endOfRound();
	bool humanCheck() const;
	void pcTurn();
	void rageQuit();
private:
	std::vector<Player*>* players;
	Card* cards_[52];
	int current_turn;
	std::map<Suit, std::map<Rank, Card*>* >* table_cards; 
	static const std::string RANKS[13];
	static const std::string SUITS[4];
	static const int CARD_COUNT;
	bool empty_table;
	int cards_left;
	int seed;
};

#endif
