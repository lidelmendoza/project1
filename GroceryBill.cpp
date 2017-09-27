#include "GroceryBill.h"
#include <iostream>
#include <fstream>

using namespace std;

//Overloading constructor
GroceryBill::GroceryBill(const PriceList *priceList, double taxRate) {
	index = 0;
	size = 20;
	bill = new GroceryListItem[size];
	_taxRate = taxRate / 100;
	lookup = *priceList;
}

//Assignment operator
GroceryBill& GroceryBill::operator=(const GroceryBill& pl){
    if (&pl != this){ //Avoid self-assignment
        index = pl.index;
        size = pl.size;
        bill = new GroceryListItem[size]; //Copy the value into a new array
        for (int i = 0; i < index; i++){
            bill[i] = pl.bill[i];
        }
    }
    return *this;
}

//Copy Constructor
GroceryBill::GroceryBill(const GroceryBill &pl){
    index = pl.index;
    size = pl.size;
    bill = new GroceryListItem[size]; //Copy the value into a new array
    for (int i = 0; i < index; i++){
        bill[i] = pl.bill[i];
    }
}

//Adding item and quantity to bill
void GroceryBill::scanItem(string scanCode, double quantity) {
	if (lookup.isValid(scanCode)){
		bill[index].item = lookup.getItem(scanCode);
		bill[index].amount = quantity;
		index++;
	}
	else
		throw invalid_argument("Invalid code");

}

// Scan multiple codes and quantities from text file
void GroceryBill::scanItemsFromFile(string filename) {
	ifstream myfile(filename);

	if (myfile.is_open()) {
		cout << "Successfully opened file " << filename << endl;
		string code;
		double amount;
		while (myfile >> code >> amount) {
			scanItem(code, amount);
		}
		myfile.close();
	}
	else
		throw invalid_argument("Could not open file " + filename);
}

//Loops through PriceListItem in bill ands them: returns the total cost of all items scanned
double GroceryBill::getTotal() {
    double x = 0;
    for (int i = 0; i < index; i++){ //Loop through all PriceListItems in the bill and add them
        double val = bill[i].item.getPrice();
        if (bill[i].item.isTaxable())
            val *= 1 + _taxRate;
        val *= bill[i].amount;
        x += val;
    }
    return x;
}

//Loops through PriceListItem in bill and prints out data
void GroceryBill::printBill() {
	for (int i = 0; i < index; i++)
		cout << bill[i].item.getItemName()
		<< "    " << bill[i].item.getPrice()
		<< "    " << (bill[i].item.isTaxable() ? "T" : "") << endl;
	cout << "TOTAL     " << getTotal() << endl;
}

//doubles array and copies the items into new array
void GroceryBill:: doubleArray(){
    size *= 2;
    size = (size > 1000 ? 1000 : size); //If its greater than a million set it to a max of a million
    GroceryListItem *tmp = new GroceryListItem[size]; //Create new list with double size
    for (int i = 0; i < index; i++){
        tmp[i] = bill[i]; //Copy from old list to new list
    }
    delete[] bill; //Delete old list
    bill = tmp;
}
