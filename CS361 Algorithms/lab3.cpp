/* NAME - Jasmit Singh
   LAB 3 - Breadth first search and Matrix chain Multiplication
   PROFESSOR - Dr. Flesch */
#include <iostream>
#include <queue>
#include <fstream>
#include <list>
#include <iomanip>
#include <vector>
#define BLUE "\x1B[37m"
#define RESET "\x1B[0m"
using namespace std;

bool check(bool array[], int size); //checks if all verticies have been visited 
void print_visited(bool array[], int size); //prints visited array to make sure we've visited all verticies. Only used to test code
void end_of_row(int size, int col, int &t, queue <int> &track); //checks if we've visited all the current vertexes neighbors. If we have we will pop it off the queue.
void bfs_matrix(int matrix[15][15], int size); //breadth first search using an adjaceny matrix. Written from scracth
void bfs_list(vector<vector<int> >list, int size); //breadth first search using adjacency list. Written from scratch
int matrix_chain_dp(int *p, int size); //this is the dynamic programming version of MCM. Got help from geeksforgeeks and psuedo code from book
int look_up_chain(int **m, int *p, int i, int j); //recursive function used for memoized MCM
int memoized_matrix(int *p, int size); //memoized version of MCM using psuedo code from book

int main()
{
    int matrix[15][15] = { //adjacency matrix using 2d array

        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,1,0,0,0,0,0,0,0,0,0,0},
        {0,1,0,1,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,1,0,0,0,0,0,0,0,0,0,0,1,1},
        {0,1,0,0,0,1,1,1,0,0,0,0,0,0,1},
        {0,0,0,0,1,0,1,0,0,0,0,0,0,0,0},
        {0,0,0,0,1,1,0,0,1,0,0,0,0,0,0},
        {0,0,0,0,1,0,0,0,1,0,1,0,0,0,0},
        {0,0,0,0,0,0,1,1,0,1,0,1,0,0,0},
        {0,0,0,0,0,0,0,0,1,0,1,0,0,0,0},
        {0,0,0,0,0,0,0,1,0,1,0,1,0,0,1},
        {0,0,0,0,0,0,0,0,1,0,1,0,1,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,1,0,1,0},
        {0,0,0,1,0,0,0,0,0,0,0,0,1,0,1},
        {0,0,0,1,1,0,0,0,0,0,1,0,0,1,0}};

    vector<vector<int> >list(15); //adjacency list using vector of vectors
    list[1] = {2,4};
    list[2] = {1,3};
    list[3] = {2,13,14};
    list[4] = {1,5,6,7,14};
    list[5] = {4,6};
    list[6] = {4,5,8};
    list[7] = {4,8,10};
    list[8] = {6,7,9,11};
    list[9] = {8,10};
    list[10] = {7,9,11,14};
    list[11] = {8,10,12};
    list[12] = {11,13};
    list[13] = {3,12,14};
    list[14] = {3,4,10,13};
    
    int p[7] = {30, 4, 8, 5, 10, 25, 15}; //array of values p0 to p6
    int size = 7; 
    
    cout << "MCM value with memoized version: " << memoized_matrix(p, size) << endl; //running memoized version of MCM
    cout << "MCM value with dynamic programming version: " << matrix_chain_dp(p, size) << endl; //running DP version of MCM
    
    bfs_matrix(matrix, 15); //running bfs using an adjacency matrix
    bfs_list(list, 15); //running bfs using adjacency lisy
    
    return 0;                               
}       
bool check(bool array[], int size) //checks if we visited all verticies
{
    for (int i = 0; i < size; i++)
    {
        if(array[i] == false)
            return false;
    }
    return true;
}
void print_visited(bool array[], int size) //used to check if all verticies were visited
{
    cout << "\t visited ";
    for (int i = 0; i < size; i++)
        cout << " " << array[i] << " ";
    cout << "\n";
}
void end_of_row(int size, int col, int &t, queue <int> &track)//checks if we have visited all of the neighbors and dequeues it 
{
    if(col == (size-1))
    {
        track.pop();
        t = track.front();
    }
}
void bfs_matrix(int matrix[15][15], int size)
{
  char alpha[14] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N'}; //used to print correct letters
    cout << "\nOriginal\n\n" << "   "; //printing original matrix
    cout << " "; 
    for (int q = 1; q < size; q++)
    {
        cout << BLUE << alpha[q-1] << RESET << "  "; 
    }
    cout << endl << endl;
    for (int row = 1; row < size; row++) //displays initial matrix of original graph
    {   
        cout << BLUE << alpha[row-1] << RESET;
        cout << " ";
        for(int column = 1; column < size; column++)
            cout << right << setw(2) << "  " << matrix[row][column];
        cout << endl;
    }

    bool visited[size]; //keeps track of verticies visited
    queue<int> track; //check whats next on breadth first
    
    for (int i = 0; i < size; i++) //set everything in visited to false
        visited[i] = false;

    int tree[size][size]; //matrix used for the MST
    for (int r = 0; r < size; r++)
    {
        for(int c = 0; c < size; c++)
            tree[r][c] = 0;
    }
    visited[0] = true; //0 is true by default since it is not used
    int t = 1; //start at vertex 1(a)
    track.push(t); //push current vertex onto queue
    while(check(visited, size) != true) //while each vertex has not been visited
    {
        for (int col = 0; col < size; col++)
        {
            if(matrix[t][col] == 1 && visited[col] == false) //if there is a connection to the current vertex and we haven't visited the current vertex
            {
                tree[t][col] = 1;
                tree[col][t] = 1;
                visited[col] = true;
                track.push(col); //adds new vertex on queue
                end_of_row(size, col, t, track); //checks if we have finished visiting the current rows neighbors. 
            }
            else if(matrix[t][col] != 1 || visited[col] == true) //if there is no connection to the vertex or we've visited it
                    end_of_row(size, col, t, track);
        }
    }
    cout << "\nResult\n\n" << "   "; //printing final matrix
    cout << " "; 
    for (int q = 1; q < size; q++)
    {
        cout << BLUE << alpha[q-1] << RESET << "  "; 
    }
    cout << endl << endl;
    for (int row = 1; row < size; row++) //displays initial matrix of original graph
    {   
        cout << BLUE << alpha[row-1] << RESET;
        cout << " ";
        for(int column = 1; column < size; column++)
            cout << right << setw(2) << "  " << tree[row][column];
        cout << endl;
    }
   
}
void bfs_list(vector<vector<int> >list, int size)
{
    
    char alpha[14] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N'};//used to print correct letters
    cout << "\nOriginal\n" << endl; //printing original graph
    for(int i = 1; i < size; i++)
    {
        cout << BLUE << alpha[i-1] << " -" << RESET;
        for(int j = 0; j < list[i].size(); j++)
        {   
            cout << " " << alpha[list[i][j]-1];
        }
        cout << endl;
    }

    bool visited[size]; //keeps track of verticies visited
    queue<int> track; //check whats next on breadth first

    for (int i = 0; i < size; i++)
    {
        visited[i] = false;
    }
    vector<vector<int> >tree(size); //create a vector of vectors to store tree
    visited[0] = true; //we dont use 0 so its true by default
    int t = 1; //start at vertex 1(a)
    track.push(t);
    while(check(visited, size) != true)//while every vertex has not been visited
    {
        for(int col = 0; col < list[t].size(); col++)
        {
            if((visited[list[t][col]]) != true)//checks if current vertex has been visited
            {
                tree[t].push_back(list[t][col]); //adding values to tree
                tree[list[t][col]].push_back(t);
                visited[list[t][col]] = true;
                track.push(list[t][col]);
            }
        }
        visited[t] = true; //done visiting vertex
        track.pop(); //remove from quene once we are done visiting
        t = track.front(); //pull next value from queue
    }
    cout << "\nResult\n" << endl; //printing BFS result
    for(int i = 1; i < size; i++)
    {
        cout << BLUE << alpha[i-1] << " -" << RESET;
        for(int j = 0; j < tree[i].size(); j++)
        {   
            cout << " " << alpha[tree[i][j]-1];
        }
        cout << endl;
    }
}
int matrix_chain_dp(int *p, int size)
{
    int m[size][size];             //Initializing matrix
    for (int i = 1; i < size; i++) 
    {
        m[i][i] = 0;
    }
    for (int l = 2; l < size; l++) //length of the chain
    {
        for (int i = 1; i < size - l + 1; i++)
        {
            int j = i + l - 1;
            m[i][j] = INT32_MAX;               //Setting values to infinity in c++ INT32_MAX is the integer limit in c++
            for (int k = i; k <= j - 1; k++) 
            {
                int multiplications = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j]; //determines number of multiplications
                if (multiplications < m[i][j])                                        //if new value is better(smaller) it will replace
                {
                    m[i][j] = multiplications;
                }
            }
        }
    }
    return m[1][size - 1]; //returns the result 
}

int look_up_chain(int **m, int *p, int i, int j) 
{
    if (m[i][j] != -1) //If the value is not -1 that mean the value is there already
    {
        return m[i][j];
    }
    if (i == j) //When i and j are the same the value is always zero
    {
        m[i][j] = 0;
    }
    else //this is where we will calculate 
    {
        for (int k = i; k < j; k++)
        {
            int q = look_up_chain(m, p, i, k) + look_up_chain(m, p, k + 1, j) + (p[i - 1] * p[k] * p[j]); //This calcuates number of multiplications
            if ((q < m[i][j]) || (m[i][j] == -1))                                                     
            {
                m[i][j] = q;
            }
        }
    }
    return m[i][j]; //Returns the result
}

int memoized_matrix(int *p, int size)
{
    int **m = new int *[size]; //Initializing new matrix
    for (int i = 0; i < size; ++i)
    {
        m[i] = new int[size];
    }
    for (int i = 1; i < size; i++) //Setting all values to -1
    {
        for (int j = i; j < size; j++)
        {
            m[i][j] = -1;
        }
    }
    return look_up_chain(m, p, 1, size - 1); //recursive call
}
