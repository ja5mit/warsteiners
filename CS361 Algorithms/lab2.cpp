/*Jasmit Singh 
Lab 2 CS365 - Algorithms
Code only runs with c++ 11*/

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <chrono>

using namespace std;

const unsigned long int max_size = 10000000;

void count_sort(long int * A, long int size, long int p); //stable sort to use in radix
void print(long int * array, long int size); //prints contents of array. Starts at index 1
int get_largest(long int * array, long int size); //returns the largest item in array
void radix_sort(long int * A, long int size);
int read(long int * array, long int nums_to_read); //reads specified number of items from the file into the array 
void bucket_sort(long int * array, long int size);
bool sortHelper(long int * array, long int index); //recursive function to go through array
bool flgIsSorted(long int * array); //user function tells if check returns true or false
bool check(long int * array); //checks if sorted
void exchange(long int * first, long int * second); //switches two things in array
void quickSort(long int * array, long int startIndex, long int endIndex); //quicksort recrusive function
int partition(long int * array, long int startIndex, long int endIndex); //quicksort algorithm that partition array
void largest_ten(long int * array, long int size); // function that calls the recursive function
void largest_ten_helper(long int * array, long int size, long int index); //recursive function that displays largest 10

int main()
{
    long int * array = new long int[max_size]; //dynamic array that will hold values from file
    long int arraySize = read(array, 1000);
    
    
    int input = 0;
    cout << "\nBefore applying sort: \n\n";
    flgIsSorted(array);
    print(array, arraySize);
    
do
    {
        cout << "\nEnter 1 for radix sort or 2 for bucket sort" << endl << "Input: ";
        cin >> input;
        if(input == 1)
        {
            auto start = chrono::steady_clock::now(); //time starts 
            //largest_ten(array, arraySize);
            radix_sort(array, arraySize);
            auto end = chrono::steady_clock::now(); //time ends
            double totalTime = double(chrono::duration_cast <chrono::nanoseconds>(end - start).count());
            cout << "\nTime taken in milliseconds was: " <<  totalTime/1000000 << endl;
            //print(array, arraySize);
            break;
        }
        else if(input == 2)
        {
            auto start = chrono::steady_clock::now();
            //largest_ten(array, arraySize);
            bucket_sort(array, arraySize);
            auto end = chrono::steady_clock::now();
            double totalTime = double(chrono::duration_cast <chrono::nanoseconds>(end - start).count());
            cout << "\nTime taken in milliseconds was: " <<  totalTime/1000000 << endl;
            //print(array, arraySize);
            break;
        }
        else
        {
            cout << "\nInvalid input try again\n";
        }
    }
    while(input != 2 || input !=1);
    cout << "\nAfter applying sort:\n\n";
    flgIsSorted(array);
    print(array, arraySize); 
    cout << "\n";

    return 0;
}
void count_sort(long int * A, long int size, long int p)
{
    long int C[10]; //C array will hold K items 
    long int temp[size]; //temp array to hold sorted items
    for(long int i = 0; i < 10; i++) //intialize C array
    {
        C[i] = 0;
    }
    for(long int i = 0; i < size; i++) //intialize C array
    {
        temp[i] = 0;
    }

    for (long int i = 0; i < size; i++) //count occurences of each number
    {
        C[(A[i]/p)%10]++;
    }
    for(long int i = 1; i < 10; i++) //determine how many number are < or = current
    {
        C[i] = C[i] + C[i-1];
    }
    for (long int i = size-1; i >= 0; i--) //puts sorted values into array B
    {
        temp[C[(A[i]/p)%10]-1] = A[i];
        C[(A[i]/p)%10]--;
    }
    for (long int i = 0; i < size; i++)
    {
        A[i] = temp[i];
    }
}
void print(long int * array, long int size)
{
    for (long int i = (size-100); i < size; i++)
        cout << array[i] << " ";
    cout << endl;
}
int get_largest(long int * array, long int size)
{
    long int max = array[0];
    for (long int i = 0; i < size; i++)
    {
        if(array[i] > max)
        {
            max = array[i];
        }
    }
    return max;
}
void radix_sort(long int * A, long int size)
{
    long int maximum = get_largest(A, size);
    for(long int p = 1; maximum/p > 0; p *= 10)//call count_sort for each place value in array according to max
    {
        count_sort(A, size, p);
    }
}
int read(long int * array, long int nums_to_read)
{
    ifstream file; 
    file.open("lab2_data.txt");
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
        if(index == nums_to_read) //how many numbers to input
        {
            break;    
        }
    }
    return index; 
}
void bucket_sort(long int * array, long int size)
{
    long int max = get_largest(array, size);
    long int bucket = (max/10)+1;
    vector<vector<long int> >a(bucket); //vector of vectors for the buckets

    for(long int i = 0; i < size; i++) //places the number in the proper bucket
    {
        long int idx = floor(array[i]/10);
        a[idx].push_back(array[i]);
    }
    for(long int i = 0; i < bucket; i++) // sorts each bucket
    {
        sort(a[i].begin(), a[i].end());   
    }
    long int idx = 0;
    for(long int i = 0; i < bucket; i++) //puts number from sorted vector of vectors back to array 
    {
        for(long int j = 0; j < a[i].size(); j++)
        {
            array[idx] = a[i][j];
            idx++;
        }
    }

}
bool sortHelper(long int * array, long int index) //Does the work for checking
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
bool flgIsSorted(long int * array)
{
    if(check(array) == true) //User utility function 
    {
        cout << "Array is sorted (checked with flgIsSorted)\n\n";
        return true;
    }
    else
    {
        cout << "Array is not sorted (checked with flgIsSorted)\n\n";
        return false;
    }
}
bool check(long int * array)
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
void exchange(long int * first, long int * second)
{
    long int a = *first; //temp variable to hold one of the elements
    *first = *second;
    *second = a;
}
void quickSort(long int * array, long int startIndex, long int endIndex)
{
    if(startIndex < endIndex) 
    {
        long int q = partition(array, startIndex, endIndex); //q catches return value of partition
        quickSort(array, startIndex, q-1); //recursive calls on the first and second half
        quickSort(array, q+1, endIndex);
    }
}
int partition(long int * array, long int startIndex, long int endIndex)
{
    long int x = array[endIndex];
    long int i = startIndex - 1;
    for (long int j = startIndex; j <= endIndex - 1; j++)
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
void largest_ten(long int * array, long int size)
{
    long int * a = new long int[max_size];
    for(long int i = 0; i < size; i++)
    {
        a[i] = array[i];
    }
    quickSort(a, 0, size); //algorithm that sorts array
    cout << "\nLargest ten numbers" << endl;
    largest_ten_helper(a, size, size);
}
void largest_ten_helper(long int * array, long int size, long int index)
{
    if(index == (size-10)) //displays last 10 numbers 
    {
        return;
    }
    else
    {
        cout << array[index] << endl;
        //cout << "size: " << size << endl;
        index--;
        return largest_ten_helper(array, size, index);
    }
}
