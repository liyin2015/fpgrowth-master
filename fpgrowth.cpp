//
// Created by Li Yin Sulimowicz on 9/16/16.
//
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include "fpgrowth.h"
#include "Database.h"
#include "Header.h"
#include "TreeElement.h"
#include "hElement.h"
#include "ItemSet.h"
#include "io_manager.h"
#include <vector>
#include <ctime>
#define LINE_BUF_SIZE 50000

using namespace std;

Database* read_database(char *filename);


void ascendTree(TreeElement* node, FreqItem& prefixPath)
{
    prefixPath.count = node->sup;
	while(node->parent && node->parent->itemID!=-1)
	{
		//if(node->parent->sup>=minsup) {
			prefixPath.itemSet.push_back(node->parent->itemID);
		//}
		node=node->parent;
	}

}



void iterFindPrefixPath(TreeElement* node, vector<FreqItem>& prefixPath)
{
	FreqItem path;
	while(node)
	{
		path.clear();
		//if(node->sup>=minsup) {
			ascendTree(node, path);
			//if (path.itemSet.size() > 1) {
				prefixPath.push_back(path);
			//}
		//}
		node = node->sibling;
	}
}


void addBase(vector<FreqItem>& frequentSet, int& itemID)
{
	for(int i=0;i<frequentSet.size();++i)
	{
		frequentSet[i].itemSet.push_back(itemID);
	}
}

void addList(FreqItem& freq, vector<FreqItem>& finalList)
{
	//for(int i=0;i<freq.size();++i)
	//{
		finalList.push_back(freq);
	//}
}
void creatConTree(vector<FreqItem>& db, Header& header, int minsup);


Database* read_database(char *filename)
{
   Database *db;
	/*FILE *dbfile = fopen(filename,"r");
	int  tid;
	int  itemCount;
	char *itemsStr;
	char row[LINE_BUF_SIZE];

	
	while (fgets(row, LINE_BUF_SIZE, dbfile))
	{
		// Get the row info
		tid = atoi(strtok(row, "\t"));
		itemCount = atoi(strtok(NULL, "\t"));
		itemsStr = strtok(NULL, "\t");
		int items[itemCount];
		
		// Split up the itemStr into items
		items[0] = atoi(strtok(itemsStr, " "));
		for (int i = 1; i < itemCount; i++)
			items[i] = atoi(strtok(NULL, " "));
		
		// Add the row to the database
		db->addRow(tid, itemCount, items);
	}*/
	
	return db;
}

FPGrowth::FPGrowth(int min, string& file)
{
	minsup = min;
	db = nullptr;
	fpTree = TreeElement(-1, -1, NULL, NULL);
	fileDir = file;
}
FPGrowth::~FPGrowth()
{
	delete db;
	db = nullptr;
}

void FPGrowth::loadData()
{
	DVector x_orig;
	int totalD;
	//read_strfile(x_orig, totalD, "/Users/yinli/Downloads/fpgrowth-master/5000-out1.csv");
	read_strfile(x_orig, totalD, fileDir);

	int min = 0; int max=0;
	x_orig.deleteCol(0,min,max);
	x_orig.print();
	db = new Database(totalD);

	for(int i=0;i<totalD;++i)
	{
		int* tmp = new int[x_orig.D_orig[i].size()];
		for(int j=0;j<x_orig.D_orig[i].size();j++)
		{
			tmp[j] = x_orig.D_orig[i][j];
		}
		bubble_sort(tmp,x_orig.D_orig[i].size());
		db->addRow(i,x_orig.D_orig[i].size(),tmp);
		delete tmp;
		tmp = nullptr;
	}
	domain = max-0+1;
}

void FPGrowth::ScanFirstTimeCreatHeader()
{
	header.Init(domain);
	cout<<"header size"<<header.domain<<"items"<<endl;
	int itemId = -1;

	// step1: Find frequent 1-item sets C1
	for (int i = 0; i < db->size; i++)
	{
		for (int j = 0; j < db->getRow(i)->count; j++)
		{
			itemId = db->getRow(i)->items[j];
			//cout<<"itemId"<<itemId<<endl;
			header.itemFound(itemId); //id starts from 0
		}
	}

	for(vector<hElement>::iterator iter=header.items.begin();iter!=header.items.end();++iter) //filder the small ones
	{
		if(iter->sup<minsup)
		{
			iter->sup = -1;
			iter->itemID = -1;
		}
	}

	cout<<"afeter delete"<<header.items.size()<<endl;
	header.print();
}

void FPGrowth::creatTree()
{
	Transaction *row = nullptr;
	TreeElement *curr = &fpTree;

	for (int i = 0; i < db->size; i++)
	{
		curr = &fpTree; //every time starts from the root.
		row = db->getRow(i);
		vector<hElement*> itemsInTrans;
		//go through the database, find item in the header, sort them in this transaction, filter it too.
		// Get the items from the header table
		for (int j = 0; j < row->count; j++)
		{
			//use the id as index
			if(header.items[row->items[j]].itemID==-1)
			{
				continue;
			}
			itemsInTrans.push_back(header.getItem(row->items[j]));
		}
		bubble_sort(itemsInTrans);
		// Stable sort the elements into their sup order
		//bubble_sort(items, row->count);

		// Go through the elements, while they meet minsup
		//for (int j = 0; j < row->count && items[j]->sup >= minsup; j++)
		for (int j = 0; j < itemsInTrans.size(); j++)
		{
			//cout<<"id:"<<itemsInTrans[j]->itemID<<endl;
			// Add the child and set it to curr
			curr = curr->addChild(itemsInTrans[j]); //starts from head
		}
	}

	fpTree.print();

}

void FPGrowth::findPrefixPath(const int& itemID, vector<FreqItem>& conPath,Header& conHeader) //start from the element in the header
{
	//vector<int> conditionPath;
	conPath.clear();

	for(int i=0;i<conHeader.items.size();++i)
	{
		if(conHeader.items[i].itemID == itemID)
		{
			//if(header.items[itemID].link) //get into the tree
			if(conHeader.items[i].link) //get into the tree
			{
				iterFindPrefixPath(conHeader.items[i].link, conPath);
			}
			return;
		}
	}


}



void FPGrowth::testPredixPath()
{
	vector<FreqItem> predixpath;

	for(int i=0;i<header.items.size();i++)
	{
		predixpath.clear();
		findPrefixPath(header.items[i].itemID,predixpath, header);


		cout<<"id"<<header.items[i].itemID<<"total set"<<predixpath.size()<<endl;

		for(int i=0;i<predixpath.size();++i)
		{
			//cout<<"item"<<i<<endl;
			predixpath[i].print();

		}
		TreeElement conTree(-1, -1, NULL, NULL);
		CondenseHeader conHeader;
		creatConTree(&conTree,predixpath,conHeader);
	}
}

void FPGrowth::creatConTree(TreeElement* conTree, vector<FreqItem>& db, CondenseHeader& conHeader)
{
	//CondenseHeader conHeader;
	for(vector<FreqItem>::iterator iter = db.begin(); iter!=db.end();++iter)
	{
		for(int i=0;i<iter->itemSet.size();++i)
		{
			conHeader.itemFound(iter->itemSet[i],iter->count);
		}
	}

	/*cout<<"header size"<<header.domain<<"items"<<endl;
    int itemId = -1;

    // step1: Find frequent 1-item sets C1
    for (int i = 0; i < db->size; i++)
    {
        for (int j = 0; j < db->getRow(i)->count; j++)
        {
            itemId = db->getRow(i)->items[j];
            //cout<<"itemId"<<itemId<<endl;
            header.itemFound(itemId); //id starts from 0
        }
    }*/

	cout<<"conHeader tree"<<conHeader.items.size()<<endl;
	conHeader.print();
	conHeader.remove(minsup);
	cout<<"after prune"<<endl;
	conHeader.print();

	if(conHeader.items.empty())
	{
		return;
	}

	FreqItem *row = nullptr;
	TreeElement *curr = conTree;

	cout<<"original tree"<<endl;
	curr->print();

	for (int i = 0; i < db.size(); i++)
	{
		curr = conTree; //every time starts from the root.
		row = &db[i];
		vector<hElement*> itemsInTrans;
		for (int j = 0; j < row->itemSet.size(); j++)
		{
			hElement* tmp = conHeader.getItem(row->itemSet[j]);
			if(tmp== nullptr)
			{
				continue;
			}
			itemsInTrans.push_back(tmp);
		}
		bubble_sort(itemsInTrans);

		for (int j = 0; j < itemsInTrans.size(); j++)
		{
			curr = curr->addConChild(itemsInTrans[j],row->count); //starts from head
		}
	}

	cout<<"current tree"<<endl;
	conTree->print();
	return;

}



void FPGrowth::mineTree(TreeElement* conTree, Header& conHead, const int& minSup, FreqItem& predixFix, vector<FreqItem>& finalList) //used to create the conditional tree
{
	for(int i=0;i<conHead.items.size();++i) {
		if (conHead.items[i].itemID == -1) {
			continue;
		}

		FreqItem newFreqSet = predixFix;
		if (predixFix.itemSet.empty())
		{
			newFreqSet.itemSet.push_back(conHead.items[i].itemID);
			newFreqSet.count = conHead.items[i].sup;
		}
		else
		{
			newFreqSet.itemSet.push_back(conHead.items[i].itemID); //5 and 2
			newFreqSet.count = conHead.items[i].sup;
		}
		//FreqItem tmp;
		//tmp.count = head.items[i].sup;
		//tmp.itemSet.push_back
		//addBase(newFreqSet, head.items[i].itemID); //concacate new id
		addList(newFreqSet,finalList);
		vector<FreqItem> conPathBass;
		findPrefixPath(conHead.items[i].itemID,conPathBass,conHead);
		cout<<"item"<<conHead.items[i].itemID<<endl;
		for(int i=0;i<conPathBass.size();++i)
		{

			conPathBass[i].print();

		}
		TreeElement conLocalTree(-1,-1,nullptr, nullptr);
		CondenseHeader conHeader;
		creatConTree(&conLocalTree,conPathBass, conHeader);

		if(!conHeader.items.empty())
		{
			//cout<<"conditionall tree for"<<newFreqSet.print()<<endl;
			/*FreqItem tmp;
            for(int i=0;i<conHeader.items.size();++i)
            {
                tmp.itemSet.push_back(conHeader.items[i].itemID);
            }
            tmp.count = conHeader.items[conHeader.items.size()-1].sup;


            tmp.itemSet.push_back(conHead.items[i].itemID);
            finalList.push_back(tmp);*/

			if(conHeader.items.size()>0)
			{
				cout<<"need to generate more for ";
				newFreqSet.print(); // the tree is 2:3 3:2

				cout<<"header"<<endl;
				for(int i=0;i<conHeader.items.size();i++)
				{
					cout<<"id:"<<conHeader.items[i].itemID<<"times:"<<conHeader.items[i].sup<<endl;
				}

				mineTree(&conLocalTree, conHeader,minsup,newFreqSet,finalList);
			}


			//mineTree(&conLocalTree, conHeader,minSup,newFreqSet,finalList);
		}
		//creatTree
	}
}



// Lawl, m i 4 real?
