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

ShoppingList::ShoppingList(Item *newHeadItem){
	itemCount = 0;
	headItem = newHeadItem;
	tailItem = NULL;
}


void ShoppingList::setHead(Item *newItem){
	headItem = newItem;
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
		newItem->prevItem = getTail();
		itemCount += 1;
		newItem->itemNumber = itemCount;
		Item *current = getTail();
		current->nextItem = newItem;
		end->prevItem = newItem;
	}
}

void ShoppingList::addItemAtEnd(Item *newItem){
	if (headItem == NULL)
	{
		itemCount += 1;
		newItem->itemNumber = itemCount;
		headItem = newItem;
		tailItem = newItem;
	}
	else
	{
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
	if (headItem == NULL){ return NULL; }
	return headItem;
}

Item *ShoppingList::getTail(){
	if (tailItem == NULL){ return NULL; }
	return tailItem;
}

void frontBackSplit(Item *sourceListBegin, 
					Item *sourceListEnd, 
					Item **frontListBegin, 
					Item **frontListEnd,
					Item **backListBegin,
					Item **backListEnd){
	*frontListBegin = sourceListBegin;
	*backListEnd = sourceListEnd;
	//logic goes here
	Item *slow = sourceListBegin;
	Item *fast = sourceListBegin->nextItem;
	
	while (fast != sourceListEnd){
		fast = fast->nextItem;
		if (fast != sourceListEnd){
			slow = slow->nextItem;
			fast = fast->nextItem;
		}
	}
	// FAST at NULL -- SLOW at (1/2)-1 of list
	frontListBegin = sourceListBegin;
	frontListEnd = NULL; //If you are copying items instead of moving them for sort you could use slow->nextItem here
	
	backListBegin = slow->nextItem;
	backListEnd = sourceListEnd;
	frontListEnd->nextItem = NULL;
	backListBegin->prevItem = NULL;
}

ShoppingList *sortedMerge(ShoppingList *a, ShoppingList *b){
	ShoppingList *result = NULL;
	if (a == NULL){ return b; }
	if (b == NULL){ return a; }
	if (a->getHead() < b->getHead()){
		result = a;
		sortedMerge(result, b);
	}
	else{
		result = b;
		sortedMerge(a, result);
	}
	return result;
}

void mergeSort(ShoppingList &sourceList){
	ShoppingList* list = *sourceList;
	ShoppingList *a;
	ShoppingList *b;

	// Ignore if 0 or 1 items in list
	if ((list == NULL) || (list->getHead() == NULL)){
		return;
	}
	// Split Linked Lists via Objects
	frontBackSplit(sourceList->headItem, sourceList->tailItem,a->headItem,a->tailItem,b->headItem,b->tailItem);
	// Sort sublists
	mergeSort(&a);
	mergeSort(&b);
	// Combine Lists
	sortedMerge(a, b);
}