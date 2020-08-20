#include <iostream>
using namespace std;

void menu();




void menu(){
  char choice;
  cout<<"Enter T to run time tests \nEnter I to accept user input and perform an insertion sort \nEnter M to accept user input and perform a merge sort \nEnter Q to quit"<<endl;
  cin>>choice;
  vector<int> arr;

  switch(choice){

    case 'T': 
      timeTests();
      break;
    case 'I':
      userInput(arr);
      insertionSort();
      break;
    case 'M':
      userInput(arr);
      mergeSort();
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





vector<int> insertionSort();




int main(){



      

  return 0;
}




