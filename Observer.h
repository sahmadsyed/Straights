#ifndef OBSERVER_H
#define OBSERVER_H

#include "Subject.h"

class Subject;

class Observer {
public:
	virtual void update() = 0;
private:
	Subject* subject;
};

#endif
