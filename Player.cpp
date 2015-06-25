#include <iostream>
#include <string>
#include "Player.h"

using namespace std;

Player::Player(Ptype type) : player_type(type) , score(0) , old_score(0) {}

Player::~Player(){
	for(int i = 0; i < hand_cards.size(); i++){
		hand_cards[i] = NULL;
	}
	for(int i = 0; i < discards.size(); i++){
		discards[i] = NULL;
	}
	for(int i = 0; i < legal_moves.size(); i++){
		legal_moves[i] = NULL;
	}
}

Player::Player(const Player& p){
	for(int i = 0; i < p.getHandCards().size(); i++){
		hand_cards.push_back(p.getHandCards()[i]);
	}
	for(int i = 0; i < p.getLegalMoves().size(); i++){
		legal_moves.push_back(p.getLegalMoves()[i]);
	}
	for(int i = 0; i < p.getDiscards().size(); i++){
		discards.push_back(p.getDiscards()[i]);
	}
	score = p.getScore();
	old_score = p.getOldScore();
}

Player& Player::operator=(const Player& p){}

void Player::addHandCard(Card* card){
	hand_cards.push_back(card);
}

Ptype Player::getType() const {
	return player_type;
}

vector<Card*> Player::getHandCards() const{
	return hand_cards;
}
vector<Card*> Player::getDiscards() const{
	return discards;
}

vector<Card*> Player::getLegalMoves() const{
	return legal_moves;
}

void Player::addLegalMoves(Card* move){
	legal_moves.push_back(move);
}

void Player::removeFromHand(Card* c){
	int index;
	for(int i = 0; i < hand_cards.size(); i++){
		if(!(hand_cards[i])) continue;
		if(*c == *hand_cards[i]) {
			index = i; break;
		}
	}
	hand_cards[index] = NULL;
}

int Player::getScore() const{
	return score;
}

void Player::incScore(int s, Card* c){
	score+=s;	
	discards.push_back(c);
}

void Player::clearLegalMoves(){
	legal_moves.clear();
}

void Player::clearDiscards(){
	discards.clear();
}

void Player::resetScore(){
	old_score+= score;
	score = 0;
}

int Player::getOldScore() const{
	return old_score;
}

void Player::clearHandCards(){
	hand_cards.clear();
}
