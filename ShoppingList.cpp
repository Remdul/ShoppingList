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
		newItem->prevItem = tailItem;
		itemCount += 1;
		newItem->itemNumber = itemCount;
		Item *current = tailItem;
		current->nextItem = newItem;
		tailItem = newItem;
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

void frontBackSplit(ShoppingList *sourceList, ShoppingList **frontList, ShoppingList **backList){
	// Length < 2
	if (sourceList->getHead() == NULL || sourceList->getHead()->nextItem == NULL){
		*frontList = sourceList;
		*backList  = NULL;
	}
	else{
		Item *slow = sourceList->getHead();
		Item *fast = sourceList->getHead()->nextItem;

		// Advance FAST Item twice and SLOW Item once
		while (fast != NULL){
			fast = fast->nextItem;
			if (fast != NULL){
				slow = slow->nextItem;
				fast = fast->nextItem;
			}
		}

		// At this point, slow should be almost halfway through as fast falls off list.
		// Split SourceList into frontList and backList
		*frontList	= sourceList;
		slow->nextItem->prevItem	= NULL;
		ShoppingList temp			= ShoppingList(slow->nextItem);
		*backList					= &temp;
		slow->nextItem				= NULL;
	}
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

void mergeSort(ShoppingList **sourceList){
	ShoppingList* list = *sourceList;
	ShoppingList *a;
	ShoppingList *b;

	// Ignore if 0 or 1 items in list
	if ((list == NULL) || (list->getHead() == NULL)){
		return;
	}
	// Split Linked Lists
	frontBackSplit(list, &a, &b);
	// Sort sublists
	mergeSort(&a);
	mergeSort(&b);
	// Combine Lists
	sortedMerge(a, b);
}