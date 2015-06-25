#include "HumanPlayer.h"
#include "Card.h"
#include "BadInputException.h"
#include <vector>
#include <string>

using namespace std;

HumanPlayer::HumanPlayer() : Player(HUMAN) {}

HumanPlayer::~HumanPlayer(){}

Card* HumanPlayer::getPlay(Card c){
	vector<Card*> legals = getLegalMoves();
	for(int i = 0; i < legals.size(); i++){
		if(c == *legals[i]) return legals[i];
	}
	throw BadInputException("This is not a legal play."); 
}

Card* HumanPlayer::getDiscard(Card c){
	vector<Card*> legals = getLegalMoves();
	if(!(legals.empty())){
		throw BadInputException("You have a legal play. You may not discard.");
        }
	vector<Card*> hcards = getHandCards();
	for(int i = 0; i < hcards.size(); i++){
                if(c == *hcards[i]) return hcards[i];
        }
}
