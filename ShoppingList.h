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
	Item *getHead() {return end->nextItem;}
	Item *getTail() {return end->prevItem;}

private:
	int itemCount;
	Item *end;
	
};

// PROTOTYPES
void mergeSort(ShoppingList &sourceList);
void mergeSortInternal(Item *first, Item *last);
ShoppingList *sortedMerge(ShoppingList *a, ShoppingList *b);
void frontBackSplit(ShoppingList *sourceList, ShoppingList **frontList, ShoppingList **backList);
void frontBackSplit(Item *sourceListBegin, Item *sourceListEnd,Item **frontListBegin,Item **frontListEnd,Item **backListBegin,Item **backListEnd);
