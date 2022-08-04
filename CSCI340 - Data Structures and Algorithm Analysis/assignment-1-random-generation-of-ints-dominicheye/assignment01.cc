#include "assignment01.h"

// Add needed constants
#define SEED 1
#define VEC_SIZE 200
#define NO_ITEMS 12
#define ITEM_W 5
// Add code for genRndNums
void genRndNums(vector<int> &v);
// Add code for printVec
void printVec(const vector<int> &v);
int 
main() 
{
// Declare vector v
vector<int> v;
// Generate random numbers to fill vector v	
genRndNums(v);
// Using STL sort sort v
std::sort(v.begin(), v.end() );	
// Print vector of sorted random numbers
printVec(v);
cout << std::endl; //adds extra line to match results01.out
    return 1;
}


