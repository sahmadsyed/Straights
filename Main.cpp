#include "GameView.h"
#include <stdlib.h>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]){
	GameView *game;
	if(argc >= 2) game = new GameView(atoi(argv[1]));
	else game = new GameView();
	game->start();	
	delete game;
	return 0;
}
