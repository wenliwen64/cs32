#include <iostream>
using namespace std;

void order(double a[], int n);
int countIncludes(const double a1[], int n1, const double a2[], int n2);
int main(){
    double a[7] = {.1, .1, .2, .2, .3, .4, .5};
    order(a, 7);
    for(int i = 0; i < 7; i++)
	cout << a[i] << " " ;
    cout << endl;

    double a0 = 1;
    order(a, 1); 
    cout << a0 << endl;

    double a1[7] = {10, 50, 40, 20, 50, 40, 30};
    double a2[3] = {10, 40, 30};
    cout << countIncludes(a1, 7, a2, 3) << endl;
    cout << countIncludes(a1, 7, a2, 0) << endl;
}
