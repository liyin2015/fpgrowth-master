//
// Created by Li Yin Sulimowicz on 9/22/16.
//

#include <string>
#include "fpgrowth.h"

const int minsup = 4;

//there might exist the space free problem
int main(int argc, char *argv[])
{
    //string filename = "/Users/yinli/Downloads/fpgrowth-master/db4.txt";

    string filename = "/Users/yinli/Downloads/fpgrowth-master/5000-out1.csv";
    FPGrowth fp(minsup,filename);
    fp.loadData();
    clock_t t1 = clock();
    fp.ScanFirstTimeCreatHeader();
    fp.creatTree();
    //fp.testPredixPath();
    FreqItem predixFix;
    vector<FreqItem> finalList;
    //bubble_sort(fp.header);
    Header newHeader = fp.header;
    bubble_sort(newHeader);
    fp.mineTree(nullptr,newHeader,minsup,predixFix,finalList);

    for(int i=0;i<finalList.size();i++)
    {
        cout<<"i:"<<i<<"  ";
        finalList[i].print();
        cout<<endl;
    }
    cout<<"total time"<<(double)(clock()-t1)/CLOCKS_PER_SEC<<"secs"<<endl;
    //the problem of the fp growth is no way to compute the confidence, can not get the frequent numbers

    // Free up memory

   // exit(0);
}

