straights : Main.o GameView.o BadInputException.o Card.o Command.o GameController.o HumanPlayer.o PCPlayer.o Player.o Subject.o TypeDialogbox.o MsgDialogbox.o TableCards.o
	g++ -std=c++0x -g -Wall Main.o GameView.o BadInputException.o Card.o Command.o GameController.o HumanPlayer.o PCPlayer.o Player.o TypeDialogbox.o  Subject.o MsgDialogbox.o TableCards.o `pkg-config gtkmm-2.4 --cflags --libs`  -o straights

BadInputException.o : BadInputException.cpp BadInputException.h
	g++ -std=c++0x -g -Wall -c BadInputException.cpp -o BadInputException.o

Card.o : Card.cpp Card.h
	g++ -std=c++0x -g -Wall -c Card.cpp -o Card.o

Command.o : Command.cpp Command.h
	g++ -std=c++0x -g -Wall -c Command.cpp -o Command.o

GameController.o : GameController.cpp GameController.h Card.h BadInputException.h Player.h
	g++ -std=c++0x -g -Wall -c GameController.cpp -o GameController.o

GameView.o : GameView.cpp GameView.h GameController.h Command.h BadInputException.h TypeDialogbox.cpp TypeDialogbox.h MsgDialogbox.cpp  MsgDialogbox.h
	g++ -std=c++0x -g -Wall -c GameView.cpp `pkg-config gtkmm-2.4 --cflags --libs`  -o GameView.o

HumanPlayer.o : HumanPlayer.cpp HumanPlayer.h
	g++ -std=c++0x -g -Wall -c HumanPlayer.cpp -o HumanPlayer.o

PCPlayer.o : PCPlayer.cpp PCPlayer.h
	g++ -std=c++0x -g -Wall -c PCPlayer.cpp -o PCPlayer.o

Main.o : Main.cpp GameView.h
	g++ -std=c++0x -g -Wall -c Main.cpp `pkg-config gtkmm-2.4 --cflags --libs`  -o Main.o

Player.o : Player.cpp Player.h Card.h
	g++ -std=c++0x -g -Wall -c Player.cpp -o Player.o

Subject.o : Subject.cpp Subject.h
	g++ -std=c++0x -g -Wall -c Subject.cpp -o Subject.o

TypeDialogbox.o : TypeDialogbox.cpp TypeDialogbox.h
	g++ -std=c++0x -g -Wall -c TypeDialogbox.cpp `pkg-config gtkmm-2.4 --cflags --libs` -o TypeDialogbox.o

MsgDialogbox.o : MsgDialogbox.cpp  MsgDialogbox.h
	g++ -std=c++0x -g -Wall -c MsgDialogbox.cpp `pkg-config gtkmm-2.4 --cflags --libs` -o MsgDialogbox.o

TableCards.o : TableCards.cpp TableCards.h
	g++ -std=c++0x -g -Wall -c TableCards.cpp `pkg-config gtkmm-2.4 --cflags --libs` -o TableCards.o

