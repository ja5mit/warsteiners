/* NAME - Jasmit Singh
   LAB 4 - DFA and Bellman Ford
   PROFESSOR - Dr. Flesch */

#include <iostream>
#include <string.h>
#include <iomanip>
#include <vector>

#define RED "\x1B[41m"
#define BLUE "\x1B[45m"
#define RESET "\x1B[0m"

using namespace std;

void dfa(string input); //Code for DFA given in lab 4
void display(int dist[], int size, int pred[]); //displays shortest path to each vertex 
void bellman_ford(struct Graph* graph, int source); //finds shortest path to each vertex used geeksforgeeks for refrence  
 
struct Edge //this struct has all featues of edge 
{ 
    int source, dest, weight; 
}; 
  
struct Graph //this struct is going to contain features of graph 
{ 
    int V, E; //V is number of veticies and E is number of egdes
  
    
    struct Edge* edge; //an array of edges
}; 
  
struct Graph* make_graph(int V, int E) //creates graph based on V and E values
{ 
    struct Graph* graph = new Graph; 
    graph->V = V; 
    graph->E = E; 
    graph->edge = new Edge[E]; 
    return graph; 
}

int main()
{
    string first = "ababa"; //these are all the strings given in lab 4
    string second = "baba";
    string third = "aababaab";
    string fourth = "babaabaaabb";
    string fifth = "";

    cout << BLUE << "\nDFA RESULTS:\n\n" << RESET;
    dfa(first);  //calling the DFA for each string 
    dfa(second);
    dfa(third);
    dfa(fourth);
    dfa(fifth);
    
    int verts = 14;  //number of verticies and edges in graph 
    int edges = 21;  
    Graph * graph = make_graph(verts, edges); //Create the graph of given size

    //0 represents A, 1 represents B and so on. Will convert back to letters in display function
  
    //edge from A to D
    graph->edge[0].source = 0; 
    graph->edge[0].dest = 3; 
    graph->edge[0].weight = 3; 
    
    //edge from B to A
    graph->edge[1].source = 1; 
    graph->edge[1].dest = 0; 
    graph->edge[1].weight = -2; 
  
    //edge from C to B
    graph->edge[2].source = 2; 
    graph->edge[2].dest = 1; 
    graph->edge[2].weight = 1; 
  
    //edge from C to N
    graph->edge[3].source = 2; 
    graph->edge[3].dest = 13; 
    graph->edge[3].weight = -3; 
  
    //edge from C to M
    graph->edge[4].source = 2; 
    graph->edge[4].dest = 12; 
    graph->edge[4].weight = 3; 
  
    //edge from D to E
    graph->edge[5].source = 3; 
    graph->edge[5].dest = 4; 
    graph->edge[5].weight = 2; 
  
    //edge from D to F
    graph->edge[6].source = 3; 
    graph->edge[6].dest = 5; 
    graph->edge[6].weight = 6; 
  
    //edge from D to G
    graph->edge[7].source = 3; 
    graph->edge[7].dest = 6; 
    graph->edge[7].weight = -1; 

    //edge from D to N
    graph->edge[8].source = 3; 
    graph->edge[8].dest = 13; 
    graph->edge[8].weight = -1;
    
    //edge from E to F
    graph->edge[9].source = 4; 
    graph->edge[9].dest = 5; 
    graph->edge[9].weight = 3;

    //edge from F to H
    graph->edge[10].source = 5; 
    graph->edge[10].dest = 7; 
    graph->edge[10].weight = -2;

    //edge from G to H
    graph->edge[11].source = 6; 
    graph->edge[11].dest = 7; 
    graph->edge[11].weight = 1; 

    //edge from G to J
    graph->edge[12].source = 6; 
    graph->edge[12].dest = 9; 
    graph->edge[12].weight = 3; 

    //edge from H to K
    graph->edge[13].source = 7; 
    graph->edge[13].dest = 10; 
    graph->edge[13].weight = -1; 

    //edge from I to H
    graph->edge[14].source = 8; 
    graph->edge[14].dest = 7; 
    graph->edge[14].weight = -4; 

    //edge from J to I
    graph->edge[15].source = 9; 
    graph->edge[15].dest = 8; 
    graph->edge[15].weight = 2; 

    //edge from J to K
    graph->edge[16].source = 9; 
    graph->edge[16].dest = 10; 
    graph->edge[16].weight = 3; 

    //edge from L to K
    graph->edge[17].source = 11; 
    graph->edge[17].dest = 10; 
    graph->edge[17].weight = 2; 

    //edge from M to L
    graph->edge[18].source = 12; 
    graph->edge[18].dest = 11; 
    graph->edge[18].weight = -4; 

    //edge from N to M
    graph->edge[19].source = 13; 
    graph->edge[19].dest = 12; 
    graph->edge[19].weight = 8; 

    //edge from N to C
    graph->edge[20].source = 13; 
    graph->edge[20].dest = 9; 
    graph->edge[20].weight = 5; 
    
    
    cout << RED << "\n\nBELLMAN FORD ALGORITHM:\n" << RESET << endl;
    bellman_ford(graph, 0);

    return 0;
}
void dfa(string input)
{
    /*Q = {S,q1,q2,r1,r2}
      S is the start state
      Acceptance states are {q1,r1}
      alphabet is {a,b}

             a   b  
      S      q1  r1
      q1     q1  q2    this is the table of states
      q2     q1  q2      
      r1     r2  r1
      r2     r2  r1

      S  = 0   a = 0                
      q1 = 1   b = 1           
      q2 = 2          indicies that represent each state & alphabet char. States are rows of 2d array and alphabet letter are columns
      r1 = 3              
      r2 = 4*/              

    int table[5][2];                    

    table[0][0] = 1;    //inputting values into the 2d array based on state table above
    table[0][1] = 3;
    table[1][0] = 1;
    table[1][1] = 2;
    table[2][0] = 1;
    table[2][1] = 2;
    table[3][0] = 4;
    table[3][1] = 3;
    table[4][0] = 4;
    table[4][1] = 3;

    int current = 0; //this is which state we are currently at. It starts at 0 since 0 represents S and S is the start state
    
    if(input.size() == 0) //if string is empty
    {
        cout << "\nYour string is " << BLUE << "empty" << RESET<< "\n\n";
        return;
    }
    for(int i = 0; i < input.size(); i++) //iterating through the string one char at a time
    {

        if(input[i] == 'a') //if next char is an 'a' go to index 0
        {
            current = table[current][0];
        }
        else if(input[i] == 'b') //if next character is a 'b' go to index 1
        {
            current = table[current][1];
        }
        else //else it means the character isn't part of the given alphabet {a,b}
        {
            cout << "\n'" << BLUE << input << RESET << "' contains letters that are not part of this alphabet\n\n";
        }
    }
    if(current == 1 || current == 3) //after going through the string this checks if the last char is at an accept state {q1,r1}
    {
        cout << "\n" << BLUE << "'" << input << "'" << RESET << " is " << BLUE << "accepted" << RESET << "\n\n" ;
    }
    else
    {
        cout << "\n" << BLUE << "'" << input << "'" << RESET << " is " << BLUE << "NOT" << RESET << " " << "accepted" << "\n\n" ;
    }
}
void display(int dist[], int size, int pred[]) //displays shortest path to each vertex 
{ 
    char alpha[14] = {'a','b','c','d','e','f','g','h','i','j','k','l','m','n'};
    cout << endl;
    for (int i = 0; i < size; ++i) 
    {
        if(i == 0) //this means distance to itself special case becasue predecessor needs to be NULL
        {
            
            cout << "The distance from " << RED << " a " << RESET << " to " << RED << " " << alpha[i] << " " <<  RESET << " is " << RED << " " << dist[i] <<" " << RESET << " and the predecessor is " << RED << " " << "null" << " " << RESET <<"\n\n";
        }
        else if(dist[i] == INT32_MAX)
        {
            cout << "The distance from " << RED << " a " << RESET << " to " << RED << " " << alpha[i] << " " << RESET << " is " << RED << "INFINITY" << RESET " so no predecessor" <<"\n\n";
        }
        else
        {
           cout << "The distance from " << RED << " a " << RESET << " to " << RED  << " " << alpha[i] << " " << RESET << " is " << RED << " " << dist[i] << " " << RESET << " and the predecessor is " << RED << " " << alpha[pred[i]] << " " << RESET << "\n\n";
        }
    }
}
void bellman_ford(struct Graph* graph, int source) 
{ 
    int V = graph->V; 
    int E = graph->E; 
    int dist[V]; 
    int pred[V];
    for(int i = 0; i < V; i++)//set all values of pred to infinity
    {
        pred[i] = 0;
    }
    for (int i = 0; i < V; i++) //set all values to max_int or infinity to begin 
    {   
        dist[i]   = INT32_MAX; 
    }
    dist[source] = 0; 
    for (int i = 1; i <= V-1; i++) //this is where all the edges are relaxed
    { 
        for (int j = 0; j < E; j++) 
        { 
            int u = graph->edge[j].source; 
            int v = graph->edge[j].dest; 
            int weight = graph->edge[j].weight; 
            if (dist[u] != INT32_MAX && dist[u] + weight < dist[v]) 
            {
                dist[v] = dist[u] + weight;
                pred[v] = u;
            }
        } 
    } 
    for (int i = 0; i < E; i++) //this makes sure we don't have a negative weight cycle 
    { 
        int u = graph->edge[i].source; 
        int v = graph->edge[i].dest; 
        int weight = graph->edge[i].weight; 
        if (dist[u] != INT32_MAX && dist[u] + weight < dist[v]) 
            cout << "This graph has a negative weight cycle"; 
    } 
  
    display(dist, V, pred); 
  
    return; 
} 
 
