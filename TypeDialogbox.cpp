#include "TypeDialogbox.h"
#include <gtkmm/stock.h>
#include <iostream>

TypeDialogbox::TypeDialogbox( Gtk::Window & parentWindow, string title) : Dialog( title, parentWindow, true, true ) {
	vector<string> messages;
	messages.push_back( "human" );
	messages.push_back( "computer" );
	set_default_size(250,50);	
	Gtk::VBox* contentArea = this->get_vbox();
	
	for ( int i = 0; i < messages.size(); i++ ) {
		buttons.push_back( Gtk::manage( new Gtk::RadioButton( group, messages[i] ) ) );
		contentArea->add( *buttons[i] );
	}
	
	buttons[0]->set_active();
	
    Gtk::Button * okButton = add_button( Gtk::Stock::OK, Gtk::RESPONSE_OK);
	show_all_children();
	
	int result = run();
    switch (result) {
        case Gtk::RESPONSE_OK:
            for ( int i = 0; i < messages.size(); i++ ) {
				if ( buttons[i]->get_active() ) {
					type = messages[i].substr(0,1);	
				} 
			} 
            break;
    }   	
} 

TypeDialogbox::~TypeDialogbox() {
	for ( int i = 0; i < buttons.size(); i++ ) delete buttons[i];
	buttons.clear();
}

string TypeDialogbox::getType() {
	return type;
}
