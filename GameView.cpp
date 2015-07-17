#include <string>
#include <iostream>
#include <gtkmm/messagedialog.h>
#include "GameView.h"
#include "GameController.h"
#include "Command.h"
#include "BadInputException.h"
#include "TypeDialogbox.h"

using namespace std;

const char* GameView::IMAGE_NAMES[53] = {
	"cards_png/0_0.png", "cards_png/0_1.png", "cards_png/0_2.png", "cards_png/0_3.png", 
	"cards_png/0_4.png", "cards_png/0_5.png", "cards_png/0_6.png", "cards_png/0_7.png", 
	"cards_png/0_8.png", "cards_png/0_9.png", "cards_png/0_j.png", "cards_png/0_q.png", 
	"cards_png/0_k.png", "cards_png/1_0.png", "cards_png/1_1.png", "cards_png/1_2.png", 
	"cards_png/1_3.png", "cards_png/1_4.png", "cards_png/1_5.png", "cards_png/1_6.png", 
	"cards_png/1_7.png", "cards_png/1_8.png", "cards_png/1_9.png", "cards_png/1_j.png", 
	"cards_png/1_q.png", "cards_png/1_k.png", "cards_png/2_0.png", "cards_png/2_1.png", 
	"cards_png/2_2.png", "cards_png/2_3.png", "cards_png/2_4.png", "cards_png/2_5.png", 
	"cards_png/2_6.png", "cards_png/2_7.png", "cards_png/2_8.png", "cards_png/2_9.png", 
	"cards_png/2_j.png", "cards_png/2_q.png", "cards_png/2_k.png", "cards_png/3_0.png", 
	"cards_png/3_1.png", "cards_png/3_2.png", "cards_png/3_3.png", "cards_png/3_4.png", 
	"cards_png/3_5.png", "cards_png/3_6.png", "cards_png/3_7.png", "cards_png/3_8.png", 
	"cards_png/3_9.png", "cards_png/3_j.png", "cards_png/3_q.png", "cards_png/3_k.png", 
	"cards_png/nothing.png"
};

Glib::RefPtr<Gdk::Pixbuf> createPixbuf(const string & name) {
	return Gdk::Pixbuf::create_from_file( name );
}

GameView::GameView() : seed_entry(), start_game_button("Start new game with seed:"), player_1_rage("Rage!"), player_2_rage("Rage!"), player_3_rage("Rage!"), player_4_rage("Rage!"), end_game_button("End current game"), table(18, 13, false), table_cards_label("Cards on the table"), hand_cards_label("Your hand") {
	controller = new GameController(players, table_cards);
	invitePlayers();
	for(vector<Player*>::iterator it = players->begin(); it != players->end(); ++it){
		(*it)->subscribe(this);
	}
	table_cards->subscribe(this);
	transform(&IMAGE_NAMES[0], &IMAGE_NAMES[G_N_ELEMENTS(IMAGE_NAMES)], 
			   std::back_inserter(deck), &createPixbuf);
	controller->deal();
	initGUI();
	startMove();
}

GameView::~GameView(){
	delete controller;
	delete IMAGE_NAMES;
	for(int i = 0; i < sizeof(table_card_images); i++){
		if(table_card_images[i]) delete table_card_images[i];
	}
	for(int i = 0; i < 13; i++){
		if(hand_cards[i]) delete hand_cards[i];
		if(hand_card_buttons[i]) delete hand_card_buttons[i];
	}
}

void GameView::onQuitClicked(){
	controller->quit();
}

void GameView::onStartClicked(){
	int seed = stoi(seed_entry.get_text());
	players = NULL; table_cards = NULL;
	GameController* temp = controller;
	controller = new GameController(players, table_cards, seed);	
	invitePlayers();
        for(vector<Player*>::iterator it = players->begin(); it != players->end(); ++it){
                (*it)->subscribe(this);
        }
        table_cards->subscribe(this);
        transform(&IMAGE_NAMES[0], &IMAGE_NAMES[G_N_ELEMENTS(IMAGE_NAMES)],
                           std::back_inserter(deck), &createPixbuf);
        controller->deal();
        update(); 
        startMove();
	delete temp;
}


void GameView::onRageClicked(){
	controller->rageQuit();
	pcMove();
}

void GameView::invitePlayers(){
	string types[4];	
	for(int i = 0; i < 4; i++){
		TypeDialogbox* typeBox = new TypeDialogbox(*this, "Select player " + to_string(i + 1) + " species");
		controller->addPlayer(typeBox->getType());
		delete typeBox;
	}
}

void GameView::startMove(){
	if(controller->emptyDeck()){
		bool end_game_check = false;
        	vector<int> winners;
        	int lowest_score = -1;
        	string message = "ROUND RESULTS\n\n";
		for(int i = 0; i < players->size(); i++){
                	Player* p = players->at(i);
			message += "Player " + to_string(i + 1) +  "'s discards:\n";
                	for(int j = 0; j < p->getDiscards().size(); j++){
                     	message += "- " + controller->getRank((int)(p->getDiscards()[j])->getRank())  + controller->getSuit((int)(p->getDiscards()[j])->getSuit()).substr(0,1) + "\n";
                	}
                	int total_score = p->getOldScore() + p->getScore();
                	if((lowest_score == -1)||(total_score < lowest_score)){
                        	winners.clear();
                        	winners.push_back(i + 1);
                        	lowest_score = total_score;
                	}else if(total_score == lowest_score){
                        	winners.push_back(i + 1);
                	}
                	if(total_score >= 80) end_game_check = true;
                	message +=  "Player " + to_string(i + 1) +  "'s score: " + to_string(p->getOldScore()) +  " + " + to_string(p->getScore()) + " = " + to_string(total_score) + "\n\n";
        	}
			MsgDialogbox stats(*this, message);
        	if(end_game_check){
			string win_msg = "";
                	for(vector<int>::iterator it = winners.begin(); it != winners.end(); ++it){
				win_msg += "Player " + to_string(*it) +  " wins!\n";
                	}
			MsgDialogbox win(*this, win_msg);
                	exit(1);
        	}	
		controller->endOfRound();
		table_cards->clearTable();
		return startMove();
	}
	controller->processLegalPlays();
	if(!(controller->humanCheck())){
		pcMove();
	}
}

void GameView::pcMove(){
	controller->pcTurn();
	controller->newMove();
	startMove();
}

Glib::RefPtr<Gdk::Pixbuf> GameView::getCardImage(Rank r, Suit s) {
	int index = ((int) s)*13 + ((int) r);
	return deck[index];
}

Glib::RefPtr<Gdk::Pixbuf> GameView::getNullCardImage() {
	return deck.back();
}

void GameView::onCardButtonClicked(Glib::ustring a){
	int index = stoi(a);
	int turn = controller->getCurrentTurn();
	try{
		controller->select(*(players->at(turn)->getHandCards()[index]));
	}catch(BadInputException& e){
		MsgDialogbox err(*this, e.getMessage());
		return;
	}
	controller->newMove();
	startMove();
}

void GameView::initGUI(){
	seed_entry.set_text("0");
	end_game_button.signal_clicked().connect( sigc::mem_fun( *this, &GameView::onQuitClicked ) );

	start_game_button.signal_clicked().connect(sigc::mem_fun( *this, &GameView::onStartClicked));
	const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = getNullCardImage();
	set_border_width(10);
	frame.set_label_align( Gtk::ALIGN_CENTER, Gtk::ALIGN_TOP );
	frame.set_shadow_type( Gtk::SHADOW_ETCHED_OUT );
	add(frame);

	frame.add(table);
	table.attach(start_game_button, 0, 4, 0, 1);
	table.attach(seed_entry, 4, 9, 0, 1);
	table.attach(end_game_button, 9, 13, 0, 1);

    table.attach(table_cards_label, 0,13,1,2, Gtk::FILL, Gtk::FILL, 2, 2 );
	for(int s = 0; s < 4; s++){
		for(int r = 0; r < 13; r++){
			table_card_images[s*13 + r] = new Gtk::Image(nullCardPixbuf);
			table.attach(*table_card_images[s*13 + r], r, r+1, s+2,s+3, Gtk::FILL, Gtk::FILL, 2, 2);	
		}
	}

	Glib::RefPtr<Gtk::TextBuffer> player_1_info = Gtk::TextBuffer::create();
    player_1_info->set_text("Player 1 Stats\nPoints: 0\nDiscards: 0");
	player_1_text.set_buffer(player_1_info);
	table.attach(player_1_text, 0,3.25,6,7, Gtk::FILL, Gtk::FILL, 2, 2 );
	player_1_rage.signal_clicked().connect( sigc::mem_fun( *this, &GameView::onRageClicked ) );
	table.attach(player_1_rage, 0, 3, 7, 8);	

	Glib::RefPtr<Gtk::TextBuffer> player_2_info = Gtk::TextBuffer::create();
	player_2_info->set_text("Player 2 Stats\nPoints: 0\nDiscards: 0");
	player_2_text.set_buffer(player_2_info);
	table.attach(player_2_text, 3.25,6.5,6,7, Gtk::FILL, Gtk::FILL, 2, 2 );
	player_2_rage.signal_clicked().connect( sigc::mem_fun( *this, &GameView::onRageClicked ) );
	table.attach(player_2_rage, 3, 6, 7, 8);

	Glib::RefPtr<Gtk::TextBuffer> player_3_info = Gtk::TextBuffer::create();
	player_3_info->set_text("Player 3 Stats\nPoints: 0\nDiscards: 0");
	player_3_text.set_buffer(player_3_info);
	table.attach(player_3_text, 6.5,9.75,6,7, Gtk::FILL, Gtk::FILL, 2, 2 );
	player_3_rage.signal_clicked().connect( sigc::mem_fun( *this, &GameView::onRageClicked ) );
	table.attach(player_3_rage, 6, 9, 7, 8);

	Glib::RefPtr<Gtk::TextBuffer> player_4_info = Gtk::TextBuffer::create();
	player_4_info->set_text("Player 4 Stats\nPoints: 0\nDiscards: 0");
	player_4_text.set_buffer(player_4_info);
	table.attach(player_4_text, 9.75,13,6,7, Gtk::FILL, Gtk::FILL, 2, 2 );
	player_4_rage.signal_clicked().connect( sigc::mem_fun( *this, &GameView::onRageClicked ) );
	table.attach(player_4_rage, 9, 13, 7, 8);

	//table.attach(hand_cards_label, 0, 13 , 9, 10, Gtk::FILL, Gtk::FILL, 2, 2 );
	
	for(int i = 0; i < 13; i++){
		hand_cards[i] = new Gtk::Image(nullCardPixbuf);
		hand_card_buttons[i] = NULL;
		table.attach(*hand_cards[i], i, i + 1, 8, 9, Gtk::FILL, Gtk::FILL, 2, 2);
    }		
	table.attach(hand_cards_label, 0, 13 , 9, 10, Gtk::FILL, Gtk::FILL, 2, 2 );
	show_all();
	update();
}

void GameView::update(){	
	const Glib::RefPtr<Gdk::Pixbuf> nullCardPixbuf = getNullCardImage();
	for(int s = 0; s < 4; s++){
		for(int r = 0; r < 13; r++){
			table.remove(*(table_card_images[s*13 + r]));
			if(table_cards->cardExists((Suit)s, (Rank)r)){
        	    		Glib::RefPtr<Gdk::Pixbuf> cardPixbuf = getCardImage((Rank) r, (Suit) s);
                		table_card_images[s*13 + r] = new Gtk::Image(cardPixbuf);
			}else{
				table_card_images[s*13 + r] = new Gtk::Image(nullCardPixbuf);
			}
			table.attach(*table_card_images[s*13 + r], r, r+1, s+2,s+3, Gtk::FILL, Gtk::FILL, 2, 2);
		}
	}	
	int turn = controller->getCurrentTurn();
	table.remove(player_1_text);
	Glib::RefPtr<Gtk::TextBuffer> player_1_info = Gtk::TextBuffer::create();
    player_1_info->set_text("Player 1 Stats\nPoints: " + to_string(players->at(0)->getScore()) + "\nDiscards: " + to_string(players->at(0)->getDiscards().size()));
	player_1_text.set_buffer(player_1_info);

	table.attach(player_1_text, 0,3.25,6,7, Gtk::FILL, Gtk::FILL, 2, 2 );

    if((turn != 0)||(players->at(turn)->getType() == PC)) player_1_rage.set_sensitive(false);
    else player_1_rage.set_sensitive(true);

    table.remove(player_2_text);
	Glib::RefPtr<Gtk::TextBuffer> player_2_info = Gtk::TextBuffer::create();
	player_2_info->set_text("Player 2 Stats\nPoints: " + to_string(players->at(1)->getScore()) + "\nDiscards: " + to_string(players->at(1)->getDiscards().size()));
	player_2_text.set_buffer(player_2_info);
	table.attach(player_2_text, 3.25,6.5,6,7, Gtk::FILL, Gtk::FILL, 2, 2 );
	if((turn != 1)||(players->at(turn)->getType() == PC))  player_2_rage.set_sensitive(false);
	else player_2_rage.set_sensitive(true);

	table.remove(player_3_text);
	Glib::RefPtr<Gtk::TextBuffer> player_3_info = Gtk::TextBuffer::create();



	player_3_info->set_text("Player 3 Stats\nPoints: " + to_string(players->at(2)->getScore()) + "\nDiscards: " + to_string(players->at(2)->getDiscards().size()));
	player_3_text.set_buffer(player_3_info);
	table.attach(player_3_text, 6.5,9.75,6,7, Gtk::FILL, Gtk::FILL, 2, 2 );
	if((turn != 2)||(players->at(turn)->getType() == PC)) player_3_rage.set_sensitive(false);
	else player_3_rage.set_sensitive(true);

	table.remove(player_4_text);
	Glib::RefPtr<Gtk::TextBuffer> player_4_info = Gtk::TextBuffer::create();
	player_4_info->set_text("Player 4 Stats\nPoints: " + to_string(players->at(3)->getScore()) + "\nDiscards: " + to_string(players->at(3)->getDiscards().size()));
	player_4_text.set_buffer(player_4_info);
	table.attach(player_4_text, 9.75,13,6,7, Gtk::FILL, Gtk::FILL, 2, 2 );
	if((turn != 3)||(players->at(turn)->getType() == PC)) player_4_rage.set_sensitive(false);
	else player_4_rage.set_sensitive(true);
	Player* p = players->at(turn);
	vector<Card*> hcards = p->getHandCards();
	
	for(int i = 0; i < 13; i++){
		if(hand_card_buttons[i]){
                
                                table.remove(*(hand_card_buttons[i]));
                
                        }else table.remove(*(hand_cards[i]));
		if(hcards[i]){
			int r = hcards[i]->getRank();
			int s = hcards[i]->getSuit();
        	Glib::RefPtr<Gdk::Pixbuf> cardPixbuf = getCardImage((Rank) r, (Suit) s);
			hand_cards[i] = new Gtk::Image(cardPixbuf);
			hand_card_buttons[i] = new Gtk::Button();
			hand_card_buttons[i]->set_image(*hand_cards[i]);
			hand_card_buttons[i]->signal_clicked().connect(sigc::bind<Glib::ustring>(sigc::mem_fun(*this, &GameView::onCardButtonClicked), to_string(i)));
			table.attach(*hand_card_buttons[i], i, i + 1, 8, 9, Gtk::FILL, Gtk::FILL, 2, 2);
		}else{
			hand_cards[i] = new Gtk::Image(nullCardPixbuf);
			hand_card_buttons[i] = NULL;
			table.attach(*hand_cards[i], i, i + 1, 8, 9, Gtk::FILL, Gtk::FILL, 2, 2);
        }
    }
	show_all();
}

