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
	vector<Observers*> observers;
};