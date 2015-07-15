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

GameController::GameController(int shuffle_seed, vector<Player*>* players_, map<Suit, map<Rank, Card*>* >* table)
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
	table_cards = new  map<Suit, map<Rank, Card*>* >();
	table = table_cards;
	for(int suit = CLUB; suit != SUIT_COUNT; suit++){	
		map<Rank, Card*>* temp = new map<Rank, Card*>();
		for(int rank = ACE; rank != RANK_COUNT; rank++){
			(*temp)[(Rank)rank] = NULL;
		}
		(*table_cards)[(Suit)suit] = temp;
	}	
}

GameController::~GameController(){
	for(int i = 0; i < players->size(); i++){
		delete players->at(i);
	}
	for(int i = 0; i < sizeof(cards_); i++){
		delete cards_[i];
	}
}

void GameController::newMove() {
        current_turn = (current_turn + 1) % 4;
}

void GameController::rageQuit(){
	// convert human to PC with data intact	
	PCPlayer* replacement = new PCPlayer(*(players->at(current_turn)));
	Player* to_delete = players->at(current_turn);
	(*players)[current_turn] = replacement;
	delete to_delete;
	cout << "Player " << current_turn + 1 << " ragequits. A computer will now take over." << endl;
}

void GameController::endOfRound(){
	bool end_game_check = false;
	vector<int> winners;
	int lowest_score = -1;
	
	for(int i = 0; i < players->size(); i++){
		Player* p = players->at(i);
		cout << "Player " << i + 1 << "'s discards:";
		for(int j = 0; j < p->getDiscards().size(); j++){
			cout << " " << *(p->getDiscards()[j]);
		}
		cout << endl;
		int total_score = p->getOldScore() + p->getScore();
		if((lowest_score == -1)||(total_score < lowest_score)){
			winners.clear();
			winners.push_back(i + 1);
			lowest_score = total_score;
		}else if(total_score == lowest_score){
			winners.push_back(i + 1);
		}
		if(total_score >= 80) end_game_check = true;
		cout << "Player " << i + 1 << "'s score: " << p->getOldScore() << " + " << p->getScore() << " = " << total_score << endl;
		p->clearHandCards();
		p->clearLegalMoves();
		p->clearDiscards();
		p->resetScore();
	}
	if(end_game_check){
		for(vector<int>::iterator it = winners.begin(); it != winners.end(); ++it){
			cout << "Player " << *it << " wins!" << endl;
		}
		exit(1);
	}
	cards_left = CARD_COUNT;
	empty_table = true;
	current_turn = 0;
	for(int suit = CLUB; suit != SUIT_COUNT; suit++){
		map<Rank, Card*>* temp = new map<Rank, Card*>();
		for(int rank = ACE; rank != RANK_COUNT; rank++){
			(*temp)[(Rank)rank] = NULL;
		}
		(*table_cards)[(Suit)suit] = temp;
	}
}

Card* GameController::findCard(Suit s, Rank r){
	for(int i = 0; i < CARD_COUNT; i++){
		if((cards_[i]->getRank() == r) && (cards_[i]->getSuit() == s))
			return cards_[i];
	}
}

void GameController::addToTable(Card* c){
	(*((*table_cards)[c->getSuit()]))[c->getRank()] = c;
}

void GameController::discard(Card c){
	Card* find = players->at(current_turn)->getDiscard(c);
	int points = (int)find->getRank() + 1;
	players->at(current_turn)->incScore(points, find);
	players->at(current_turn)->removeFromHand(find);
	cout << "Player " << current_turn + 1 << " discards " << *find << "." << endl;
	cards_left--;
}

void GameController::play(Card c){
	Card* legal = players->at(current_turn)->getPlay(c);
	addToTable(legal);
	players->at(current_turn)->removeFromHand(legal);
	cards_left--;
	cout << "Player " << current_turn + 1 << " plays " << *legal << "." << endl;	
}

void GameController::pcTurn(){
	Card c;
	if(players->at(current_turn)->getLegalMoves().empty()) discard(c);			
	else play(c);
}

void GameController::processLegalPlays(bool print) {
	if(print) cout << "Legal plays:";
	vector<Card*> hand_cards = players->at(current_turn)->getHandCards();
	if(empty_table){
		Card* first_card = findCard(SPADE, SEVEN);
		players->at(current_turn)->addLegalMoves(first_card);
		if(print) cout << " " << *first_card << endl;
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
			if(print) cout << " " << *current_card;
			continue;
		}	
		if(current_rank != ACE){
			if((*((*table_cards)[current_suit]))[(Rank)(current_rank - 1)]){
				players->at(current_turn)->addLegalMoves(current_card);
				if(print) cout << " " << *current_card;
				continue;
			}
		}
		if(current_rank != KING){
			if((*((*table_cards)[current_suit]))[(Rank)(current_rank + 1)]){
				players->at(current_turn)->addLegalMoves(current_card);
				if(print) cout << " " << *current_card;
			}
		}
	}
	if(print) cout << endl;
}

void GameController::printPlayerHand() const{
	cout << "Your hand:";
	Player* current_player = players->at(current_turn);
	for(int i = 0; i < current_player->getHandCards().size(); i++){
		Card* c = current_player->getHandCards()[i];
		if(c) cout << " " << *c;
	}
	cout << endl;
}

bool GameController::emptyDeck() {
	return !(cards_left);
}

bool GameController::humanCheck() const{
	return (players->at(current_turn)->getType() == HUMAN);
}

void GameController::printTableCards() {
	cout << "Cards on the table:" << endl;
	for(map<Suit, map<Rank, Card*>* >::iterator it = table_cards->begin(); it != table_cards->end(); ++it){
		int index = distance(table_cards->begin(), it);
		cout << SUITS[index] << ":";
		for(int r = ACE; r != RANK_COUNT; r++){
			Card* check = it->second->at((Rank)r);
			if(check) cout << " " << RANKS[check->getRank()];
		}
		cout << endl;
	}
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

void GameController::deal(int& first) {
	shuffle();
	for(int i = 0; i < players->size(); i++){
		int player_num = i;
		Player* p = players->at(i);
		for(int i = player_num*13; i < (player_num*13 + 13); i++){
			p->addHandCard(cards_[i]);
			if((cards_[i]->getSuit() == SPADE) && (cards_[i]->getRank() == SEVEN)) {
				current_turn = player_num; first = player_num + 1;
			}
		}
	}
}

void GameController::printDeck() const {
	for(int i = 0; i < 4; i++){
		cout << *cards_[i*13];
		for(int j = i*13 + 1; j < i*13 + 13; j++){
			cout << " " << *cards_[j];
		}
		cout << endl;
	}
}

void GameController::quit() const{
	exit(1);
}

void GameController::shuffle(){
	static mt19937 rng(seed);
	int n = CARD_COUNT;
	while ( n > 1 ) {
		int k = (int) (rng() % n);
		--n;
		Card *c = cards_[n];
		cards_[n] = cards_[k];
		cards_[k] = c;
	}
} 
