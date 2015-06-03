#include <iostream>
#include <string>
#include "ShoppingList.h"
#include <sstream>
#include <map>

Item::Item(std::string itemName, double priceCost){
	name		= itemName;
	price		= priceCost;
	nextItem	= NULL;
	prevItem	= NULL;
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
			return;
		}
		if (indexCounter == index){
			return findItem;
		}
		findItem = findItem->nextItem;
		indexCounter += 1;
	}
	return;
}

int ShoppingList::showSize(){
	return itemCount;
}

void ShoppingList::organize(){
	for (int i = 0; i < itemCount; i++){
		ordering[at(i)->itemNumber] = at(i)->price;
	}



}

void ShoppingList::mergesort(std::map<int, double> *a, int*b, int low, int high){
	int pivot;
	if (low<high){
		pivot = (low + high) / 2;
		mergesort(ordering, b, low, pivot);
		mergesort(ordering, b, pivot + 1, high);
		merge(ordering, b, low, pivot, high);
	}
}
void ShoppingList::merge(std::map<int, double> *ordering, int *b, int low, int pivot, int high){
	int h, i, j, k;
	h = low;
	i = low;
	j = pivot + 1;

	while ((h <= pivot) && (j <= high)){
		if (ordering[h] <= ordering[j]){
			b[i] = ordering[h];
			h++;
		}
		else
		{
			b[i] = ordering[j];
			j++;
		}
		i++;
	}
	if (h>pivot)
	{
		for (k = j; k <= high; k++)
		{
			b[i] = ordering[k];
			i++;
		}
	}
	else
	{
		for (k = h; k <= pivot; k++)
		{
			b[i] = ordering[k];
			i++;
		}
	}
	for (k = low; k <= high; k++) ordering[k] = b[k];
}