#include <glibmm/ustring.h>
#include <gtkmm/label.h>
#include <vector>
#include <map>
#include <gdkmm/pixbuf.h>
#include <gtkmm/window.h>
#include <gtkmm/image.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/frame.h>
#include <gtkmm/table.h>
#include <gtkmm/entry.h>
#include <gtkmm/textview.h>
#include <gtkmm/textbuffer.h>
#include "GameController.h"
#include "Card.h"
#include "MsgDialogbox.h"
#include "Player.h"
#include "Observer.h"
#include "TypeDialogbox.h"
#include "TableCards.h"

class GameController;

class GameView : public Observer, public Gtk::Window{
public:
	GameView();
	~GameView();
	void invitePlayers();
	void startMove();
	void pcMove();
	void update();
	Glib::RefPtr<Gdk::Pixbuf> getCardImage(Rank, Suit);
	Glib::RefPtr<Gdk::Pixbuf> getNullCardImage();
	void onCardButtonClicked(Glib::ustring a);
	void onQuitClicked();
	void onStartClicked();
	void initGUI();
	void onRageClicked();
private:
	GameController* controller;
	std::vector<Player*>* players;
	TableCards* table_cards; 
	static const char* IMAGE_NAMES[53];          
	Gtk::Image* table_card_images[52];         
	Gtk::Image* hand_cards[13];
	Gtk::Button* hand_card_buttons[13];
	std::vector< Glib::RefPtr< Gdk::Pixbuf > > deck;  
	Gtk::Frame frame;            
	Gtk::Table table;
	Gtk::Button start_game_button;
    Gtk::Button end_game_button;
	Gtk::Entry seed_entry;
	Gtk::TextView table_cards_title;
	Gtk::TextView player_1_text;
	Gtk::TextView player_2_text;
	Gtk::TextView player_3_text;
	Gtk::TextView player_4_text;
	Gtk::Button player_1_rage;
	Gtk::Button player_2_rage;
	Gtk::Button player_3_rage;
	Gtk::Button player_4_rage;
	Gtk::Label table_cards_label;
	Gtk::Label hand_cards_label;	
};
