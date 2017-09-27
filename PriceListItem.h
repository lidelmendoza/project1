#pragma once
#include <string>
#include <stdexcept>
#include "PriceListItem.h"

using namespace std;

class PriceList {
public:
    PriceList();
    PriceList(const PriceList &pl);
    PriceList& operator=(const PriceList& pl);
	void createPriceListFromDatafile(string filename);//reads text file
	void addEntry(string itemName, string code, double price, bool taxable);// stores data from text file into program
    void doubleArray();
	bool isValid(string code) const;
	PriceListItem getItem(string code) const;
     ~PriceList(){delete[] aptr;} //Delete the ptr
private:
    int index, size;
	PriceListItem *aptr;
};
