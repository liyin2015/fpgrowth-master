//
// Created by Li Yin Sulimowicz on 9/22/16.
//

#ifndef APRIORI_FPGROWTH_H
#define APRIORI_FPGROWTH_H
#include "Header.h"
#include "TreeElement.h"
#include "hElement.h"
#include "io_manager.h"
#include "Database.h"
#include "ItemSet.h"
#include <string>
using namespace std;

class FPGrowth
{
public:
    FPGrowth(int min, string& file);
    ~FPGrowth();

    void loadData();

    void ScanFirstTimeCreatHeader();

    void creatTree();

    void findPrefixPath(const int& itemID, vector<FreqItem>& conPath,Header& conHeader); //start from the element in the header

    void testPredixPath();

    void creatConTree(TreeElement* conTree, vector<FreqItem>& db, CondenseHeader& conHeader);

    void mineTree(TreeElement* conTree, Header& conHead, const int& minSup, FreqItem& predixFix, vector<FreqItem>& finalList); //used to create the conditional tree

public:
    int minsup;
    Database *db;
    Header header;
    TreeElement fpTree;
    string fileDir;
    int domain;
};


#endif //APRIORI_FPGROWTH_H
