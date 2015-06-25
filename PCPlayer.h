#ifndef PCPLAYER_H
#define PCPLAYER_H

#include "Player.h"
#include "Card.h"

class PCPlayer : public Player {
public:
	PCPlayer();
	~PCPlayer();
	PCPlayer(const Player&);
	Card* getPlay(Card);
	Card* getDiscard(Card);
};

#endif
