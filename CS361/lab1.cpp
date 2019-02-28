/*Jasmit Singh
  Lab 1 - Merge Sort and Quicksort
  Works with c++ 11 only (run with g++ -std-c++11 flag)
  Help Source - GeeksforGeeks.com and algorithms book*/

#include <iostream>
#include <fstream>
#include <ctime>
#include <chrono>

using namespace std;

void combine(int * array, int left, int middle, int right); //combines sorted array together after 

void auxMergeSort(int * array, int startIndex, int endIndex); //Recursive merge sort function

void print(int * array, int size); //Prints the array
bool sortHelper(int * array, int index); //recursive function to go through array
bool check(int * array); //checks if sorted
bool flgIsSorted(int * array); //user function tells if check returns true or false
void exchange(int * first, int * second); //switches two things in array

void auxQuickSort(int * array, int startIndex, int endIndex); //quicksort recrusive function

int partition(int * array, int startIndex, int endIndex); //quicksort algorithm that partition array
double takeTime(clock_t c1, clock_t c2);


const int max_size = 10000000; //the max amount of items possible 

int main() 
{ 
    int * array = new int[max_size]; //dynamic array that will hold values from file
    ifstream file; 
    file.open("lab1_data.txt");
    if(!file) //checks if file exists
    {
        cerr << "Not a valid file" << endl;
        return 0;
    }
    int num = 0;
    int index = 0;
    while(!file.eof()) //keeps going until it reaches end of the file
    {
        file >> array[index];
        index++;
        if(index == 2000000) //how many numbers to input
        {
            break;    
        }
    }
    int arraySize = index-1; 

    /*cout << "The initial array is" << endl; 
      print(array, arraySize); */

    cout << "\nBefore applying sort: ";
    flgIsSorted(array);
    int input = 0;
    do
    {
        cout << "\n1 for mergesort 2 for quicksort" << endl << "Input: ";
        cin >> input;
        if(input == 1)
        {
            auto start = chrono::steady_clock::now(); //time starts 
            auxMergeSort(array, 0, arraySize - 1); 
            auto end = chrono::steady_clock::now(); //time ends
            double totalTime = double(chrono::duration_cast <chrono::nanoseconds>(end - start).count());
            cout << "\nTime taken in milliseconds was: " <<  totalTime/1000000 << endl;
            break;
            

        }
        else if(input == 2)
        {
            auto start = chrono::steady_clock::now();
            auxQuickSort(array, 0, arraySize - 1); 
            auto end = chrono::steady_clock::now();
            double totalTime = double(chrono::duration_cast <chrono::nanoseconds>(end - start).count());
            cout << "\nTime taken in milliseconds was: " <<  totalTime/1000000 << endl;
            break;
        }
        else
        {
            cout << "\nInvalid input try again\n";
        }
    }
    while(input != 2 || input !=1);

    cout << "\nThe array after sorting algorithm is\n\n";
    cout << "\nAfter applying sort: \n\n";
    flgIsSorted(array);
    print(array, arraySize); 

    return 0; 
} 
void merge(int * array, int left, int middle, int right) //function that merges array together
{ 
    int i, j, k; 
    int first = middle - left + 1; 
    int second =  right - middle; 

    int L[first], R[second]; //create temp arrays

    for (i = 0; i < first; i++)     
        L[i] = array[left + i];     //puts data into arrays
    for (j = 0; j < second; j++) 
        R[j] = array[middle + 1+ j]; 

    //Reset index values
    i = 0;  
    j = 0;  
    k = left; 
    while (i < first && j < second) 
    { 
        if (L[i] <= R[j]) //check if value in Left is less or same and right
        { 
            array[k] = L[i]; 
            i++; 
        } 
        else
        { 
            array[k] = R[j]; 
            j++; 
        } 
        k++; 
    } 
    while (i < first) 
    { 
        array[k] = L[i]; 
        i++; 
        k++; 
    } 
    while (j < second) 
    { 
        array[k] = R[j]; 
        j++; 
        k++; 
    } 
} 
void auxMergeSort(int * array, int startIndex, int endIndex) 
{ 
    if (startIndex < endIndex) 
    { 
        int middle = startIndex +(endIndex-startIndex)/2; 

        auxMergeSort(array, startIndex, middle); //sort two arrays 
        auxMergeSort(array, middle+1, endIndex); 

        merge(array, startIndex, middle, endIndex); //call merge function to attach arrays back
    } 
} 
void print(int * array, int size) 
{ 
    int i; 
    for (i=0; i < 100; i++) 
        cout << array[i] << " "; 
    cout << endl << endl; 
}
bool sortHelper(int * array, int index) //Does the work for checking
{
    if(sizeof(array) - index < 2)
    {
        return true;
    }
    else if(array[index] > array [index + 1]) //checks if value is greater than successor
    {
        return false;
    }
    return sortHelper(array, index + 1);
}
bool flgIsSorted(int * array)
{
    if(check(array) == true) //User utility function 
    {
        cout << "Array is sorted (checked with flgIsSorted)\n";
        return true;
    }
    else
    {
        cout << "Array is not sorted (checked with flgIsSorted)\n";
        return false;
    }
}
bool check(int * array)
{
    if(sortHelper(array, 0) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}
void exchange(int * first, int * second)
{
    int a = *first; //temp variable to hold one of the elements
    *first = *second;
    *second = a;
}
void auxQuickSort(int * array, int startIndex, int endIndex)
{
    if(startIndex < endIndex) 
    {
        int q = partition(array, startIndex, endIndex); //q catches return value of partition
        auxQuickSort(array, startIndex, q-1); //recursive calls on the first and second half
        auxQuickSort(array, q+1, endIndex);
    }
}
int partition(int * array, int startIndex, int endIndex)
{
    int m = (startIndex + endIndex)/2;
    exchange(&array[m], &array[endIndex]);
    int x = array[endIndex];
    int i = startIndex - 1;
    for (int j = startIndex; j <= endIndex - 1; j++)
    {
        if(array[j] <= x)
        {
            i++;
            exchange(&array[i], &array[j]);
        }
    }
    exchange(&array[i + 1], &array[endIndex]);
    return (i + 1);
}

