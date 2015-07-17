#include "Subject.h"
#include <vector>

using namespace std;

Subject::Subject(){}

Subject::~Subject(){
	observers.clear();
}

void Subject::subscribe(Observer* o){
	observers.push_back(o);
}

void Subject::notify(){
	for(vector<Observer*>::iterator it = observers.begin(); it != observers.end(); ++it){
		(*it)->update();
	}
}
