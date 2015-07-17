#include "TableCards.h"

using namespace std;

TableCards::TableCards(){
	clear();
}

TableCards::~TableCards(){
	clear();
}

void TableCards::addToTable(Card* c){
	table_cards[c->getSuit()][c->getRank()] = c;
}

void TableCards::clear(){
	for(int suit = CLUB; suit != SUIT_COUNT; suit++){	
		map<Rank, Card*> temp;
		for(int rank = ACE; rank != RANK_COUNT; rank++){
			temp[(Rank)rank] = NULL;
		}
		table_cards[(Suit)suit] = temp;
	}
}

bool TableCards::cardExists(Suit s, Rank r){
	return table_cards[s][r];
}

void TableCards::clearTable(){
	clear();
	notify();
}
