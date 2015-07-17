#include "GameView.h"
#include <stdlib.h>
#include <iostream>
#include <gtkmm/main.h>
using namespace std;

int main(int argc, char* argv[]){	
	Gtk::Main kit(argc, argv);
	GameView game;
	Gtk::Main::run(game);
	return 0;
}
