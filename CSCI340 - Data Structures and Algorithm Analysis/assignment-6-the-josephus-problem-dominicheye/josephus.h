#ifndef H_JOSEPHUS
#define H_JOSEPHUS

#include <iostream>
#include <sstream>
#include <string>
#include <list>
#include <algorithm>

using namespace std;

#define NO_LETS  26    // no of letters in English alphabet
#define NO_ITEMS 12    // no of items printed on single line

// struct for input arguments

struct args {
    unsigned N,       // no of initial people   
             M,       // count to eliminate person
             K;       // frequency of printouts
};

// class to generate name tags for people

class SEQ {
private:
    string id;         // name tag for person
    unsigned size, nd; // no of people, no of digits in name tags

    // returns no of digits in name tags
    unsigned find_nd ( const double& sz ) {
        if ( ( sz / NO_LETS ) <= 1 ) return 2;
        else return ( find_nd ( sz / NO_LETS ) + 1 );
    }

public:
    // constructor for name-tag generator
    SEQ ( const unsigned& s = 1 ) : size ( s ) {
        double sz = ( double ) size / 9; nd = find_nd ( sz );
        id = string ( nd, 'A' ); id [ nd - 1 ] = '1'; 
    }

    // returns next name tag in sequence
    string operator ( ) ( ) {
        string tmp = id; int i = nd - 1;
        if ( id [ i ] < '9' ) id [ i ]++;
        else {
            id [ i ] = '1'; bool flag = true;
            for ( i--; i >= 0 && flag; i-- )
                if ( id [ i ] < 'Z' ) { id [ i ]++; flag = false; }
                else id [ i ] = 'A';
        } 
        return tmp;
    }
};





// reads and initializes all input arguments
void init_vals(list<string> &, args &);

void init_vals(list<string> &L, args &in)
{
cin >> in.N >> in.M >> in.K; //read in numbers 

//print out the numbers
cout << "Number of people? " << in.N << endl    
     << "Index for elimination? " << in.M << endl
     << "Index for printing? " << in.K << endl << endl;
//make list big enough for all the numbers
L.resize(in.N);
//use generate function along with given class to fill list
generate(L.begin(), L.end(), SEQ(in.N));
}






// prints all name tags for remaining people after elimination
void print_list ( const list < string >&, const unsigned& );

void print_list(const list<string> &L, const unsigned &cnt)
{
//output title of group 
if(cnt == 0)
    cout << "Initial group of people" << endl << "-----------------------" << endl;
//creates string so that "----" is same length as title. cnt is used to find how many people were eliminated so far.
else
    {
    string output("After eliminating ");
    output += to_string(cnt);
    output += "th person";
    cout << output << endl << string(output.length(), '-') << endl;
    }

int oCount = 0; //for counting the amount on a line
//loop to output each element with a space, until 12th element, then starts new line
for(list<string>::const_iterator it = L.begin(); it != L.end(); it++)
    {
    cout << *it << " ";
    oCount++;
    if(oCount%12 == 0)
        cout << endl;
    }


cout << endl << endl;
}
#endif
