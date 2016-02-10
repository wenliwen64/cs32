#include <iostream>
#include <cassert>
using namespace std;

bool anyTrue(const double a[], int n);
int countTrue(const double a[], int n);
int firstTrue(const double a[], int n);
int indexOfMin(const double a[], int n);
bool includes(const double a1[], int n1, const double a2[], int n2);
int main(){
    double* a0 = 0;
    assert(!anyTrue(a0, 0));// Anytrue
    assert(countTrue(a0, 0) == 0);
    assert(firstTrue(a0, 0) == -1);
    assert(indexOfMin(a0, 0) == -1);


    double a[8] = {11, -1, -1, 4.5, 1.6, .7, .6, .6};
    assert(anyTrue(a, 8));// Anytrue
    assert(countTrue(a, 8) == 2);
    assert(firstTrue(a, 8) == 1);
    assert(indexOfMin(a, 8) == 1);
    double a1[7] = {10, 50, 40, 20, 50, 40, 30};
    double a2[3] = {50, 20, 30};
    assert(includes(a1, 7, a2, 3));
    assert(includes(a2, 3, a0, 0));
    assert(includes(a0, -1, a0, 0));
    assert(includes(a1, 7, a1, 7));
    assert(!includes(a0, -1, a1, 7));
    if(includes(a1, 7, a2, 3))
	cout << "good" << endl;
    else
	cout << "bad" << endl;
}
