#include <stdio.h>

#include "TreeElement.h"
#include "hElement.h"

TreeElement::TreeElement(int _itemID, int _sup, TreeElement *_sibling, TreeElement *_parent)
{
	itemID = _itemID;
	sup = _sup;
	sibling = _sibling;
	parent = _parent;
}

TreeElement::~TreeElement()
{
	delete sibling;
	delete parent;
	children.clear();
}

TreeElement* TreeElement::addChild(hElement *headerNode)
{
	TreeElement* child = find(headerNode->itemID); //find from the children
	
	if (child) //if exist,
	{
		child->found();//increase the count
	}
	else//add new node
	{
		child = new TreeElement(headerNode->itemID, 1, headerNode->link, this); //headerNode->link is the sibling
		headerNode->link = child; //add link from the head
		children.push_back(child); //add children
	}
	
	return child;
}


TreeElement* TreeElement::addConChild(hElement *headerNode, int& count)
{
	TreeElement* child = find(headerNode->itemID); //find from the children

	if (child) //if exist,
	{
		child->conFound(count);//increase the count
	}
	else//add new node
	{
		child = new TreeElement(headerNode->itemID, count, headerNode->link, this); //headerNode->link is the sibling
		headerNode->link = child; //add link from the head
		children.push_back(child); //add children
	}

	return child;
}

int TreeElement::getSupport()
{
	return sup;
}

int TreeElement::getTotalSupport()
{
	if (sibling)
		return sup + sibling->getTotalSupport();
	else
		return sup;
}

int TreeElement::getItemID()
{
	return itemID;
}

TreeElement* TreeElement::find(int itemID)
{
	for (int i = 0; i < children.size(); i++)
	{
		if (children[i]->itemID == itemID)
		{
			return children[i];
		}
	}
	return NULL;
}

void TreeElement::found()
{
	sup++;
}

void TreeElement::conFound(int& count)
{
	sup+=count;
}


TreeElement* TreeElement::getSibling()
{
	return sibling;
}

TreeElement* TreeElement::getParent()
{
	return parent;
}

void TreeElement::print(int nParents)
{
	if (itemID != 0)
	{
		for (int i = 0; i < nParents; i++)
			printf("        ");
			
		printf("%d:%d\n", itemID, sup);
	}
	
	for (int i = 0; i < children.size(); i++)
		children[i]->print(nParents + 1);
}

void TreeElement::print()
{
	print(0);
}
