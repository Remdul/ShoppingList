#include <iostream>
#include <string>
#include "ShoppingList.h"

int main(){
	ShoppingList myList;
	myList.addItemAtEnd("Bananas", 3.20);
	myList.addItemAtEnd("Milk", 5.20);
	myList.addItemAtEnd("Eggs", 1.30);
	myList.addItemAtEnd("Toilet Paper", 19.48);
	myList.addItemAtEnd("Bread", 0.50);
	myList.addItemAtEnd("Poopuri", 7.99);

	std::cout << myList.showList() << std::endl;
	std::cout << myList.showSize() << std::endl;
	
	Item test1 = Item("Cookies", 6.00);
	Item test2 = Item("Flour", 4.50);
	if (test1 > test2){
		std::cout << "First True" << std::endl;
	}
	if (test1 < test2){
		std::cout << "Second True" << std::endl;
	}
}	

