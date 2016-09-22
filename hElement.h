#ifndef _hElement
#define _hElement

class TreeElement;

class hElement {
public:
	int itemID;
	int sup; //total count
	TreeElement *link;

	hElement():itemID(-1),sup(0),link(nullptr){}
	hElement(int _itemID, int _sup, TreeElement *_link);
	void print(int index);
};
#endif
