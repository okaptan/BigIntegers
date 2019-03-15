#ifndef INTSLLIST_H
#define INTSLLIST_H
#include<iostream>
class IntSLLNode {
public:
    IntSLLNode() {
        next = 0;
    }
    IntSLLNode(int data, IntSLLNode *ptr = 0) {
        info = data; next = ptr;
    }
    int info;
    IntSLLNode *next;
};

class IntSLList {
public:
    IntSLList() {
        head = tail = 0;
    }
    ~IntSLList();
    int isEmpty() {
        return head == 0;
    }
    IntSLLNode *first_node()
    {
    	return head;
	}
    IntSLLNode *last_node()
    {
    	return tail;
	}
	int size()
	{
		int count=0;
		IntSLLNode* p=head;
		while (p!=NULL)
		{
			count++;
			p = p->next;
		}
		return count;
	}
	void *copyTo(IntSLList *bigInt)
	{
		IntSLLNode *node=head;
		while(node!=NULL)
		{
			bigInt->addToTail(node->info);
			node=node->next;
		}
	}
	bool is_small_from(IntSLList *bigInt)
	{
		if(size() < bigInt->size())
			return true;
		if(size() > bigInt->size())
			return false;
		else
		{
			IntSLLNode *node1=head;
			IntSLLNode *node2=bigInt->first_node();
			while(node1!=NULL)
			{
				int n1=node1->info;
				int n2=node2->info;

				if(n1<n2)
					return true;
				if(n1>n2)
					return false;
				if(n1==n2)
				{
					node1=node1->next;
					node2=node2->next;
				}
			}
		}

		return true;
	}
    void addToHead(int);
    void addToTail(int);
    int  deleteFromHead();
    int  deleteFromTail();
private:
    IntSLLNode *head, *tail;
};

#endif
