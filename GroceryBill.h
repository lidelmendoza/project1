#pragma once

#include "PriceList.h"

struct GroceryListItem{
	PriceListItem item;
	double amount;
};

class GroceryBill {
public:
    GroceryBill(const GroceryBill &pl);    
    GroceryBill& operator=(const GroceryBill& pl);
	GroceryBill(const PriceList *priceList, double taxRate);
	void scanItem(string scanCode, double quantity); // add item and quantity to bill; throw exception if item's code is not found in the pricelist
	void scanItemsFromFile(string filename); // Scan multiple codes and quantities from the given text file
	void printBill(); // Print the bill to cout. Each line contains the name of an item, total price, and the letter "T" if tax was addded.
    double getTotal(); // return the total cost of all items scanned
	~GroceryBill(){delete[] bill;} //Delete the ptr
private:
	int index, size;
	GroceryListItem *bill;
	PriceList lookup;
	double _taxRate, quantity;
    string scanCode;
};
