// Dominic Heye
// Z1841746
// CSCI330
// Assignment 3

#include <iostream>
#include <sys/types.h> //for open 
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>//for read


using namespace std;

int main(int argc, char *argv[])
{
char *buffer;
//check to see if there are any files, else is error meaning no files given
if(argc > 1)
    {//for loop to go through every argument
    for(int j = 1; j < argc; ++j)
        { //if statement to check if cat -  was given
        if(argv[j][0] == '-' && argv[j][1] == 0)
            {
            cout << endl;
            ssize_t nr;
            //since cat - allows users to write several lines, 
            //this loop lets multiple lines be written and 
            //reproduced until cntl-c is hit
            while(!cin.eof())
                {
                nr =  read(0, buffer, 255);
                nr = write(1, buffer , nr);
                }
            }
        else
            {
            //if this isn't cat -
            int fd = open(argv[j], O_RDONLY);
            //check to see if file opened
            if(fd == -1) 
                {
                perror("open");
                return 2;
                }  
            
            //read the file, and start a while loop
            //that reads and prints out entire file with
            //small chunks at a time
            ssize_t nr;
            nr = read(fd, buffer, 255);
            while(nr != 0) 
                {
                if(nr == -1)
                    {
                    perror("read");
                    return 3;
                    }

                size_t nw;
                nw = write(1, buffer, nr);
                nr = read(fd, buffer, 255);
                }
            //close the file
            close(fd);
            cout << endl << endl;
            }
        }
    }
    
//if no arguments are given then print error
else 
    {
    cerr << "No files given" << endl;
    return 1;
    }


return 0;
}
