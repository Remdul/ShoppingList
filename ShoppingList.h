#include <iostream>
#include <map>

class Item{
	friend class ShoppingList;
public:
	Item(std::string itemName, double priceCost);
	std::string showItem();
	bool operator < (const Item &rhs);
private:
	std::string name;
	double price;
	int itemNumber;
	Item *nextItem;
	Item *prevItem;
};

//Move this to the cpp file
bool Item::operator < (const Item &rhs)
{
	if (price < rhs.price)
	{
		return true;
	}
	else if (price > rhs.price)
	{
		return false;
	}
	//the prices are equal
	return name < rhs.name;
}

class ShoppingList{
public:
	ShoppingList();
	void  addItemAtEnd(std::string name, double price);
	std::string showList();
	int showSize();
	void organize();
	Item *ShoppingList::at(int index);
	void merge(std::map<int, double> *a, int*, int, int, int);
	void mergesort(std::map<int, double> *a, int*b, int low, int high);

private:
	int itemCount;
	Item *headItem;
	Item *tailItem;
	std::map<int, double> *ordering;

};

