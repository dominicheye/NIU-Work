// Dominic Heye
// Z1841746
// CSCI330
// Assignment 4

#include <iostream>
#include <iomanip>
#include <sys/types.h> //for open 
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>//for read
#include <cstring>
#include <unistd.h>


using namespace std;

int openFile(char *, bool, bool);

int main(int argc, char *argv[])
{
char *buffer;
bool trunc;
bool fileExists = 1;
char *fileName;
struct stat buf;
int rc = stat(fileName, &buf);
if(rc == -1)
    {
    fileExists = 0;
    }
else
    {
    cout << buf.st_mode << endl;
    }
//check to see if any arguments are given
if(argc > 1)
    {
    //check to see if there's -c
    //if so store 1 in binary bit
    if(argv[1][0] == '-' && argv[1][1] == 'c' && argv[1][2] == 0)
        {
        if(argc < 4)
            {
            cerr << "Not Enough Arguments" << endl;
            return 1;
            }
        trunc = 1;
        fileName = argv[2];
        buffer = argv[3];
        int rc = stat(fileName, &buf);
        if(rc == -1)
            {
            fileExists = 0;
            }
        else
            {
	    fileExists = 1;
            int mode = buf.st_mode & 511;
            if(mode != 0)
                {
                perror("Not Secure");
                return 4;
                }
            }
        }
    else   
        {
        if(argc < 3)
            {
            cerr << "Not Enough Arguments" << endl;
            return 3;
            }
        fileName = argv[1];
        buffer = argv[2];
        int rc = stat(fileName, &buf);
        if(rc == -1)
            {
            fileExists = 0;
            }
        else
            {
	    fileExists = 1;
            int mode = buf.st_mode & 511;
	    if(mode != 0)
                {
                cerr << "Not Secure" << endl;
                return 4;
                }
            }
        }
    int fd = openFile(fileName, trunc, fileExists);
    write(fd, buffer, strlen(buffer));
    write(fd, "\n", 1);
    int rv = chmod(fileName, 000);
    if(rv == -1)
	{
	perror("chmod 2");
	return 5;
	}
    close(fd);
    }

//for if no arguments are provided
else
    { //error message explaining usage of command
    cerr << "Usage: seclog [-c] out_file message_string" << endl
         << "       where the message_string is appended to file out_file." << endl
         << "       The -c option clears the file before the message is appended" << endl;
    //return 1 for error
    return 1;
    }



//if not, read arg as file name
//create new file if necessary, 
//then check file permissions
//send error if not 000.
//


return 0;
}

int openFile(char *fileName, bool trunc, bool Exist)
    {
    if(Exist == 1)
        {
    	int rv = chmod(fileName, 146);
    	if(rv == -1)
            {
            perror("chmod 1");
            return 5;
            }
	}

    if(trunc == 0)
        {
        int fd;
        if(Exist == 0)
            fd = open(fileName, O_WRONLY | O_CREAT | O_APPEND, 146);
        else
            fd = open(fileName, O_WRONLY | O_APPEND);
        //check to see if file opened
        if(fd == -1) 
            {
            perror("open");
            } 
        return fd;
        }
    else   
        {
        int fd;
        if(Exist == 0)
            fd = open(fileName, O_WRONLY | O_CREAT | O_TRUNC, 000);
        else
            fd = open(fileName, O_WRONLY | O_TRUNC);
        //check to see if file opened
        if(fd == -1) 
            {
            perror("open");
            } 
        return fd;
        }
    }


