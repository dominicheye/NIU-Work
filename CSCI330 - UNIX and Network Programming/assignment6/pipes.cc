/*
Dominic Heye
Z1841746

Assignment 6 Pipes
CSCI330
*/
#include <unistd.h>
#include <iostream> 
#include <sys/types.h>
#include <sys/wait.h>
#include <string>
#include <cstring>
#include <string.h>


using namespace std;

int main()
{
int pipefd[2];
int rs;
char *in1[6] = {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr}; //for command 1
char *in2[6] = {nullptr,nullptr,nullptr,nullptr,nullptr,nullptr}; //for command 2

//read in user commands as strings
string ins1, ins2;
cout << "command 1? ";
getline(cin, ins1); //reads whole line
cout << "command 2? ";
getline(cin, ins2); //reads whole line

//find lengths so that we can convert strings to char arrays
int n = ins1.length();
int m = ins2.length();
//create char arrays
char instar1[n+1], instar2[m+1];
//convert the strings to char arrays so strtok() can work
strcpy(instar1, ins1.c_str());
strcpy(instar2, ins2.c_str());

//create variables needed for loops to copy everything into the char* arrays
//that will be used in execvp()
int i = 0;
char *buffer;
//strtok returns the first block of char* that is before the first space
buffer = strtok(instar1, " ");
while(buffer != NULL)//do this until there is nothing returned
    {
    in1[i] = buffer; //put argument into corresponding spot in char*array
    buffer = strtok(NULL, " "); //use instar1 again
    i++; 
    }
//reset i for next conversion    
i = 0;

//now again for instar2
buffer = strtok(instar2, " ");
while(buffer != NULL)
    {
    in2[i] = buffer;//put argument into corresponding spot in char*array
    buffer = strtok(NULL, " ");//use instar2 again
    i++;
    }

//set up pipe
rs = pipe(pipefd);
if(rs == -1) //this is error return
    {
    perror("pipe");
    exit(1);
    }

//start fork
rs = fork();

if(rs < 0) //error message
    {
    perror("fork");
    exit(1);
    }

//child process
if(rs == 0)
    {
    close(pipefd[1]); //close write end
    
    close(0); //close standard input
    dup(pipefd[0]); //make this standard input
    close(pipefd[0]);//close the pipe

    
    int exec; //for return code
    exec = execvp(in2[0], in2);//run 2nd command
    if(exec < 0) //error message
        {
        perror("child exec");
        exit(1);
        }
    }

else   
    {
    close(pipefd[0]); //close read end
    
    
    close(1); //close standard output
    dup(pipefd[1]); //make this standard output
    close(pipefd[1]);//close the pipe

    
    int exec;//for return code
    exec = execvp(in1[0], in1);//run 1st command
    if(exec < 0) //error message
        {
        perror("parent exec");
        exit(1);
        }
    
    }


return 0;
}