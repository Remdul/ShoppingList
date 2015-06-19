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
	ShoppingList(Item *newHeadItem);
	void addItemAtEnd(std::string name, double price);
	void addItemAtEnd(Item *newItem);
	std::string showList();
	int showSize();
	Item *ShoppingList::at(int index);
	Item *getHead();
	Item *getTail();
	void setHead(Item *newItem);

private:
	int itemCount;
	Item *headItem;
	Item *tailItem;
};

// PROTOTYPES
void mergeSort(ShoppingList **sourceList);
ShoppingList *sortedMerge(ShoppingList *a, ShoppingList *b);
void frontBackSplit(ShoppingList *sourceList, ShoppingList **frontList, ShoppingList **backList);
