#include "MsgDialogbox.h"
#include <gtkmm/stock.h>
using namespace std;

MsgDialogbox::MsgDialogbox( Gtk::Window & parentWindow, string msg) : MessageDialog(parentWindow, "Error!" ) {
	set_message(msg);
	show_all_children();
	run();
}
	
