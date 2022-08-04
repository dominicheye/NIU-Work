#ifndef H_ASSIGNMENT01 // should not be defined any place else 
#define H_ASSIGNMENT01 // same const value as for ifndef directive

// Add needed header files here ..
#include <vector>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <algorithm>

using std::vector;
using std::cout;

// You need to implement these two functions ...

/*********************************
void genRndNums(vector<int> &v);
function to generate random numbers using rand() function
and inputs them into a vector provided

arguments: a vector
returns: nothing
***********************************/
void genRndNums(vector<int> &v)
    {
    int SEED = 1;
    
    srand(SEED);
    for( int i = 0; i < 200; i++)
        {
        v.push_back((rand()%10000) + 1);
        }

    }

/*********************************
void printVec(const vector<int> &v);
function to print a vector out with the spacing of 5
using cout statements

arguments: a vector
returns: nothing
***********************************/
void printVec(const vector<int> &v)
    {
    //count is a variable to help with making sure after 12 numbers a new line is started
    int count = 1;
    //for loop to cycle through each element of the vector, 
    //uses the begin() and end() functions to know where to stop
    for(auto i = v.begin(); i != v.end(); i++)
        {
        //*i is the number being displayed, and the formatting is before it
        cout << std::setw(5) << std::right << *i << " "; 
        //if statement to check if it is the 12th number, if so, create new line
        if(count%12 == 0)
            {
            cout << std::endl;
            }
        count++;
        }
    }
#endif