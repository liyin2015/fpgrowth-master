//
// Created by Li Yin Sulimowicz on 9/16/16.
//

#ifndef APRIORI_IO_MANAGER_H
#define APRIORI_IO_MANAGER_H
#include "hElement.h"
#include "Header.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <vector>
using namespace std;

double str2double(char const *  str);


/**************************class DVector**********************************************************/
class DVector //used for transaction X_orig
{
public:
	DVector(int totalD); //total D means total item in one transaction
	DVector();
	~DVector();
	DVector(const DVector& m);
	const DVector& operator=(const DVector& m);
	void AddOneItem(int item, int index);
	bool FindInSingleD(int index, int& item);
	void print();
	void deleteCol(const int col, int& min, int& max);
public:
	vector<int>* D_orig;
	int totalD;
};

int read_strfile(DVector& D, int& totalD, std::string filename);

void bubble_sort(hElement **items, int itemCount);

void bubble_sort(vector<hElement*>& dataset);
void findFrequentItemsets(TreeElement*, int);

void bubble_sort (int arr[], int n);
void bubble_sort(Header& header);



#endif //APRIORI_IO_MANAGER_H
