#ifndef HUMANPLAYER_H
#define HUMANPLAYER_H

#include "Player.h"
#include "Card.h"

class HumanPlayer : public Player {
public:
	HumanPlayer();
	~HumanPlayer();
	Card* getPlay(Card);
	Card* getDiscard(Card);
};

#endif
