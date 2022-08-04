#ifndef SIMPLEGRAPH_H
#define SIMPLEGRAPH_H
#include <list>
#include <vector>
#include <fstream>
#include <iostream>

using namespace std;
class Graph {
 private:
  int                          size;
  vector<std::list<int> > adj_list;
  vector<char>            labels;
  void                         Depthfirst(int, bool[], list<char>&);

 public:
  Graph(const char* filename);
  ~Graph();
  int  Getsize() const;
  void Traverse();
  void Print() const;
};

//constructer, uses inputted file name to create new graph
Graph::Graph( const char* filename)
    {
    ifstream inFile;
    int readInt;
    char readChar;
    inFile.open(filename);

    //find number of v
    inFile >> size;
    labels.resize(size);
    adj_list.resize(size);
    //read labels and add to vector
    for(int i = 0; i < size; i++)
        {
        inFile >> readChar;
        labels[i] = readChar;
        }

    //read where edges are and add to list in vectro adj_list
    for (int i = 0; i < size; i++)
        {
        inFile >> readChar;
        for(int j = 0; j < size; j++)
            {
            inFile >> readInt;
            if(readInt == 1)
                adj_list[i].push_back(j);
            }
        }
    
    inFile.close();

    }


//destructor
Graph::~Graph() 
    {
    for(int i = 0; i < size; i++)
        adj_list[i].clear();
    
    adj_list.clear();
    labels.clear();
    }


//returns amount of vertices
int Graph::Getsize() const
    {
    return size;
    }

//goes through all the vertices by calling recursive funct. depth_first()
//also holds order of traversed points in list order, so that path can be followed.
void Graph::Traverse() 
    {
    cout << "traversal of the graph (depth-first)" << endl;
    list<char> order; //for following path
    bool *visited; //to see which points have been visited
    visited = new bool[size];
    for(int i = 0; i < size; i++)
        visited[i] = false;

    //go through each point, if they havent been visited, use recursive depth_first
    //to display all points that i is connected to
    for(int i = 0; i < size; i++)
        {
        if(!visited[i])
            {
            Depthfirst(i, visited, order);
            }
        }
    
    //output path list
    cout << endl;
    cout << "path taken" << endl;
    int i = 0;
    while(!order.empty())    
        {
        i++;
        cout << order.front() << "->";
        order.pop_front();
        cout << order.front() << "  ";
        if(i%4 == 0)
            cout << endl;
        }
    
    //empty out memory
    delete visited;
    order.clear();
    }


//recursive function that checks to see if each point on the adj_list for given n point
//has been visited, and if it hasn't, calls a new depth_first to go through that point
//uses order to see the path of traversed points
void Graph::Depthfirst(int n, bool visited[], list<char>& order)
    {
    if(order.back() != labels[n])
        order.push_back(labels[n]);
    
    visited[n] = true;
    cout << labels[n] << "  ";
    list<int>::iterator it;
    //for each vertex adjacent to v
    for (it = adj_list[n].begin(); it != adj_list[n].end(); ++it)
        {
        int w = *it;
        if (!visited[w])
            {
            order.push_back(labels[w]);
            Depthfirst(w, visited, order);
            order.push_back(labels[n]);
            
            }
        }
    if(order.back() != labels[n])
        order.push_back(labels[n]);
    }

//prints the adj. list for each point
void Graph::Print() const
    {
    cout << "connections on the graph" << endl;
    for(int i = 0; i < size; i++)
        {
        cout << labels[i] << ": ";  
        for (list<int>::const_iterator it = adj_list[i].begin(); it != adj_list[i].end(); ++it)
            {
            //used to convert the point from int to char
            int numToChar = *it;
            numToChar = numToChar + 65;
            cout << (char)numToChar << ", ";
            }
        cout << endl;
        }
    }

#endif // SIMPLEGRAPH_H
