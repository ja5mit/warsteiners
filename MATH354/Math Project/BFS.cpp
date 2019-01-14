/* NAME - Jasmit Singh
FINAL PROJECT - Breadth first search to find a spanning tree 
PROFESSOR - Mathew Nabity */
#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

bool check(bool array[], int size); //checks if all verticies have been visited 
void print_visited(bool array[], int size); //prints visited array to make sure we've visited all verticies
void end_of_row(int size, int col, int &t, queue <int> &track); //checks if we've visited all the current vertexes neighbors. If we have we will pop it off the queue.

int main()
{
    int inp = 0;
    ifstream infile("input.txt");
    infile >> inp; //number of verticies
    cout << "\nWelcome, let me help you find a spanning tree for your graph\n";
    cout << "Your graph has " << inp << " verticies\n\n";
    int size = (inp+1); //size is one more than number of verticies so we can use index 1 for vertex 1 and so on
    int matrix[size][size];

    for (int i = 0; i < size; i++) //initialize matrix
    {
        for (int j = 0; j < size; j++)
        {
            matrix[i][j] = 0;
        }

    }
    for (int y = 1; y < size; y++) //inputs all values into adjacency matrix 
    {
        for (int z = 1; z < size; z++)
        {
            infile >> matrix[y][z];
        }

    }
    cout << "\n\tOriginal\n\n" << "   ";
    for (int w = 1; w < size; w++)
    {
        cout << "V" << w << " "; 
    }
    cout << endl;
    for (int ro = 1; ro < size; ro++) //displays initial matrix of original graph
    {   
        cout << "V" << ro;

        for(int co = 1; co < size; co++)
            cout << "  " << matrix[ro][co];
        cout << endl;
    }
    bool visited[size]; //keeps track of verticies visited
    queue<int> track; //check whats next on breadth first
    
    for (int i = 0; i < size; i++)
        visited[i] = false;

    int tree[size][size];
    for (int r = 0; r < size; r++)
    {
        for(int c = 0; c < size; c++)
            tree[r][c] = 0;
    }
    visited[0] = true;
    int t = 1;
    track.push(t);
    while(check(visited, size) != true) //while each vertex has not been visited
    {
        for (int col = 0; col < size; col++)
        {
            if(matrix[t][col] == 1 && visited[col] == false) //if there is a connection to the current vertex and we haven't visited the current vertex
            {
                tree[t][col] = 1;
                tree[col][t] = 1;
                visited[col] = true;
                track.push(col);
                end_of_row(size, col, t, track); //this function checks if we have finished visiting the current rows neighbors. If we have we will dequeue it off 
            }
            else if(matrix[t][col] != 1 || visited[col] == true) //if there is no connection to the current vertex or if we've already visited the current vertex
                    end_of_row(size, col, t, track);
        }
    }
    cout << "\n\tResult\n\n" << "   ";
    for (int q = 1; q < size; q++)
    {
        cout << "V" << q << " "; 
    }
    cout << endl;
    for (int row = 1; row < size; row++) //displays initial matrix of original graph
    {   
        cout << "V" << row;

        for(int column = 1; column < size; column++)
            cout << "  " << tree[row][column];
        cout << endl;
    }
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
void end_of_row(int size, int col, int &t, queue <int> &track)//checks if we have visited all of the neighbors of the current vertex(row). If we have we will dequeue it
{
    if(col == (size-1))
    {
        track.pop();
        t = track.front();
    }
}
