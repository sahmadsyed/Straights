#ifndef TABLE_CARDS_H
#define TABLE_CARDS_H

#include "Card.h"
#include <map>

class TableCards : public Subject{
public:
	TableCards();
	~TableCards();
	void addToTable(Card*);
	void clearTable();
	bool cardExists(Suit, Rank);
protected:
	void clear();
private:
	std::map<Suit, std::map<Rank, Card*> > table_cards;
};

#endif
