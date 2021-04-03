#pragma once
#include <iostream> 
#include "ItemType.h"
using namespace std;
class Stack
{
private:
	ItemType* top;
public:
	Stack();
	~Stack();
	void MakeEmpty();
	bool IsEmpty();
	void Push(ItemType Item);
	ItemType pop();
};

