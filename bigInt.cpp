#include <iostream>
#include <fstream>
#include "intSLList.cpp"
using namespace std;

IntSLList *array_bigInt[10];
IntSLList *result;
char operators[10];
int count_bigInt=0,count_operator=0;
void freeBigInt(IntSLList* bigInt)
{
	delete bigInt;
}
IntSLList *createBigInt(string bigInt)
{
	IntSLList *new_bigInt=new IntSLList();
	for(int i=0;i<bigInt.length();i++)
	{
		int data = bigInt[i]-'0';
		new_bigInt->addToTail(data);
	}
	return new_bigInt;
}
void *updateBigInt(IntSLList *bigInt,int count_zero)
{
	while(count_zero!=0)
	{
		bigInt->addToHead(0);
		count_zero--;
	}
}
IntSLList *addBigInt(IntSLList *bigInt1,IntSLList *bigInt2)
{
	int on_hand=0;
	int sum=0;
	IntSLList *new_bigInt=new IntSLList();
	IntSLList *temp1=new IntSLList();
	IntSLList *temp2=new IntSLList();
	bigInt1->copyTo(temp1);
	bigInt2->copyTo(temp2);
	if(temp1->size() > temp2->size())
	{
		int n=temp1->size() - temp2->size();
		updateBigInt(temp2,n);
	}
	if(temp2->size() > temp1->size())
	{
		int n=temp2->size() - temp1->size();
		updateBigInt(temp1,n);
	}
	while(temp1->first_node()!=NULL)
	{
		int a=temp1->last_node()->info;
		int b=temp2->last_node()->info;
		sum=a+b+on_hand;
		if(sum>=10)
		{
			on_hand=1;
			sum=sum%10;
		}
		else
			on_hand=0;
		new_bigInt->addToHead(sum);
		temp1->deleteFromTail();
		temp2->deleteFromTail();
	}
	if(on_hand!=0)
		new_bigInt->addToHead(on_hand);

	freeBigInt(temp1);
	freeBigInt(temp2);

	return new_bigInt;
}
IntSLList *multiplyBigInt(IntSLList *bigInt1,IntSLList *bigInt2)
{
	IntSLList *sum=new IntSLList();
	IntSLList *one=new IntSLList();
	IntSLList *i=new IntSLList();
	IntSLList *number=new IntSLList();
	IntSLList *condition=new IntSLList();
	sum=createBigInt("0");
	one=createBigInt("1");
	i=createBigInt("1");
	if(bigInt1->size() > bigInt1->size())
	{
		bigInt2->copyTo(condition);
		bigInt1->copyTo(number);
	}
	else
	{
		bigInt1->copyTo(condition);
		bigInt2->copyTo(number);
	}
	while(i->is_small_from(condition))
	{
		sum=addBigInt(sum,number);
		i=addBigInt(i,one);
	}

	freeBigInt(one);
	freeBigInt(i);
	freeBigInt(number);
	freeBigInt(condition);

	return sum;
}

void read_file(char *file_name)
{
	ifstream file;
	file.open(file_name);
	if(file)
	{
		char character;
		string bigInt="";

		while(file.get(character))
		{
			if(character>='0' & character<='9')
			{
				bigInt+=character;
			}
			if(character=='+'||character=='*')
			{
				if(bigInt!="" & bigInt.length()<=50)
				{
					operators[count_operator]=character;
					array_bigInt[count_bigInt]=createBigInt(bigInt);
					count_operator++;
					count_bigInt++;
				}
				bigInt="";
			}
		}
		if(bigInt.length()<=50)
		{
			array_bigInt[count_bigInt]=createBigInt(bigInt);
			count_bigInt++;
		}
	}
	else
		cout<<"Input dosyasi hatasi!"<<endl;
	file.close();
}

void write_file(char *file_name)
{
	ofstream file;
	file.open(file_name);
	IntSLLNode *node=result->first_node();
	while(node!= NULL)
	{

		file<<node->info;
		node=node->next;
	}
	file.close();
}

int main()
{
	read_file("input.txt");
	result=new IntSLList();
	IntSLList *carpim=new IntSLList();
	result->addToHead(0);
	carpim->addToHead(1);
	char oncekiIslem=' ';
	char sonrakiIslem=' ';

	for(int i=0;i<count_operator;i++)
	{

		if(i < count_operator-1)
			sonrakiIslem=operators[i+1];
		if(i==count_operator-1)
			sonrakiIslem=' ';
		if(i > 0)
			oncekiIslem=operators[i-1];
		if(i==0)
			oncekiIslem=' ';
		if(operators[i]=='*')
		{

			carpim=multiplyBigInt(carpim, array_bigInt[i]);
			if(sonrakiIslem=='+' || sonrakiIslem==' ')
			{
				carpim=multiplyBigInt(carpim, array_bigInt[i+1]);
				result=addBigInt(result,carpim);
				carpim=new IntSLList();
				carpim=createBigInt("1");
			}
		}
		else
		{
			if(oncekiIslem=='+')
			{
				result=addBigInt(result, array_bigInt[i]);
				if(i==count_operator-1)
				{
					result=addBigInt(result, array_bigInt[i+1]);
				}
			}
			else if(oncekiIslem=='*')
			{
			/*	if(sonrakiIslem=='*')
				{
					result=addBigInt(result,carpim);
					carpim=new IntSLList();
					carpim=createBigInt("1");
				} */
				if(sonrakiIslem==' ')
				{
				//	result=addBigInt(result,carpim);
					result=addBigInt(result, array_bigInt[i+1]);
				}
			}
			else
			{
				result=addBigInt(result,array_bigInt[i]);
			}
		}
	}
	write_file("output.txt");

	return 0;
}
