#include "Stack.h"

Stack::Stack()
{
	top = nullptr;
}
Stack::~Stack()
{
	MakeEmpty();
}

void Stack::MakeEmpty()
{
	ItemType* temp;
	while (top!=nullptr)
	{
		temp = top;
		top = top->next;
		delete temp;
	}
}

bool Stack::IsEmpty()
{
	if (top==nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}
void Stack::Push(ItemType Item)
{
	// Create new node temp and allocate memory  
	ItemType* temp;
	temp = new ItemType();


	// Initialize data into temp data field  
	temp->len = Item.len;
	temp->val = Item.val;

	temp->x = Item.x;
	temp->y = Item.y;
	temp->res = Item.res;


	temp->xl = Item.xl;
	temp->xr = Item.xr;
	temp->yl = Item.yl;
	temp->yr = Item.yr;


	temp->rightsize = Item.rightsize;
	temp->leftsize = Item.leftsize;
	temp->maxl = Item.maxl;

	temp->p1 = Item.p1;
	temp->p2 = Item.p2;
	temp->p3 = Item.p3;

	temp->tmp1 = Item.tmp1;
	temp->tmp2 = Item.tmp2;

	temp->line = Item.line;//first line of code;

	// Put top pointer reference into temp link  
	temp->next = top;

	// Make temp as top of Stack  
	top = temp;

}
ItemType Stack::pop()
{
	if (IsEmpty())
	{
		cout << "\nStack Underflow" << endl;
		exit(-10);
	}
	else
	{
		ItemType* temp1;
		ItemType temp;
		// Top assign into temp  
		temp1 = top;

		// Assign second node to top  
		top = top->next;
		// Destroy connection between 
		// first and second  
		temp1->next = nullptr;

		// Release memory of top node but first copy it to temp
		
		temp.len = temp1->len;
		temp.val = temp1->val;

		temp.x = temp1->x;
		temp.y = temp1->y;
		temp.res = temp1->res;


		temp.xl = temp1->xl;
		temp.xr = temp1->xr;
		temp.yl = temp1->yl;
		temp.yr = temp1->yr;


		temp.rightsize = temp1->rightsize;
		temp.leftsize = temp1->leftsize;
		temp.maxl = temp1->maxl;

		temp.p1 = temp1->p1;
		temp.p2 = temp1->p2;
		temp.p3 = temp1->p3;

		temp.tmp1 = temp1->tmp1;
		temp.tmp2 = temp1->tmp2;

		temp.line = temp1->line;//first line of code;

		delete[] temp1;
		return temp;
	}
}