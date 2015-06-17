#include <iostream>

class Item{
	friend class ShoppingList;
public:
	Item(const std::string &itemName, double priceCost);
	std::string showItem();
	bool operator < (const Item &rhs);
	bool operator > (const Item &rhs);
	std::string name;
	double price;
	int itemNumber;
	Item *nextItem;
	Item *prevItem;
};

class ShoppingList{
public:
	ShoppingList();
	void  addItemAtEnd(std::string name, double price);
	std::string showList();
	int showSize();
	void organize();
	Item *ShoppingList::at(int index);
	Item *getHead();
	Item *getTail();
private:
	int itemCount;
	Item *headItem;
	Item *tailItem;
};