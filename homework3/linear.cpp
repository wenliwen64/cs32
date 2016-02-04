#include <iostream>
using namespace std;

bool somePredicate(double x){ 
    return x < 0;
}

bool anyTrue(const double a[], int n){
    if(n <= 0) 
	return false;
    if(somePredicate(a[0]))
	return true;
    return anyTrue(a + 1, n - 1);
}

int countTrue(const double a[], int n){
    if(n <= 0)
	return 0;
    if(somePredicate(a[0]))
	return countTrue(a + 1, n - 1) + 1;
}

int firstTrue(const double a[], int n){
    if(n <= 0)
	return -1;
    if(somePredicate(a[0]))
	return 0;
    return firstTrue(a + 1, n - 1) + 1;
}

int indexOfMin(const double a[], int n){
    if(n <= 0)
	return -1;
    int ind = indexOfMin(a+1, n-1);
    cout << ind << endl;
    if(ind < 0) 
	return 0;
    if(a[0] <= a[ind + 1])
        return 0;
    else 
	return ind + 1;
}

bool includes(const double a1[], int n1, const double a2[], int n2){
    if(n1 <= 0){
	if(n2 <= 0)
	    return true;
	else
	    return false;
    }
    if(n2 <= 0)
	return true;
    if(a1[0] == a2[0]){
	return includes(a1 + 1, n1 - 1, a2 + 1, n2 - 1);
    }
    else{
	return includes(a1 + 1, n1 - 1, a2, n2);
    }

}

int main(){
    double a[8] = {1, 1, 2.3, 4.5, 1.6, .7, .6, .6};
    cout << indexOfMin(a, 8) << endl;

    double a1[7] = {10, 50, 40, 20, 50, 40, 30};
    double a2[3] = {50, 20, 30};
    if(includes(a1, 7, a2, 3))
	cout << "good" << endl;
    else
	cout << "bad" << endl;
}
