#ifndef MSG_DIALOG_BOX_H
#define MSG_DIALOG_BOX_H
#include <gtkmm/messagedialog.h>
#include <gtkmm/box.h>
#include <string>

class MsgDialogbox : Gtk::MessageDialog {
public:
	MsgDialogbox( Gtk::Window &parent, std::string msg);
};
#endif
