// Dominic Heye
// Z1841746
// CSCI330
// Assignment 5

#include "dog.h"


int main(int argc, char* argv[])
{
//First declare needed variables
Flags flag1;

//Figure out what flags are given
findFlags(&flag1, argc, argv);

//Check to see if -r and -c or -b and -x (ERROR)
if(flag1.caesarOpt == 1 && flag1.rotateOpt == 1)
    {
    perror("Can't do -c and -r");
    return 1;
    }
    
if(flag1.hexOpt == 1 && flag1.binOpt == 1)
    {
    perror("Can't do -b and -x");
    return 1;
    }


//read the file, shift if needed, write in required format
if(flag1.bufOpt == 1) //if a buffer size is given
    readFile(&flag1, optind, argv, argc, atoi(flag1.bufSize));
else //otherwise use 255 as standard
    readFile(&flag1, optind, argv, argc, 255);


return 0;
}