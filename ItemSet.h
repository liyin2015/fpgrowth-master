#ifndef _ItemSet
#define _ItemSet

#include <vector>
#include <iostream>
using namespace std;
class ItemSet {
public:
	int *items;
	int size;
	int count;

public:
	ItemSet(int);
	//bool operator==(const ItemSet& m);
	ItemSet(int, ItemSet*);
	void printSet();
	bool compare(ItemSet*);
};

class FreqItem
{
public:
	FreqItem():count(0){}
	void clear(){itemSet.clear(); count = 0;}
	void print()
	{
		for(int i=0; i<itemSet.size();++i)
		{
			cout<<itemSet[i]<<" ";
		}
		cout<<":"<<count<<endl;
	}
public:
	vector<int> itemSet;
	int count;
};
#endif
