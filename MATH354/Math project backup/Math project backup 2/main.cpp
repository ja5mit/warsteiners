#include <iostream>
#include <queue>
#include <fstream>

using namespace std;

bool check(bool array[], int size); //checks if all verticies have been visited 
void print_visited(bool array[], int size); //prints visited array to make sure we've visited all verticies
void end_of_row(int size, int col, int &t, queue <int> &track); //pops vertex off queue once we have visited all its neighbors

int main()
{
    int inp = 0;
    ifstream take("input.txt");
    take >> inp; //number of verticies
    cout << "Your graph has " << inp << " verticies\n\n";
    int size = (inp+1); //size is one more than number of verticies so we can use index 1 for vertex 1 and so on
    int matrix[size][size];

    for (int i = 0; i < size; i++)
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
            take >> matrix[y][z];
        }

    }
    for (int o = 1; o < size; o++) //displays initial matrix of original graph
    {
        for(int p = 1; p < size; p++)
            cout << matrix[o][p] << " ";
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
                end_of_row(size, col, t, track);
            }
            else if(matrix[t][col] != 1 || visited[col] == true) //if there is no connection to the current vertex or if we've already visited the current vertex
                    end_of_row(size, col, t, track);
        }
    }
    cout << "\n\tResult\n\n";
    for (int ro = 1; ro < size; ro++)
    {
        for(int co = 1; co < size; co++)
            cout << tree[ro][co] << " ";
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
void end_of_row(int size, int col, int &t, queue <int> &track)//used to pop vertex off queue once we are finished visiting all its neighbors
{
    if(col == (size-1))
    {
        track.pop();
        t = track.front();
    }
}
