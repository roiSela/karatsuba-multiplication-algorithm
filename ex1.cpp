#define _CRT_SECURE_NO_WARNINGS
#include <iostream> 
#include <cstring>
#include "Stack.h"
#include <chrono>
#include <fstream>
#include <iomanip>
#include <math.h>
using namespace std;

class numarray
{
public:
	char* arr;
	bool setarr(int n);
};



/*functions related to regular multipication*/
void regularmultiplication(char* x, char* y, int n);

///////////////////////////////////////////////////////////////////

/* functions related to recursive karatsuba*/

void adustTheLengthOfGivenArrays(char* a, char* b);// add leading zeros if needed 

void add_zeros(char* a, int n);
void remove_zeros(char* a);
void multeplyBy10powN(char* a, int n); //returns a * 10^n 

void sub(char* a, char* b, char* res);
void karatsubaRec(char* x, char* y, char* res,int n);
void sub(char* a, char* b, char* res);
//////////////////////////////////////////////////

/* functions related to the itirative karatsuba*/

void karatsubaItirative(char* x, char* y, int n, char* res);

//////////////////////////////////////////////////
/*general functions:*/

int howmanydigits(int num);//this function recives a number and returns how many digits it has
int check_n(int n); // checks if the number of digits that was inputed contains zeros at the beggining
bool isdigit(char digit);//checks if a char is a digit between 0-9
char* createarray(int len);
void reverse(int arr[], int n); //utility function to reverse elements of an array








int main() {
	int n = 0;
	numarray x, y;
	char* res;

	/*in the mama tests first there is a space and then the user enters the number thats the only reason why there is a ch and cin.get in here.. */
	char ch;
	ch = cin.get();
	//////////////

	/*cout << "please enter the number of the digits of both numbers:" << endl;*/
	n = check_n(n);
	if (x.setarr(n) == false)
	{
		cout << "wrong output" << endl;
		exit(-1);
	}
	else
	{
		if (y.setarr(n) == false)
		{
			cout << "wrong output" << endl;
			exit(-1);
		}
		else
		{
			/////////////////////////////regular multipication//////////////////////////////////////////
			auto start = chrono::high_resolution_clock::now();
			// unsync the I/O of C and C++.
			ios_base::sync_with_stdio(false);

			cout << "long multiplication: x * y = ";
			regularmultiplication(x.arr, y.arr, n);// Here you put the name of the function you wish to measure


			auto end = chrono::high_resolution_clock::now();
			// Calculating total time taken by the program.
			double time_taken =	chrono::duration_cast<chrono::nanoseconds>(end - start).count();
			time_taken *= 1e-9;
			ofstream myfile("Measure.txt"); // The name of the file
			myfile << "Time taken by function regularmultiplication is : " << fixed
				<< time_taken << setprecision(9);
			myfile << " sec" << endl;
			myfile.close();
////////////////////////////////////////////////////////////////////////////////////////////////////////////

			/////////////////////////////rec karatsuba//////////////////////////////////////////
			char* xch;
			char* ych;
			xch = createarray(n + 1);
			ych = createarray(n + 1);
			for (int i = 0; i < n; i++)
			{
				xch[i] = x.arr[i];
				ych[i] = y.arr[i];
			}
			xch[n] = 0;
			ych[n] = 0;
			res = createarray(2 * (n + 1));
			cout << "Karatsuba (recursive):x * y =";

			start = chrono::high_resolution_clock::now();
			// unsync the I/O of C and C++.
			ios_base::sync_with_stdio(false);

			karatsubaRec(xch, ych, res,n);


			 end = chrono::high_resolution_clock::now();
			// Calculating total time taken by the program.
			 time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
			time_taken *= 1e-9;
			myfile << "Time taken by function Karatsuba (recursive) is : " << fixed
				<< time_taken << setprecision(9);
			myfile << " sec" << endl;
			myfile.close();

			


			for (int i = 0; i < 2 * (n + 1); i++)
			{
				cout << res[i];
			}




			
		/////////////////////////////////////// itirative karatsuba using stack ////////////////////////////////////////
			
			cout << "\n";
			cout << "Karatsuba (iterative):x * y =";

			 start = chrono::high_resolution_clock::now();
			// unsync the I/O of C and C++.
			ios_base::sync_with_stdio(false);

			karatsubaItirative(xch, ych, n, res);


			end = chrono::high_resolution_clock::now();
			// Calculating total time taken by the program.
			time_taken = chrono::duration_cast<chrono::nanoseconds>(end - start).count();
			time_taken *= 1e-9;
			myfile << "Time taken by function regularmultiplication is : " << fixed
				<< time_taken << setprecision(9);
			myfile << " sec" << endl;
			myfile.close();

		


			for (int i = 0; i < 2 * (n + 1); i++)
			{
				cout << res[i];
			}

			delete[] res;
			delete[] xch;
			delete[] ych;
			delete[] x.arr;
			delete[] y.arr;
		}
	}

	return 0;
}

void regularmultiplication(char* num1, char* num2, int n)
{
	char* out;
	out = new char[2 * n];
	int len1 = n;
	int len2 = n;
	if (n == 0)
	{
		cout << "0" << endl;

	}

	// will keep the result number in vector 
	// in reverse order 
	int* result;
	result = new int[2 * n];
	for (int i = 0; i < 2 * n; i++)
	{
		result[i] = 0;
	}

	// below two indexes are used to find positions 
	// in result.  
	int i_n1 = 0;
	int i_n2 = 0;

	// go from right to left in num1 
	for (int i = len1 - 1; i >= 0; i--)
	{
		int carry = 0;
		int n1 = num1[i] - '0';

		// to shift position to left after every 
		// multiplication of a digit in num2 
		i_n2 = 0;

		// go from right to left in num2              
		for (int j = len2 - 1; j >= 0; j--)
		{
			// take current digit of second number 
			int n2 = num2[j] - '0';

			// multiply with current digit of first number 
			// and add result to previously stored result 
			// at current position.  
			int sum = n1 * n2 + result[i_n1 + i_n2] + carry;

			// carry for next iteration 
			carry = sum / 10;

			// store result 
			result[i_n1 + i_n2] = sum % 10;

			i_n2++;
		}

		// store carry in next cell 
		if (carry > 0)
			result[i_n1 + i_n2] += carry;

		// to shift position to left after every 
		// multiplication of a digit in num1. 
		i_n1++;
	}

	bool hasappeard = false;


	reverse(result, 2 * n);

	for (int i = 0; i < 2 * n; i++)
	{
		if (result[i] != 0)
		{
			hasappeard = true;
			cout << result[i];
		}
		else
		{
			if (hasappeard == true)
			{
				cout << result[i];
			}
			if (hasappeard == false && i == 2 * n - 1)
			{
				cout << result[i];
			}

		}

	}

	delete[] result;
	delete[] out;
	cout << "\n";

}

int check_n(int n)
{
	n = 0;
	int log = 0, phs = 2;
	char* arr, * temp;
	arr = new char[phs];
	char ch;

	ch = cin.get();

	if ((ch - '0') == 0)
	{
		cout << "wrong output" << endl;
		exit(-1);
	}
	while (ch != '\n')
	{
		log++;
		if (log >= phs)
		{
			phs *= 2;
			temp = new char[log];
			for (int i = 0; i < log; i++)
			{
				temp[i] = arr[i];
			}
			delete[]arr;
			arr = new char[phs];
			for (int i = 0; i < log; i++)
			{
				arr[i] = temp[i];
			}
			delete[]temp;
		}
		arr[log - 1] = ch;
		ch = cin.get();
	}

	int counter = 0;
	for (int i = log - 1; i >= 0; i--)
	{
		n += (arr[i] - '0') * (int)pow(10, counter);
		counter++;
	}
	delete[]arr;
	return n;
}

bool numarray::setarr(int n)
{
	int log = 0;
	arr = new char[n];
	char ch;
	ch = cin.get();
	while (ch != '\n')
	{
		if (isdigit(ch))
		{
			log++;
			if (log > n)
			{
				cout << "wrong output" << endl;
				exit(-1);
			}
			arr[log - 1] = ch;
		}
		else
		{
			cout << "wrong output" << endl;
			exit(-1);
		}

		ch = cin.get();
	}

	if (log != n)
	{
		return false;
	}
	return true;
}



//utility function to reverse elements of an array
void reverse(int arr[], int n)
{
	int temp;
	int low, high;
	for (low = 0, high = n - 1; low < high; low++, high--)
	{
		temp = arr[low];
		arr[low] = arr[high];
		arr[high] = temp;
	}
}

bool isdigit(char digit)
{
	if (digit >= '0' && digit <= '9')
	{
		return true;
	}
	else
	{
		return false;
	}
}

int chararrtoint(char* arr, int n)
{
	int num = 0;
	int j = 0;
	for (int i = n - 1; i >= 0; i--)
	{
		num = num + ((arr[i] - '0') * (int)(pow(10, j)));
		j++;
	}
	return num;

}

int howmanydigits(int num)
{
	int counter = 0;
	while (num > 0)
	{
		num = num / 10;
		counter++;
	}
	return counter;
}

//////////////////
/* functions related to recursive karatsuba*/

void add_zeros(char* a, int n)
{
	int lena = strlen(a);
	for (int i = lena - 1 + n; i >= n; --i)
	{
		a[i] = a[i - n];
	}
	a[lena + n] = 0;
	for (int i = 0; i < n; ++i)
	{
		a[i] = '0';
	}
}

void remove_zeros(char* a)
{
	int lena = strlen(a);
	int ind = 0;
	while (ind < lena && a[ind] == '0')
	{
		++ind;
	}
	for (int i = ind; i < lena; ++i)
	{
		a[i - ind] = a[i];
	}
	a[lena - ind] = 0;
}

void sum(char* a, char* b, char* res)
{
	int temp;
	char* chartemp;
	int lena = strlen(a);
	int lenb = strlen(b);

	if (lena < lenb)
	{

		//swap(a,b);
		chartemp = a;
		a = b;
		b = chartemp;
		//swap(lena,lenb)
		temp = lena;
		lena = lenb;
		lenb = temp;
	}

	int toadd = 0;
	for (int inda = lena - 1, indb = lenb - 1; inda >= 0; --inda, --indb)
	{
		int x = a[inda] - '0';
		int y = indb >= 0 ? b[indb] - '0' : 0;

		int cur = x + y + toadd;

		if (cur >= 10)
		{
			toadd = 1;
			cur -= 10;
		}
		else
		{
			toadd = 0;
		}

		res[inda] = cur + '0';
	}

	if (toadd == 1)
	{
		add_zeros(res, 1);
		res[0] = '1';
	}
}

//assume that a > b 
void sub(char* a, char* b, char* res)
{
	int lena = strlen(a);
	int lenb = strlen(b);


	int tosub = 0;
	for (int inda = lena - 1, indb = lenb - 1; inda >= 0; --inda, --indb)
	{
		int x = a[inda] - '0';
		int y;
		if (indb >= 0) 
		{
			y = (b[indb] - '0');
		}			
		else 
		{
			y = 0; 
		}

		if (tosub == 1)
		{
			x--;
		}
		int cur;
		if (x < y)
		{
			cur = x + 10 - y;
			tosub = 1;
		}
		else
		{
			cur = x - y;
			tosub = 0;
		}

		res[inda] = cur + '0';
	}
}

//returns a * 10^n 
void multeplyBy10powN(char* a, int n)
{
	int lena = strlen(a);
	if (lena == 1 && a[0] == '0')
	{
		return;
	}
	for (int i = lena; i < lena + n; ++i)
	{
		a[i] = '0';
	}
	a[lena + n] = 0;
}

//creates an array with given len
char* createarray(int len)
{
	char* res = new char[len];
	for (int i = 0; i < len; i++)
	{
		res[i] = 0;
	}
	return res;
}

// add leading zeros if needed 
void adustTheLengthOfGivenArrays(char* a, char* b)
{
	int lena = strlen(a);
	int lenb = strlen(b);
	int n;
	if (lena > lenb)
	{
		n = lena;
	}
	else
	{
		n = lenb;
	}
	add_zeros(a, n - lena);
	add_zeros(b, n - lenb);
}

void karatsubaRec(char* x, char* y, char* res,int n)
{
	adustTheLengthOfGivenArrays(x, y);
	int len = strlen(x);
	if (len == 1)
	{
		int value;
		value= (x[0] - '0') * (y[0] - '0');
		if (value < 10) //if value is only one digit
		{
			res[0] = value + '0';
		}
		else
		{
			res[0] = (value / 10) + '0';
			res[1] = (value % 10) + '0';
		}
	}
	else
	{
		int rightsize = len / 2;

		int leftsize = len - rightsize;

		char* xl = createarray(len); //this is a

		char* xr = createarray(len);//this is b

		char* yl = createarray(len); //this is c

		char* yr = createarray(len); //this is d

		//now we feel a b c and d
		strncpy(xl, x, leftsize);
		strcpy(xr, x + leftsize);
		strncpy(yl, y, leftsize);
		strcpy(yr, y + leftsize);


//now we create arrays for the multipication of a c b and d
		int maxl = 3 * len;
		char* p1 = createarray(maxl);
		char* p2 = createarray(maxl);
		char* p3 = createarray(maxl);

		karatsubaRec(xl, yl, p1,n);// we comupute recurivly ac
		karatsubaRec(xr, yr, p2,n);//we cumpute recursivly bd

		char* tmp1 = createarray(maxl);
		char* tmp2 = createarray(maxl);

		sum(xl, xr, tmp1);
		sum(yl, yr, tmp2);
		karatsubaRec(tmp1, tmp2, p3,n);
		sub(p3, p1, p3);
		sub(p3, p2, p3);
		multeplyBy10powN(p3, rightsize);
		multeplyBy10powN(p1, 2 * rightsize);
		sum(p1, p2, res);
		sum(res, p3, res);
		remove_zeros(res);

		//now we must free the memory to avoid memory loss
		delete[] p1;
		delete[] p2;
		delete[] p3;
		delete[] xl;
		delete[] xr;
		delete[] yl;
		delete[] yr;
		delete[] tmp1;
		delete[] tmp2;
		
	}
}

void karatsubaItirative(char* x, char* y, int n, char* res)
{

	Stack S; // Stack which simulates the recursion.
	ItemType Curr; // Values of current recursive call
	ItemType Next; // Values of next recursive call.
	adustTheLengthOfGivenArrays(x, y);
	Curr.x = x;
	Curr.y = y;
	Curr.res = res;
	Curr.line = 1;
	Curr.len = strlen(x);
	S.Push(Curr);
	while (!S.IsEmpty()) {
		
		Curr = S.pop();
		if (Curr.line == 1) {
			if (Curr.len == 1)//start
			{
				Curr.val = (Curr.x[0] - '0') * (Curr.y[0] - '0');
				if (Curr.val < 10)
				{
					Curr.res[0] = Curr.val + '0';
				}
				else
				{
					Curr.res[0] = (Curr.val / 10) + '0';
					Curr.res[1] = (Curr.val % 10) + '0';
				}
			}
			else {
				Curr.line = 2;//after first
				Curr.xl = createarray(Curr.len);
				Curr.xr = createarray(Curr.len);
				Curr.yl = createarray(Curr.len);
				Curr.yr = createarray(Curr.len);

				Curr.rightsize = Curr.len / 2;
				Curr.leftsize = Curr.len - Curr.rightsize;

				strncpy(Curr.xl, Curr.x, Curr.leftsize);
				strcpy(Curr.xr, Curr.x + Curr.leftsize);
				strncpy(Curr.yl, Curr.y, Curr.leftsize);
				strcpy(Curr.yr, Curr.y + Curr.leftsize);
				Curr.maxl = 3 * Curr.len;
				Curr.p1=createarray(Curr.maxl);
				Curr.p2 = createarray(Curr.maxl);
				Curr.p3 = createarray(Curr.maxl);
				S.Push(Curr);
				//now updating the next recursive call

				
				
				adustTheLengthOfGivenArrays(Curr.xl, Curr.yl);
				Next.line = 1;
				Next.x = Curr.xl;
				Next.y = Curr.yl;
				Next.res = Curr.p1;
				Next.len = strlen(Next.x);
				S.Push(Next);
			}
		}
		else if (Curr.line == 2) {//after first recursive call

			//karatsuba(xr, yr, p2);
			Curr.line = 3;//after second	
			S.Push(Curr);
			//now updating the next recursive call
			adustTheLengthOfGivenArrays(Curr.xr, Curr.yr);
			Next.line = 1;
			Next.x = Curr.xr;
			Next.y = Curr.yr;
			Next.res = Curr.p2;		
			Next.len = strlen(Next.x);
			S.Push(Next);
		}
		else if (Curr.line == 3) {//after second  recursive call
			Curr.line = 4;			
			Curr.tmp1 = createarray(Curr.maxl);
			Curr.tmp2 = createarray(Curr.maxl);
			sum(Curr.xl, Curr.xr, Curr.tmp1);
			sum(Curr.yl, Curr.yr, Curr.tmp2);
			S.Push(Curr);
			//karatsuba(tmp1, tmp2, p3);
			adustTheLengthOfGivenArrays(Curr.tmp1, Curr.tmp2);
			Next.line = 1;
			Next.x = Curr.tmp1;
			Next.y = Curr.tmp2;
			Next.res = Curr.p3;
			Next.len = strlen(Next.x);
			S.Push(Next);
	
		}
		else if(Curr.line == 4)//after third recursive call
		{
			Curr.line = 5;
			sub(Curr.p3, Curr.p1, Curr.p3);
			sub(Curr.p3, Curr.p2, Curr.p3);
			multeplyBy10powN(Curr.p3, Curr.rightsize);
			multeplyBy10powN(Curr.p1, 2 * Curr.rightsize);
			sum(Curr.p1, Curr.p2, Curr.res);
			sum(Curr.res, Curr.p3, Curr.res);
			remove_zeros(Curr.res);

		
			delete[] Curr.xl;
			delete[] Curr.xr;
			delete[] Curr.yl;
			delete[] Curr.yr;
			delete[] Curr.tmp1;
			delete[] Curr.tmp2;
			delete[] Curr.p1;
			delete[] Curr.p2;
			delete[] Curr.p3;
					
		}
		else if (Curr.line == 5)//after third
		{
			//in this case do nothing
		}
	}

}
