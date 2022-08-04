#ifndef DOG_H
#define DOG_H

#include <iostream>
#include <sys/types.h> //for open 
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>//for read
#include <string>

using namespace std;

struct Flags
    {
    bool bufOpt =0; //-s 
    char *bufSize; //buffer size, set to 256 by default but can be changed by -s
    bool readOpt =0; //-n
    char *readSize; //size for read, only needed if -n
    bool caesarOpt =0; // -c
    char *shift; //how many letters we shift by, only for -c and -r
    bool rotateOpt =0; //-r
    bool hexOpt =0; //display in hex -x
    bool binOpt =0; //display in binary -b
    };

void writeToBinary(int); //used to print the ascii code of a char in binary
void findFlags(Flags *, int, char* argv[]); //finds what -? are given
void readFile(Flags *, int, char* argv[], int, int); //reads and writes the file to standard output
void caesarSwitch(Flags *,char *, int); //checks to see if-c and then switches if necessary
void rotate(Flags *, char *, int);//checks to see if-r and then switches if necessary

#endif