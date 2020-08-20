#include <iostream>
using namespace std;

void menu();
void userInput(vector<int> & arr);
void timeTests();
vector<int> insertionSort();
vector<int> mergeSort();



void menu(){
  char choice;
  vector<int> arr;
  cout<<"Enter T to run time tests \n"
      <<"Enter I to accept user input and perform an insertion sort \n"
      <<"Enter M to accept user input and perform a merge sort \n"
      <<"Enter Q to quit"<<endl;
  cin>>choice;

  switch(choice){

    case 'T': 
      timeTests();
      break;
    case 'I':
      userInput(arr);
      arr = insertionSort();
      break;
    case 'M':
      userInput(arr);
      arr = mergeSort();
      break;
    case 'Q': return;
  }
}

void userInput(vector<int> & arr){
  arr.clear();
  int elem;
  while(cin>>elem && elem!=-999)
    arr.push_back(elem);
}

void timeTests(){ }

vector<int> insertionSort();

vector<int> mergeSort();



int main(){
  menu();
}




