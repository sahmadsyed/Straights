#include <string>
#include <iostream>
#include "GameView.h"
#include "GameController.h"
#include "Command.h"
#include "BadInputException.h"

using namespace std;

GameView::GameView(int seed){
	controller = new GameController(seed);
}

GameView::~GameView(){
	delete controller;
}

void GameView::invitePlayers(){
	string player_type;
	for(int i = 0; i < 4; i++) {
		cout << "Is player " << i + 1 << " a human(h) or a computer(c)?" << endl;
		cout << ">";
		cin >> player_type;
		controller->addPlayer(player_type);
	}
}

void GameView::start(){
	invitePlayers();
	startRound();
}

void GameView::startRound(){
	int first;
	controller->deal(first);
	cout << "A new round begins. It's player " << first << "'s turn to play." << endl; 
	while(true){
		if(controller->emptyDeck()){ 
			controller->endOfRound();
			return startRound();
		}
		if(controller->humanCheck()){
			humanMove();
		}else{
			pcMove();
		}
		controller->newMove();
	}

}

void GameView::pcMove(){
	controller->processLegalPlays(false);
	controller->pcTurn();
}

void GameView::humanMove(){
	Command *cmd = new Command;
	controller->printTableCards();
	controller->printPlayerHand();
	controller->processLegalPlays();
	while(true){
		cout << ">";
		cin >> *cmd;
		Type t = cmd->type;
		try{
			switch(t){
			case PLAY:
				controller->play(cmd->card);
				break;
			case DISCARD:
				controller->discard(cmd->card);
				break;
			case DECK:
				controller->printDeck();
				continue;
			case QUIT:
				controller->quit();
			case RAGEQUIT:
				controller->rageQuit();
				pcMove();
				break;
			}
		}catch(BadInputException& e){
			cout << e.getMessage() << endl;
			continue;
		}
		break;
	}
	delete cmd;
}

