#ifndef Header_H_
#define Header_H_

#include "hElement.h"
#include <vector>

class Header
{
public:
	std::vector<hElement> items;
	int domain;

	Header();
	
	//Header(int d);
	void Init(int d);
	~Header();
	void itemFound(int itemID);
	void print();
	int getSupport(int itemID);
	hElement* getItem(int itemID);
};

class CondenseHeader:public Header
{
public:
	void itemFound(int itemID, int count);
	int getSupport(int itemID);
	hElement* getItem(int itemID);
	//void itemCheck(int itemID)
	void remove(int minsup);
	void print();

};
#endif
