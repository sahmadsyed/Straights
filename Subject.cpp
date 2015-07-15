#include "Subject.h"

Subject::Subject(){}

Subject::~Subject(){
	observers.clear();
}

void Subject::subscribe(Observer* o){
	observers.push_back(o);
}

void Subject::notify(){
	for(vector<Observers*>::iterator it = observers.begin(); it != observers.end(); ++it){
		(*it)->update();
	}
}