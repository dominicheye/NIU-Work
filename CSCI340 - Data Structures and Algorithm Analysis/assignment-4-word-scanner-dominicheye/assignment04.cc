#include <iostream>
#include <iomanip>
#include <map>
#include <fstream>
#include <algorithm>
using namespace std;

#define NO_ITEMS 3
#define ITEM_W 16

void get_words(map<string, int>&);
void print_words(const map<string, int>&);
void clean_entry(const string&, string&);

int main()
{

map<string, int> wordCount;
get_words(wordCount);
print_words(wordCount);
return 0;
}

/*************************************
 get_words

 Purpose: uses if stream to move words into map,
          calls clean_entry before adding words to map

Arguments: map container <string, int>
Returns: nothing
*************************************/

void get_words(map<string, int>& wordCount)
    {
    
    //declare string objects to hold 
    string origin, cleaned;
    //while loop to cycle through each word in cin
    //until each has been cleaned and put into wordCount
    while(cin >> origin)
        {
        clean_entry(origin, cleaned);
        if(cleaned.length() != 0)
            wordCount[cleaned]++;
        }
    }

/*************************************
 clean_entry

 Purpose: takes string given, and looks for punctuation, 
        if punctuation is found, deletes everything after

Arguments: 2 strings (original and one to store in)
Returns: nothing
*************************************/

void clean_entry(const string& origin, string& cleaned)
    {
    //empty the string
    cleaned.clear();
    //declare necessary variables
    bool alnum = true;
    int j = 0;
    char c;
    
    //for loop cycles through original string and puts all
    //letters and numbers in cleaned string until first 
    //punct. mark, or until word is over. 
    for(size_t i = 0; i < origin.size() && alnum; i++)
        {
        c = origin[i];

        if(isalnum(c))
            {
            c = tolower(c);
            cleaned.push_back(c);
            j++;
            }
        //special case of first letter being a punct. mark with letters
        //after it covered by i != 0
        if(isalnum(c) == 0 && i != 0 )
            {
            alnum = false; 
            }  
        }
    }

/*************************************
 print_words

 Purpose: prints the map of words, by the string 
         and the amount of times it appears.

Arguments: map container
Returns: nothing
*************************************/

void print_words(const map<string, int>& wordCount)
    {
    //declare necessary variables
    map<string, int>::const_iterator it;
    it = wordCount.begin();
    int count = 1;
    int outNum = 0, inNum = 0;

    //while loop that cycles through each wordcount part, outputs it, and 
    //increases counters on input and output amount of words. every NO_ITEMS words new
    //line
    while(it != wordCount.end())
        {
        cout << setw(ITEM_W) << left << it->first << " : " << setw(2) << it->second << "\t";
        inNum = inNum + it->second;
        it++;
        if(count == NO_ITEMS)
            {
            cout << endl;
            count = 0;
            }
        count++;
        outNum++;
        }
    
    cout << endl << "no of words in input stream  : " << inNum << endl;
    cout << "no of words in output stream : " << outNum << endl;
    }