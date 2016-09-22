#include <stdio.h>

#include "Header.h"

Header::Header()
{
	domain = 0;
}
void Header::Init(int d)
{
	domain = d;
	//items = new hElement*[domain];
	items.assign(domain, hElement());
	
	for (int i = 0; i < domain; i++)
		items[i] = hElement(i, 0, NULL);
}

Header::~Header()
{
}

void Header::itemFound(int itemID)
{
	items[itemID].sup++;
}

int Header::getSupport(int itemID)
{
	items[itemID - 1].sup;
}

hElement* Header::getItem(int itemID)
{
	return &items[itemID];
}

void Header::print()
{
	for (int i = 0; i < items.size(); i++)
	{
		if (items[i].sup > 0)
			items[i].print(i);
	}
}

int CondenseHeader::getSupport(int itemID)
{
	std::vector<hElement>::iterator iter;
	for( iter= items.begin();iter!=items.end();++iter )
	{
		if(iter->itemID == itemID)
		{
			return iter->sup;
		}
	}
	return -1;
}

void CondenseHeader::itemFound(int itemID, int count)
{
	//bool bFound = false;
	for(std::vector<hElement>::iterator iter = items.begin();iter!=items.end();++iter )
	{
		if(iter->itemID == itemID)
		{
			iter->sup+=count;
			return;
		}
	}
	items.push_back(hElement(itemID,count, nullptr));
	return ;
	//items[itemID].sup++;
}


hElement* CondenseHeader::getItem(int itemID)
{
	std::vector<hElement>::iterator iter;
	for( iter= items.begin();iter!=items.end();++iter )
	{
		if(iter->itemID == itemID)
		{
			return &(*iter);
			//return iter;
		}
	}
	return nullptr;
}

void CondenseHeader::remove(int minsup)
{
	std::vector<hElement>::iterator iter;
	for( iter= items.begin();iter!=items.end();)
	{
		if(iter->sup < minsup)
		{
			iter=items.erase(iter);
		}
		else
		{
			++iter;
		}
	}

}

void CondenseHeader::print()
{
	for (int i = 0; i < items.size(); i++)
	{
		printf("%d: %d: %d\n", i, items[i].itemID, items[i].sup);
	}
}
