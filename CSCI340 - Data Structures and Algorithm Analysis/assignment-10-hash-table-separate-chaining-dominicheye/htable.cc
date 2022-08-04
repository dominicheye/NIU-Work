#include "htable.h"

#define N1 10  // num of decimal digits
#define N2 26  // num of upper-case letters

// Hash function, you may NOT modify this function
int HT::hash(const string &s) {
  int n = (N2 * N1) * (s[0] - 'A') + N1 * (s[1] - 'A') + (s[2] - '0');

  return n % hsize;
}

// You will complete the code below ...
HT::HT(const unsigned &hs) 
  {
  hsize = hs; 
  hTable.resize(hsize);
  }

HT::~HT() 
  {
  //clears every pointer entry
  for(vector<Entry*>::iterator it = pTable.begin(); it != pTable.end(); it++)
    {
    delete *it;
    }
  //clears both vectors
  pTable.clear();
  hTable.clear();
  }

void HT::insert(const Entry &e) 
  {
  bool found = false;
  int i = 0;
  list<Entry> &l = hTable[i];
  Entry test;

  while(l != hTable[hsize-1] && found == false)
    {
    test = l.front(); //do not have to rotate through list bc not adding dup. keys
    if(test.key == e.key)
      found == true;
    
    i++;
    l = hTable[i];
    }

  l.front() = e;

  if(found == true)
    cout << " not inserted - duplicate key!!!" << endl;
  else 
    {
    hTable[hash(e.key)] = l;
    cout << "entry = " << setw(ID_SZ) << hash(e.key) << endl;
    }
  }

void HT::search(const string &s) 
  {
  bool found = false;
  int i = 0;
  list<Entry> &l = hTable[i];
  Entry test;

  while(l != hTable[hsize-1] && found == false)
    {
    test = l.front(); //do not have to rotate through list bc not adding dup. keys
    if(test.key == s)
      found == true;

    i++;
    l = hTable[i];
    }
  if(found == false)
    cout << " not in table!!" << endl;

  else
    {
    cout << " ==> number: " << setw(ID_SZ + 1) << test.num << " - item: " 
         << test.desc << endl;
    }
  
  }

void HT::hTable_print() 
  {
  int i = 0;
  list<Entry> &l = hTable[i];
  Entry test;

  while(l != hTable[hsize-1])
    {
    if(l.begin() != NULL)
      [
      
      ]
    test = l.front();
    
    cout << setw(4) << hash(test.key) << ": " << setw(4) << test.key 
         << "  - " << setw(5) << test.num << "  -  " << test.desc << endl;

    i++;
    l = hTable[i];
    }
  }

void HT::pTable_print() 
  {
  
  }