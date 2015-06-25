#include <iostream>
#include "PCPlayer.h"
#include "Player.h"
#include "Card.h"
#include <vector>
#include <string>

using namespace std;

PCPlayer::PCPlayer() : Player(PC) {}

PCPlayer::~PCPlayer() {}

PCPlayer::PCPlayer(const Player& p) : Player(p) {}

Card* PCPlayer::getPlay(Card c){
	vector<Card*> legals = getLegalMoves();
	Card* first = legals[0];
	return first;
}

Card* PCPlayer::getDiscard(Card c){
	Card* discard;
	vector<Card*> hcards = getHandCards();
        for(int i = 0; i < hcards.size(); i++){
		if(hcards[i]) {
                	discard = hcards[i]; 
			return discard;
                }
        }
}
