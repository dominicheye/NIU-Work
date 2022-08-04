#include "matrix.h"



/************************************************
open_files

purpose: opens two files into two ifstream files, checks to make sure it opened
arguments: two ifstream variables
returns: nothing
************************************************/
void open_files(ifstream& is1, ifstream& is2)
    {

    is1.open(FILE1);

    //check to see if file opened and if not closes the program
    if(!is1)
        {
        cerr << "ERROR: file 1 did not open, closing program now." << endl;
        exit(0);
        }


    is2.open(FILE2);

    //check to see if file opened and if not closes the program
    if(is2.fail())
        {
        cerr << "ERROR: file 2 did not open, closing program now." << endl;
        exit(0);
        }

    }

/************************************************
read_data

purpose: to read the data from a ifstream into a matrix vector
arguments: a ifstream variable and a matrix vector 
returns: nothing
************************************************/
void read_data(ifstream &is, vector<vector<int>> &m)
    {
    //loops through the rows and columns to fill each spot with a number 
    //from the .dat file
    for(size_t i = 0; i < m.size(); i++)
        {
        for(size_t j = 0; j < m[i].size() ; j++)
            {
            is >> m[i][j];
            }
            
        }
    //since we are done with the file, close it
    is.close();
    }


/**************************************************
print_data

purpose: Goes through entire 2d vector and prints
            based off of rows and columns with
            specific width
arguments: 2d vector object
returns: nothing
**************************************************/
void print_data(const vector<vector<int>> &m)
    {

    //formatting the top
    cout << m.size() << " x " << m[1].size(); //puts # of rows and cols. (uses m[1] because it can use any number there)
    cout << endl << "----------------------------------------------------------------------";

    //cycles through each row and column to print the number with width ITEM_W
    //creates a new line after row is finished when j is completed
    for(size_t i = 0; i < m.size(); i++)
        {
        cout << endl;
        for(size_t j = 0; j < m[i].size() ; j++)
            {
            cout << setw(ITEM_W) << m[i][j];
            }   
        }
    cout << endl;
    }

/***********************************************
gen_data

purpose: multiplies two vector matrices using matrix
         multiplication and stores it in a third matrix vector
arugments: 3 vector matrices
returns: nothing
***********************************************/
void gen_data(const vector<vector<int>> &A, const vector<vector<int>> &B, vector<vector<int>> &C)
    {
    
    //cycles through each row and column of C with the first two for loops
    //the third loop allows A and B to be multiplied by cycling through A's 
    //column and b's rows. 
    for(size_t i = 0; i < C.size(); i++)
        {

        for(size_t j = 0; j < C[i].size() ; j++)
            {

            //looks to B.size because the columns of A always equals the rows of B
            for(size_t k = 0; k < B.size(); k++) 
                {
                //multiplies two parts of A matrix and B matrix, and adds it to the total in C matrix
                C[i][j] += A[i][k] * B[k][j]; 
                }
            }   
        }
    }