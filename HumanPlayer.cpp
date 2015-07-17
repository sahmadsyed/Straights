#include "HumanPlayer.h"
#include "Card.h"
#include "BadInputException.h"
#include <vector>
#include <string>
#include <iostream>

using namespace std;

HumanPlayer::HumanPlayer() : Player(HUMAN) {}

HumanPlayer::~HumanPlayer(){}

Card* HumanPlayer::getPlay(Card c){
	vector<Card*> legals = getLegalMoves();
	for(int i = 0; i < legals.size(); i++){
		if(c == *legals[i]) return legals[i];
	}
	throw BadInputException("You are holding legal play(s) and this isn't one of them"); 
}

Card* HumanPlayer::getDiscard(Card c){
	vector<Card*> hcards = getHandCards();
	for(int i = 0; i < hcards.size(); i++){
                if((hcards[i])&&(c == *hcards[i])) return hcards[i];
        }
}
