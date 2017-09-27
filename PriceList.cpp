#include <string>
#include <iostream>
#include <fstream>
#include <stdexcept>
#include "PriceList.h"
#include "PriceListItem.h"

using namespace std;

//Default constructor
PriceList::PriceList()
{
    index = 0;
    size = 10;
    aptr = new PriceListItem[size];
}

//Copy Constructor
PriceList::PriceList(const PriceList &pl){
    index = pl.index;
    size = pl.size;
    aptr = new PriceListItem[size]; //Copies the value into a new array
    for (int i = 0; i < index; i++){
        aptr[i] = pl.aptr[i];
    }
}

//Assignment operator
PriceList& PriceList::operator = (const PriceList &pl){
    if (&pl != this){ //Avoid self-assignment
        index = pl.index;
        size = pl.size;
        aptr = new PriceListItem[size]; //Copy the value into a new array
        for (int i = 0; i < index; i++){
            aptr[i] = pl.aptr[i];
        }
    }
    return *this;
}

// Load information from a text file with the given filename.
void PriceList::createPriceListFromDatafile(string filename) {
	ifstream myfile(filename);

	if (myfile.is_open()) {
		cout << "Successfully opened file " << filename << endl;
		string name;
		string code;
		double price;
		bool taxable;
		while (myfile >> name >> code >> price >> taxable) {
			// cout << code << " " << taxable << endl;
			addEntry(name, code, price, taxable);
		}
		myfile.close();
	}
	else
		throw invalid_argument("Could not open file " + filename);
}

// return true only if the code is valid
bool PriceList::isValid(string code) const {
    for (int i = 0; i < index; i++){
        if (aptr[i].getCode() == code) //If the code is valid
            return true; //Return true
    }
    return false;
}

// return price, item name, taxable? as an ItemPrice object; throw exception if code is not found
PriceListItem PriceList::getItem(string code) const {
    PriceListItem tmp;
    bool found = false;
    for (int i = 0; i < index; i++){
        tmp = aptr[i]; //Have temp variable updated for loop
        if (tmp.getCode() == code){ //Check if the codes align
            found = true;
            break;
        }
    }
    if (!found)
        throw invalid_argument("Item not found");
    return tmp;
}

// doubles array and copies the items into new array
void PriceList:: doubleArray(){
    size *= 2;
    if(size>1000000)
        size = 1000000;
  
    PriceListItem *tmp = new PriceListItem[size];
    for (int i = 0; i < index; i++){
        tmp[i] = aptr[i];
    }
    delete[] aptr;
    aptr = tmp;
}

// add item to the price list and if next entry is bigger than array double it
void PriceList::addEntry(string itemName, string code, double price, bool taxable) {
    cout << "Adding entry " << itemName << code << price << taxable << endl;
    PriceListItem item(itemName, code, price, taxable);
    aptr[index] = item;
    index++;
    if (index >= size)
        doubleArray();
}
