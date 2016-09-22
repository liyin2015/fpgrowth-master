//
// Created by Li Yin Sulimowicz on 9/16/16.
//

#include "io_manager.h"
#include <vector>

double str2double(char const *  str)
{
    int x=0;
    double y=0;
    int j;
    int decimalnum=1;
    bool pointExist=false;
    bool bFirst = true;
    bool bNegative = false;
    while(*str)
    {
        if (*str>='0' && *str<='9')
        {
            if(pointExist)
            {
                j=(int)(*(str))-48;
                y=y+j*std::pow(0.1,decimalnum);
                decimalnum++;
            }
            else
            {
                x=x*10+*str-48;
            }
        }
        else if(*str=='.')
        {
            pointExist=true;
        }
        else if(*str=='-'&&bFirst)
        {
            bNegative = true;
            bFirst = false;
        }
        else
        {
            return -1;//unrecognize str
        }
        str++;
    }
    if(bNegative)
    {
        return -(x+y);
    }
    return x+y;
}

int read_strfile(DVector& D, int& totalD, std::string filename)//in
{
    totalD=0;
    ifstream  inputfile(filename);

    if(!inputfile)
    {
        cout << "cannot open file."<<endl;
        return -1;
    }

    char ch;

    inputfile.get(ch);
    while(!inputfile.eof())
    {
        std::ostringstream  ss;
        ss<<ch;
        if(ch=='\n')
        {
            totalD++;
        }
        inputfile.get(ch);
    }
    inputfile.close();
    totalD+=1;

    cout<<"totalD"<<totalD<<endl;
    D = DVector(totalD);

    //read the second time
    ifstream  in(filename);

    if(!in)
    {
        cout << "cannot open file."<<endl;
        return -1;
    }

    int lines = 0;
    std::string str = "";
    in.get(ch);
    while(!in.eof())
    {
        std::ostringstream  ss;
        ss<<ch;
        if(ch=='\n') //transfer former input to num
        {
            D.AddOneItem((int)str2double(str.c_str()),lines);
            str.clear();
            lines++;
        }
            /*else if(ch==' '||ch == ',')
            {
                D.AddOneItem((int)str2double(str.c_str()),lines);
                str.clear();
            }*/

        else if(ch == ',')
        {
            D.AddOneItem((int)str2double(str.c_str()),lines);
            str.clear();
        }
        else if((ch>='0'&&ch <= '9'))
        {
            str.append(ss.str());
        }
        in.get(ch);
    }
    D.AddOneItem((int)str2double(str.c_str()),lines);
    in.close();
    return 0;
}


/*********************************DVector*********************************************/
DVector::DVector(int total)
{
    totalD = total;
    D_orig = new vector<int>[totalD];
}
DVector::DVector()
{
    totalD=0;
    D_orig = NULL;
}
DVector::~DVector()
{
    if(D_orig!= NULL)
    {
        delete[] D_orig;
        D_orig = NULL;
    }
}
DVector::DVector(const DVector& m)
{
    if(this != &m)
    {
        totalD = m.totalD;
        D_orig= new vector<int>[totalD];
        for(int i=0;i<totalD;i++)
        {
            D_orig[i].clear();
            vector<int>::iterator  ite = m.D_orig[i].begin();
            for(;ite!=m.D_orig[i].end();ite++)
            {
                D_orig[i].push_back(*ite);
            }
        }
    }

}
const DVector& DVector::operator=(const DVector& m)
{
    if(this != &m)
    {
        if(totalD!=0&&D_orig!=NULL)
        {
            delete[] D_orig;
            D_orig = NULL;
        }
        totalD = m.totalD;
        D_orig= new vector<int>[totalD];
        for(int i=0;i<totalD;i++)
        {
            D_orig[i].clear();
            vector<int>::iterator  ite = m.D_orig[i].begin();
            for(;ite!=m.D_orig[i].end();ite++)
            {
                D_orig[i].push_back(*ite);
            }
        }
    }
    return *this;
}

void DVector::deleteCol(const int col, int& minItemNo, int& maxItemNo)
{
    minItemNo = INT32_MAX;
    maxItemNo = -1;
    for(int i=0;i<totalD;i++)
    {
        D_orig[i].erase(D_orig[i].begin()+col); //col started from zero


    }
    for(int i=0;i<totalD;i++)
    {
        for(int j=0;j<D_orig[i].size();j++)
            //vector<int>::iterator iter = D_orig[i].begin();
        //for(;iter!=D_orig[i].end();++iter)
        {
            if(D_orig[i][j]>maxItemNo)
                maxItemNo = D_orig[i][j];
            if(D_orig[i][j]<minItemNo)
                minItemNo = D_orig[i][j];
        }

    }
    cout<<"min"<<minItemNo<<"max"<<maxItemNo<<endl;
    return;

}
void DVector::print()
{
    for(int i=0;i<totalD;i++)
    {
        cout<<endl;
        cout<<"row = "<<i<<endl;
        vector<int>::iterator ite = D_orig[i].begin();
        for(;ite!= D_orig[i].end();ite++)
        {
            cout<<*ite<<"\t";
        }
        cout<<endl;
    }
}
//void AddOneRow(string& item);
void DVector::AddOneItem(int item, int index)
{
    if(index>=totalD)
    {
        cout<<"sorry, no enough space"<<endl;
        return;
    }
    D_orig[index].push_back(item);
}
bool DVector::FindInSingleD(int index, int& item)
{
    vector<int>::iterator ite = D_orig[index].begin();
    for(;ite!= D_orig[index].end();ite++)
    {
        if(*ite==item)
        {
            return true;
        }
    }
    return false;
}

void bubble_sort(hElement **items, int itemCount)
{
    bool sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (int i = 1; i < itemCount; i++)
        {
            if (items[i]->sup > items[i-1]->sup)
            {
                hElement* t = items[i];
                items[i] = items[i-1];
                items[i-1] = t;
                sorted = false;
            }
        }
    }
}

void bubble_sort(vector<hElement*>& dataset)
{
    bool sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (int i = 1; i < dataset.size(); i++)
        {
            if (dataset[i]->sup > dataset[i-1]->sup)
            {
                hElement* t = dataset[i];
                dataset[i] = dataset[i-1];
                dataset[i-1] = t;
                sorted = false;
            }
        }
    }
}

void bubble_sort(Header& header)
{
    bool sorted = false;
    while (!sorted)
    {
        sorted = true;
        for (int i = 1; i < header.items.size(); i++)
        {
            if (header.items[i].sup > header.items[i-1].sup)
            {
                hElement t = header.items[i];
                header.items[i] = header.items[i-1];
                header.items[i-1] = t;
                sorted = false;
            }
        }
    }
}

void bubble_sort (int arr[], int n)

{

    for (int i = 0; i < n; ++i)

        for (int j = 0; j < n - i - 1; ++j)

            if (arr[j] > arr[j + 1])

            {

                int temp = arr[j];

                arr[j] = arr[j + 1];

                arr[j + 1] = temp;

            }

}