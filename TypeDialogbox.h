#ifndef TYPE_DIALOG_BOX_H
#define TYPE_DIALOG_BOX_H
#include <gtkmm/dialog.h>
#include <gtkmm/box.h>
#include <gtkmm/radiobuttongroup.h>
#include <gtkmm/radiobutton.h>
#include <string>
#include <vector>
using std::string;
using std::vector;

class TypeDialogbox : Gtk::Dialog {
public:
	TypeDialogbox( Gtk::Window & parentWindow, string title);
	virtual ~TypeDialogbox();
	string getType();	
private:
	Gtk::RadioButton::Group group;
	vector<Gtk::RadioButton *> buttons;
	string type;
};
#endif
