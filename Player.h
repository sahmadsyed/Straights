#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "Card.h"
#include "Subject.h"

enum Ptype{HUMAN, PC};

class Player : public Subject{
public:
	Player(Ptype);
	~Player();
	Player(const Player&);
	Player& operator=(const Player&);
	void addHandCard(Card*);
	std::vector<Card*> getHandCards() const;
	std::vector<Card*> getDiscards() const;
	Ptype getType() const;
	void addLegalMoves(Card*);
	std::vector<Card*> getLegalMoves() const;
	void removeFromHand(Card* c);
	int getScore() const;
	int getOldScore() const;
	void incScore(int, Card*);
	void clearLegalMoves();
	void clearDiscards();
	void clearHandCards();
	void resetScore(); 	
	virtual	Card* getPlay(Card c) = 0;
	virtual Card* getDiscard(Card c) = 0;
	void newMove();
private:
	Ptype player_type;
	std::vector<Card*> hand_cards;
	std::vector<Card*> discards;
	std::vector<Card*> legal_moves;
	int score;
	int old_score;
};

#endif
