class Observer {
public:
	virtual void update() = 0;
private:
	Subject subject*;
};