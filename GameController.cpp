#include <random>
#include <vector>
#include <string>
#include <random>
#include <iostream>
#include <stdlib.h>
#include <map>
#include "Card.h"
#include "GameController.h"
#include "BadInputException.h"
#include "Player.h"
#include "PCPlayer.h"
#include "HumanPlayer.h"

using namespace std;

const string GameController::RANKS[13] = {"A", "2", "3", "4", "5", "6", "7", "8", "9", "10", "J", "Q", "K"};
const string GameController::SUITS[4] = {"Clubs", "Diamonds", "Hearts", "Spades"};
const int GameController::CARD_COUNT = 52;

GameController::GameController(vector<Player*>* &players_, TableCards* &table, int shuffle_seed)
{
	seed = shuffle_seed;
	cards_left = CARD_COUNT;
	current_turn = 0;
	empty_table = true;
	Card* c;
	int card_count = 0;
	for(int suit = CLUB; suit != SUIT_COUNT; suit++){
		for(int rank = ACE; rank != RANK_COUNT; rank++){
			Suit s = (Suit)suit;
			Rank r = (Rank)rank;
			c = new Card(s, r);
			cards_[card_count] = c;
			card_count++;
		}
	}
	players = new vector<Player*>();
	players_ = players;
	table_cards = new  TableCards();
	table = table_cards;	
}

GameController::~GameController(){
	delete table_cards;
	for(int i = 0; i < players->size(); i++){
		delete players->at(i);
	}
	delete players;
	for(int i = 0; i < CARD_COUNT; i++){
		cout << i << endl;
		delete cards_[i];
	}
}

string GameController::getRank(int r){
	return RANKS[r];
}

string GameController::getSuit(int s){
	return SUITS[s];
}

void GameController::newMove() {
    current_turn = (current_turn + 1) % 4;
	players->at(current_turn)->newMove();
}

void GameController::rageQuit(){
	// convert human to PC with data intact	
	PCPlayer* replacement = new PCPlayer(*(players->at(current_turn)));
	Player* to_delete = players->at(current_turn);
	(*players)[current_turn] = replacement;
	delete to_delete;
}

void GameController::endOfRound(){
	for(int i = 0; i < players->size(); i++){
    	Player* p = players->at(i);
    	p->clearHandCards();
    	p->clearLegalMoves();
    	p->clearDiscards();
    	p->resetScore();
	}
	cards_left = CARD_COUNT;
	empty_table = true;
	current_turn = 0;
	deal();
}

Card* GameController::findCard(Suit s, Rank r){
	for(int i = 0; i < CARD_COUNT; i++){
		if((cards_[i]->getRank() == r) && (cards_[i]->getSuit() == s))
			return cards_[i];
	}
}

void GameController::discard(Card c){
	Card* find = players->at(current_turn)->getDiscard(c);
	int points = (int)find->getRank() + 1;
	players->at(current_turn)->incScore(points, find);
	players->at(current_turn)->removeFromHand(find);
	cards_left--;
}

void GameController::play(Card c){	
	Card* legal = players->at(current_turn)->getPlay(c);
	table_cards->addToTable(legal);
	players->at(current_turn)->removeFromHand(legal);
	cards_left--;
}

void GameController::select(Card c){
	if(players->at(current_turn)->getLegalMoves().size()){
		play(c);
	}else{
		discard(c);
	}
}

void GameController::pcTurn(){
	Card c;
	if(players->at(current_turn)->getLegalMoves().empty()) {
		discard(c);	
	}
	else{
		play(c);
	}
}

void GameController::processLegalPlays() {
	vector<Card*> hand_cards = players->at(current_turn)->getHandCards();
	if(empty_table){
		Card* first_card = findCard(SPADE, SEVEN);
		players->at(current_turn)->addLegalMoves(first_card);
		empty_table = false;
		return;
	}
	players->at(current_turn)->clearLegalMoves();
	for(int i = 0; i < hand_cards.size(); i++){
		Card* current_card = hand_cards[i];
		if(!current_card) continue;
		Rank current_rank = current_card->getRank();
		Suit current_suit = current_card->getSuit();
		if(current_rank == SEVEN){
			players->at(current_turn)->addLegalMoves(current_card);
			continue;
		}	
		if(current_rank != ACE){
			if(table_cards->cardExists(current_suit, (Rank)(current_rank - 1))){
				players->at(current_turn)->addLegalMoves(current_card);
				continue;
			}
		}
		if(current_rank != KING){
			if(table_cards->cardExists(current_suit, (Rank)(current_rank + 1))){
				players->at(current_turn)->addLegalMoves(current_card);
			}
		}
	}
}

bool GameController::emptyDeck() {
	return !(cards_left);
}

bool GameController::humanCheck() const{
	return (players->at(current_turn)->getType() == HUMAN);
}

void GameController::addPlayer(string type){
	Player* new_player;
	if(type == "h"){
		new_player = new HumanPlayer();
	}else if(type == "c"){
		new_player = new PCPlayer();
	}
	players->push_back(new_player);
}

void GameController::deal() {
	shuffle();
	for(int i = 0; i < players->size(); i++){
		int player_num = i;
		Player* p = players->at(i);
		for(int i = player_num*13; i < (player_num*13 + 13); i++){
			p->addHandCard(cards_[i]);
			if((cards_[i]->getSuit() == SPADE) && (cards_[i]->getRank() == SEVEN)) {
				current_turn = player_num;
			}
		}
	}
}

void GameController::quit() const{
	exit(1);
}

void GameController::shuffle(){
	static mt19937 rng(seed);
	rng.seed(seed);
	int n = CARD_COUNT;
	cout << "SALMAN " << seed << endl;
	while ( n > 1 ) {
		int k = (int) (rng() % n);
		cout << k << endl;
		--n;
		Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
	cout << "FAIZAN" << endl;
}

int GameController::getCurrentTurn(){
	return current_turn;
} 
