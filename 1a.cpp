#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
void menu();
void userInput(vector<int>& arr);
void timeTests();
void printArr(vector<int> & v);
vector<int> insertionSort(vector<int> & v);
vector<int> mergeSort(vector<int> v, int p, int r);


/********************************************************************
* @descr - displays menu for the user. calls appropriate functions 
* according to the user's menu choice: 
*   1) time tests 2) insertion sort 3) merge sort 4) quit
*********************************************************************/
void menu() {
    char choice;
    vector<int> arr;
    while (true) {
        arr.clear();
        choice = 'Q';
        cout << "Enter T to run time tests \n"
            << "Enter I to accept user input and perform an insertion sort \n"
            << "Enter M to accept user input and perform a merge sort \n"
            << "Enter Q to quit" << endl;
        cin >> choice;
        switch (choice) {
            case 'T':
                cout << "Running Time Tests" << endl;
                timeTests();
                break;
            case 'I':
                cout << "Running Insertion Sort" << endl;
                userInput(arr);
                arr = insertionSort(arr);
                printArr(arr);
                break;
            case 'M':
                cout << "Running Merge Sort" << endl;
                userInput(arr);
                arr = mergeSort(arr,0,arr.size()-1);
                printArr(arr);
                break;
            case 'Q': return;
        }
    }
}

/*********************************************************************
* @descr - main purpose is to read an array of n elements. If an 
* element is equal to -999, then we stop reading elements and return
* the array by reference to the calling function.
*********************************************************************/
void userInput(vector<int>& arr) {
    arr.clear();
    int elem;
    while (cin >> elem && elem != -999)
        arr.push_back(elem);
}

/********************************************************************
* @descr - prints an array
*********************************************************************/
void printArr(vector<int>& v) {
    cout << "Array: ";
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << ' ';
    cout << endl;
}

/********************************************************************
* @descr - runs time tests
*********************************************************************/
void timeTests() { 

}

/********************************************************************
* @descr - returns true if array is sorted and false otherwise. Used
* in timeTests function. 
*********************************************************************/
bool isSorted(vector<int> & v) {
    for (int i = 1; i < v.size(); i++) 
        if (v[i] < v[i - 1])
            return false;
    return true;
}

/********************************************************************
* @description - sorts an array using insertion sort
* @params v - unsorted array 
*********************************************************************/
vector<int> insertionSort(vector<int> & v) {
    int key, i;
    for (int j = 1; j < v.size(); j++) {
        key = v[j];
        i = j - 1;
        while (i >= 0 && v[i] > key) {
            v[i + 1] = v[i];
            i--;
        }
        v[i + 1] = key;
    }
    return v;
}

/********************************************************************
* @description - sorts an array using merge sort
* @params v - unsorted array
*********************************************************************/
vector<int> mergeSort(vector<int> v, int p, int r) {
    if (p < r) {
        vector<int> left, right;
        int q = floor((p + r) / 2);
        std::copy(v.begin(), v.begin() + q, left.begin());
        std::copy(v.begin() + q + 1, v.begin()+ r, right.begin());

        left = mergeSort(left, p, q);
        right = mergeSort(right, q + 1, r);

        inplace_merge(left.begin(), right.begin(), v.begin());
    }
    return v;
}

/********************************************************************
* @descr - Begins execution of the program. calls the menu function
* which is an infinite loop until the user decides to quit. 
********************************************************************/
int main() {
    menu();
    return 0;
}

