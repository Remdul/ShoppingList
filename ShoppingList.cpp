#include <iostream>
#include <string>
#include "ShoppingList.h"
#include <sstream>
#include <map>

Item::Item(const std::string &itemName, double priceCost){
	name		= itemName;
	price		= priceCost;
	nextItem	= NULL;
	prevItem	= NULL;
}

bool Item::operator < (const Item &rhs){
	if (price < rhs.price){
		return true;
	}
	else if (price > rhs.price){
		return false;
	}
	return name < rhs.name;
}

bool Item::operator > (const Item &rhs){
	if (price > rhs.price){
		return true;
	}
	else if (price < rhs.price){
		return false;
	}
	return name > rhs.name;
}

std::string Item::showItem(){
	std::stringstream itemPrinted;
	itemPrinted << name << " : " << price;
	return itemPrinted.str();
}

ShoppingList::ShoppingList(){
	itemCount = 0;
	headItem = NULL;
	tailItem = NULL;
}

std::string ShoppingList::showList(){
	Item *printNode = headItem;
	std::stringstream printList;

	if (headItem == NULL){
		return "List is Empty. You Fail.";
	}

	printList << "LinkedList Contents: \n";

	int count = 0;
	while (printNode != NULL){
		std::cout << count << " : " << printNode->name << " > " << std::endl;
		if (printNode->nextItem == NULL){
			std::cout << "   nextNode = NULL" << std::endl;
		}
		else{
			std::cout << "   nextNode Value: " << printNode->nextItem->name << std::endl;
		}
		if (printNode->prevItem == NULL){
			std::cout << "   prevNode = NULL" << std::endl;
		}
		else{
			std::cout << "   prevNode Value: " << printNode->prevItem->name << std::endl;
		}
		std::cout << "ITEM NUMBER: " << printNode->itemNumber << std::endl;

		count++;
		printNode = printNode->nextItem;
	}
	return printList.str();
}

void ShoppingList::addItemAtEnd(std::string name, double price){
	if (headItem == NULL)
	{
		Item *newItem = new Item(name, price);
		itemCount += 1;
		newItem->itemNumber = itemCount;
		headItem = newItem;
		tailItem = newItem;
	}
	else
	{
		Item *newItem = new Item(name, price);
		newItem->prevItem = tailItem;
		itemCount += 1;
		newItem->itemNumber = itemCount;
		Item *current = tailItem;
		current->nextItem = newItem;
		tailItem = newItem;
	}
}

Item *ShoppingList::at(int index){
	Item *findItem = headItem;
	int indexCounter = 0;
	while (NULL != findItem){
		if (NULL == findItem){
			return NULL;
		}
		if (indexCounter == index){
			return findItem;
		}
		findItem = findItem->nextItem;
		indexCounter += 1;
	}
	return findItem;
}

int ShoppingList::showSize(){
	return itemCount;
}
Item *ShoppingList::getHead(){
	return headItem;
}

Item *ShoppingList::getTail(){
	return tailItem;
}

void ShoppingList::organize(){
	for (int i = 0; i < itemCount; i++){
		//ordering[at(i)->itemNumber] = at(i)->price;
	}
}


void frontBackSplit(ShoppingList *list, Item *source){
	Item *headRefrence = list->getHead();
	Item *tailRefrence = list->getTail();

	// Length < 2
	if (source == NULL || source->nextItem == NULL){
		headRefrence = source;
		tailRefrence = NULL;
	}
	else{
		Item *slow = source;
		Item *fast = source->nextItem;

		// Advance FAST Item twice and SLOW Item once
		while (fast != NULL){
			fast = fast->nextItem;
			if (fast != NULL){
				slow = slow->nextItem;
				fast = fast->nextItem;
			}
		}

		// At this point, slow should be almost halfway through when fast finishes.
		headRefrence = source;
		tailRefrence = slow->nextItem;
		//tailRefrence->prevItem = NULL;
		slow->nextItem = NULL;
	}
}
void mergeSort(ShoppingList **mainList){
	ShoppingList* list = *mainList;
	ShoppingList *a;
	ShoppingList *b;

	// Ignore if 0 or 1 items in list
	if ((list == NULL) || (list->getHead() == NULL)){
		return;
	}

	frontBackSplit(&mainList, &a, &b);


}

Item *sortedMerge(Item *a, Item *b){
	Item *result = NULL;

	if (a == NULL){
		return b;
	}
	if (b == NULL){
		return a;
	}

	if (a->price <= b->price){
		result = a;
		result->nextItem = sortedMerge(a->nextItem, b);
	}
	else{
		result = b;
		result->nextItem = sortedMerge(a, b->nextItem);
	}
	return result;
}