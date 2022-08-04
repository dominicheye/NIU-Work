#include <unistd.h>
#include <iostream> 
#include <sys/types.h>
#include <sys/wait.h>
#include <string>


using namespace std;

int main()
{
string input;
int pipefd[2];
int rs;

rs = pipe(pipefd);
if(rs == -1)
    {
    perror("pipe");
    return(1);
    }
cout << "gimme something baby ";
cin >> input;


while(input != "done" && input != "Done")
    {

    pid_t pid = fork();
    wait(nullptr);
    if(pid == -1)
        {
        perror("fork");
        return(1);
        }
    else if(pid  == 0)//child process
        {

        pid_t pid2 = fork();
        if(pid2 == -1)
            {
            perror("fork");
            return(1);
            }
        else if(pid2 == 0)
            {
            close(pipefd[0]);
            cout << "this is first!" << endl;
            close(1); //close standard output
            
            //dup write pipe into stand. output
            dup(pipefd[1]);
            close(pipefd[1]);
            rs = execlp("ls", "ls", (char *) NULL);
            if(rs < 0)
                {
                perror("execl");
                return(1);
                }

            
            }
        wait(nullptr);

        pid2 = fork();
        if(pid2 == -1)
            {
            perror("fork");
            return(1);
            }
        else if(pid2 == 0)
            {
            close(pipefd[1]);//close write end of pipe
            cout << "this is second!" << endl;
            //run ls
            close(0); //close the standard input

            //dup read pipe into stand. input
            dup(pipefd[0]);
            close(pipefd[0]); //close the read end of pipe
            rs = execlp("wc", "wc", (char *) NULL);
            if(rs < 0)
                {
                perror("execl");
                return(1);
                }
            }
        wait(nullptr);
        close(pipefd[0]);
        }
    else //parent process
        {
        
        close(pipefd[1]);

        }
    
    cout << endl << "gimme something baby ";
    cin >> input;
    }



}