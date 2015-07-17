#ifndef SUBJECT_H
#define SUBJECT_H

#include "Observer.h"
#include <vector>

class Subject {
public:
	Subject();
	~Subject();
	void subscribe(Observer*);
protected:
	void notify();
private:
	std::vector<Observer*> observers;
};

#endif
