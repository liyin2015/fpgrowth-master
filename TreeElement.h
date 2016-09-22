#ifndef _TreeElement
#define _TreeElement

#include <vector>

class hElement;

class TreeElement
{
public:
	int sup;
	int itemID;
	TreeElement *sibling; //sibling means speacial link
	TreeElement *parent;
	std::vector<TreeElement*> children;

	TreeElement():itemID(-1),sup(0),sibling(nullptr),parent(nullptr){}
	
	TreeElement(int _itemID, int _sup, TreeElement *_sibling, TreeElement *_parent);
	~TreeElement();
	TreeElement* find(int itemID);
	void print(int nParents);
	void print();
	void found();
	void conFound(int& count);
	TreeElement* getSibling();
	TreeElement* getParent();
	int getSupport();
	int getTotalSupport();
	int getItemID();
	TreeElement* addChild(hElement *headerNode);
	TreeElement* addConChild(hElement *headerNode, int& count);
};
#endif
