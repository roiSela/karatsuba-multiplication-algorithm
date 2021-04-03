#pragma once
class ItemType
{// an item that will be stored in Stack which simulates the recursion.
public:
	int len;
	int val;

	char* x;
	char* y;
	char* res;

	char* xl;
	char* xr;
	char* yl;
	char* yr;


	int rightsize;
	int leftsize;
	int maxl;

	char* p1;
	char* p2;
	char* p3;

	char* tmp1;
	char* tmp2;

	int line;

	ItemType* next;

	ItemType();
	
};

