#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <climits>

using namespace std;
void menu();
void userInput(vector<int>& arr);
void timeTests();
void printArr(vector<int> & v);
vector<int> insertionSort(vector<int> & v);
void merge(vector<int>& v, int p, int q, int r);
void mergeSort(vector<int> & v, int p, int r);
vector<int> makeTest(int len);
void correctnessTests();
bool isSorted(vector<int>& v, int len);

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
            << "Enter C to run correction tests \n"
            << "Enter Q to quit" << endl;
        cin >> choice;
        switch (toupper(choice)) {
            case 'T':
                cout << "Time Tests" << endl;
                timeTests();
                break;
            case 'I':
                cout << "Insertion Sort" << endl;
                userInput(arr);
                arr = insertionSort(arr);
                printArr(arr);
                break;
            case 'M':
                cout << "Merge Sort" << endl;
                userInput(arr);
                //arr = mergeSort(arr);
                mergeSort(arr, 0, arr.size()-1);
                printArr(arr);
                break;
            case 'C':
                cout << "Correctness Tests" << endl;
                correctnessTests();
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
void userInput(vector<int> & arr) {
    arr.clear();
    cout << "\nInput: ";
    int elem;
    while (cin >> elem && elem != -999)
        arr.push_back(elem);
}

/********************************************************************
* @descr - prints an array
*********************************************************************/
void printArr(vector<int> & v) {
    cout << "\nSorted: ";
    for (int i = 0; i < v.size(); i++)
        cout << v[i] << ' ';
    cout << endl << endl;
}

/********************************************************************
* @descr - runs time tests
*********************************************************************/
void timeTests() { 
    vector<int> unsorted, sorted, test;
    ofstream fout;
    fout.open("timeTests.csv");
    for (int i = 2; i <= 2000; i+=50) {
        fout << i << ", ";
        cout << i << ", ";
        test = makeTest(i);

        /******************* Time Insertion Sort ********************/
        unsorted = test;
        auto start = std::chrono::steady_clock::now();
        sorted = insertionSort(unsorted);
        auto end = std::chrono::steady_clock::now();
        std::chrono::duration<double> elapsed_seconds = end - start;
            
        fout << elapsed_seconds.count() << ", ";
        cout << elapsed_seconds.count() << ", ";

        /******************* Time Merge Sort ************************/
        unsorted = test;
        start = std::chrono::steady_clock::now();
        //sorted = mergeSort(unsorted);
        mergeSort(unsorted, 0, unsorted.size()-1);
        sorted = unsorted;
        end = std::chrono::steady_clock::now();
        elapsed_seconds = end - start;

        fout << elapsed_seconds.count() << "\n";
        cout << elapsed_seconds.count() << "\n";

    }
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
* @dscr - correctness tests: run sorting functions on many arrays of
* varrying sizes. 
**********************************************************************/
void correctnessTests() {
    vector<int> unsorted, sorted, test;
    for (int i = 1; i < 500; i++) {
        test = makeTest(i);
        cout << "test: ";
        printArr(test);
        /********************* Insertion Sort ************************/
        unsorted = test;
        sorted = insertionSort(unsorted);
        printArr(sorted);
        if (!isSorted(sorted,i)) {
            cout << "NOT SORTED!" << endl;
            return;
        }
        /******************** Merge Sort *****************************/
        unsorted = test;
        //sorted = mergeSort(unsorted);
        mergeSort(unsorted, 0, unsorted.size()-1);
        sorted = unsorted;
        printArr(sorted);
        if (!isSorted(sorted,i)) {
            cout << "NOT SORTED!" << endl;
            return;
        }
        cout << endl;
    }
    cout << "everything was sorted correctly" << endl;
}

/********************************************************************
* @descr - returns true if array is sorted and false otherwise. Used
* in timeTests function. 
*********************************************************************/
bool isSorted(vector<int> & v, int len) {
    if (v.size() != len) return false; 
    for (int i = 1; i < v.size(); i++) 
        if (v[i] < v[i - 1])
            return false;
    return true;
}

/********************************************************************
* GRADING:INSERT
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
* GRADING:MERGE
*********************************************************************/
void merge(vector<int>& v, int p, int q, int r) {
    vector<int> left(q - p + 1), right(r - q);
    for (int i = p, j = 0; i <= q; i++, j++) left[j] = v[i];
    for (int i = q + 1, j = 0; i <= r; i++, j++) right[j] = v[i];
    left.push_back(INT_MAX);
    right.push_back(INT_MAX);
    for (int i = p, j = 0, k = 0; i <= r; i++)
        v[i] = (left[j] <= right[k]) ? left[j++] : right[k++];
}

/********************************************************************
* @ GRADING:MERGE
*********************************************************************/
void mergeSort(vector<int> & v, int p, int r) {
    if (p < r) {
        int q = (p + r) / 2;
        mergeSort(v, p, q);
        mergeSort(v, q + 1, r);
        merge(v, p, q, r);
    }
}

/********************************************************************
* @descr - Begins execution of the program. calls the menu function
* which is an infinite loop until the user decides to quit. 
********************************************************************/
int main() {
    menu();
    return 0;
}

