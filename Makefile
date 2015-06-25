straights : Main.o GameView.o BadInputException.o Card.o Command.o GameController.o HumanPlayer.o PCPlayer.o Player.o
	g++ -std=c++0x -g -Wall Main.o GameView.o BadInputException.o Card.o Command.o GameController.o HumanPlayer.o PCPlayer.o Player.o -o straights

BadInputException.o : BadInputException.cpp BadInputException.h
	g++ -std=c++0x -g -Wall -c BadInputException.cpp -o BadInputException.o

Card.o : Card.cpp Card.h
	g++ -std=c++0x -g -Wall -c Card.cpp -o Card.o

Command.o : Command.cpp Command.h
	g++ -std=c++0x -g -Wall -c Command.cpp -o Command.o

GameController.o : GameController.cpp GameController.h Card.h BadInputException.h Player.h
	g++ -std=c++0x -g -Wall -c GameController.cpp -o GameController.o

GameView.o : GameView.cpp GameView.h GameController.h Command.h BadInputException.h
	g++ -std=c++0x -g -Wall -c GameView.cpp -o GameView.o

HumanPlayer.o : HumanPlayer.cpp HumanPlayer.h
	g++ -std=c++0x -g -Wall -c HumanPlayer.cpp -o HumanPlayer.o

PCPlayer.o : PCPlayer.cpp PCPlayer.h
	g++ -std=c++0x -g -Wall -c PCPlayer.cpp -o PCPlayer.o

Main.o : Main.cpp GameView.h
	g++ -std=c++0x -g -Wall -c Main.cpp -o Main.o

Player.o : Player.cpp Player.h Card.h
	g++ -std=c++0x -g -Wall -c Player.cpp -o Player.o
