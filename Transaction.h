
#ifndef Transaction_H_
#define Transaction_H_
class Transaction //same as AItem in my code
{
public:
	int id;
	int count; //total length
	int *items;
	
	Transaction(int id, int count, int items[]);
	~Transaction();
};
#endif
