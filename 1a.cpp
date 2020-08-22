#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
void menu();
void userInput(vector<int>& arr);
void timeTests();
void printArr(vector<int> & v);
vector<int> insertionSort(vector<int> & v);
vector<int> mergeSort(vector<int> v);
vector<int> makeTest(int len);
vector<vector<int>> makeAllTests(int testCount);

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
                arr = mergeSort(arr);
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
void printArr(vector<int> & v) {
    cout << "Array: ";
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << ' ';
    cout << endl;
}

/********************************************************************
* @ descr - debugging and printing arrays
*********************************************************************/
void printD(vector<int>& v) {
    cout << "Debug: ";
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << ' ';
    cout << endl;
}

/********************************************************************
* @descr - runs time tests
*********************************************************************/
void timeTests() { 
    /*
    vector<vector<int>> tests = makeAllTests(100);
    for (int i = 0; i < tests.size(); i++) {
        cout << "test " << i + 1 << " : ";
        for (int j = 0; j < tests[i].size(); j++) {
            cout << tests[i][j] << ", ";
        }
        cout << endl;
    }*/

    vector<int> unsorted, sorted, test;
    for (int i = 2; i <= 100; i+=2) {
        test = makeTest(i);
        printD(test);


        /* Time Insertion Sort */
        unsorted = test;
        auto start = std::chrono::steady_clock::now();
        sorted = insertionSort(unsorted);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
        std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";

        /* Time Merge Sort */
        unsorted = test;
        start = std::chrono::steady_clock::now();
        sorted = mergeSort(unsorted);
        end = std::chrono::steady_clock::now();
        elapsed_seconds = end - start;
        std::cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
    }
    
    /*
    vector<int> t1 = { 99, 88, 77, 66, 55, 44, 33, 22, 11, 5, -999 };
    printArr(t1);
    vector<int> t2 = mergeSort(t1);
    printArr(t2);
    */
}

/********************************************************************
* @descr - makes all tests for timeTests function
* @param testCount - number of tests to generate
*********************************************************************/
vector<vector<int>> makeAllTests(int testCount) {
    vector<vector<int>> ret;
    for (int i = 2; i <= testCount; i+=2)
        ret.push_back(makeTest(i));
    return ret;
}

/********************************************************************
* @descr - generate one test
* @param len - length of array to make
*********************************************************************/
vector<int> makeTest(int len) {
    vector<int> ret;
    for (int i = 0; i < len; i++)
        ret.push_back(rand() % len);
    return ret;
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
vector<int> mergeSort(vector<int> v) {
    if (v.size()>1) {
        vector<int> left, right;
        for (int i = 0; i < (v.size()+1) / 2; i++) left.push_back(v[i]);
        for (int i = (v.size()+1)/2; i < v.size(); i++) right.push_back(v[i]);
        left = mergeSort(left);
        right = mergeSort(right);
        merge(left.begin(), left.end(), right.begin(), right.end(), v.begin());
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

