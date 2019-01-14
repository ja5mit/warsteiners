#include <iostream>
#include <queue>

using namespace std;

bool check(bool array[], int size);
void print_visited(bool array[]);
void end_of_row(int col, int &t, queue <int> &track);

int main()
{
    int matrix[5][5] = {
    {0,0,0,0,0},
    {0,0,1,0,1},
    {0,1,0,1,0},
    {0,0,1,0,1},
    {0,1,0,1,0}};

    for (int row = 0; row < 5; row++)
    {
        for(int column = 0; column < 5; column++)
            cout << matrix[row][column] << " ";
        cout << endl;
    }
    bool visited[5]; //keeps track of verticies visited
    queue<int> track; //check whats next on breadth first
    
    for (int i = 0; i < 5; i++)
        visited[i] = false;

    int tree[5][5];
    for (int r = 0; r < 5; r++)
    {
        for(int c = 0; c < 5; c++)
            tree[r][c] = 0;
    }

    visited[0] = true;
    int t = 1;
    track.push(t);

    while(check(visited, 5) != true) //while each vertex has not been visited
    {
        for (int col = 0; col < 5; col++)
        {
            if(matrix[t][col] == 1 && visited[col] == false)
            {
                tree[t][col] = 1;
                tree[col][t] = 1;
                visited[col] = true;
                track.push(col);
                end_of_row(col, t, track);
            }
            else if(matrix[t][col] != 1 || visited[col] == true) 
                    end_of_row(col, t, track);
        }
    }
    cout << "\n\tResult\n\n";
    for (int ro = 0; ro < 5; ro++)
    {
        for(int co = 0; co < 5; co++)
            cout << tree[ro][co] << " ";
        cout << endl;
    }
}
bool check(bool array[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if(array[i] == false)
            return false;
    }
    return true;
}

void print_visited(bool array[])
{
    cout << "\t visited ";
    for (int i = 0; i < 5; i++)
        cout << " " << array[i] << " ";
    cout << "\n";
}

void end_of_row(int col, int &t, queue <int> &track)
{
    if(col == 4)
    {
        track.pop();
        t = track.front();
    }
}
