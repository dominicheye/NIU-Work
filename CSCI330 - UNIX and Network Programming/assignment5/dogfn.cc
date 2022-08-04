#include "dog.h"

void writeToBinary(int n) 
    { 
    // char array to store binary
    char cArray[8] = {48,48,48,48,48,48,48,48}; //48 is 0 in ASCII
    // counter for binary array 
    int i = 0, k = 7; 
    int m;
    while (n > 0)
        { 
        // storing remainder in binary array 
        m = n % 2; 
        cArray[k] = m + 48;
        n = n / 2; 
        i++;
        k--; 
        }
     
    write(1, cArray, 8);
    
    } 


void findFlags(Flags *flag, int argc, char* argv[])
    {
    int opt;
    while( (opt = getopt(argc, argv, "s:n:c:r:xb")) != -1)
        {
        switch(opt){
            case 's':
                flag->bufOpt = 1;
                flag->bufSize = optarg;
                break;
            case 'n':
                flag->readOpt = 1;
                flag->readSize = optarg;
                break;
            case 'c':
                flag->caesarOpt = 1;
                flag->shift = optarg;
                break;
            case 'r':
                flag->rotateOpt = 1;
                flag->shift = optarg;
                break;
            case 'x':
                flag->hexOpt = 1;
                break;
            case 'b':
                flag->binOpt = 1;
                break;
            default:
                cerr << "The given flag of -" << (char)opt << " is not allowed." << endl;
        }
        }
    }

void readFile(Flags* flag, int optind, char* argv[], int argc )
    {
    int nr;
    size_t nw;
    for(int i = optind; i < argc; i++)
        {
        int fd = open(argv[i], O_RDONLY);
        //check to see if file opened
        if(fd == -1) 
            {
            perror("open");
            }

        
        //start with creating a buffer, if -s was used then use the number given
        if(flag->bufOpt == 1)
            {
            int l = atoi(flag->bufSize); //changes size given into int
            char *buffer = new char[l]; //creates buffer at size given
            
            if(flag->readOpt == 1)
                {
                int readCount = atoi(flag->readSize);
                while(readCount != 0 && nr != 0)
                    {
                    if(l < readCount)
                        {
                        nr = read(fd, buffer, l);
                        if(nr == -1)
                                {
                                perror("read");
                                return;
                                }
                        
                        nw = write(1, buffer, nr);
                        readCount = readCount - nw;
                        }
                    else 
                        {
                        nr = read(fd, buffer, readCount);
                        if(nr == -1)
                                {
                                perror("read");
                                return;
                                }
                        
                        nw = write(1, buffer, nr);
                        readCount = readCount - nw;
                        }
                    }
                }
            else 
                {
                nr = read(fd, buffer, l);
                while(nr != 0) 
                    {
                    if(nr == -1)
                        {
                        perror("read");
                        }
                    
                    size_t nw;
                    nw = write(1, buffer, nr);
                    nr = read(fd, buffer, l);
                    nw = nw;
                    }
                }
            delete[] buffer;   
            }
        else   
            {
            char buffer[255];
            if(flag->readOpt == 1)
                {
                int readCount = atoi(flag->readSize);
                /*if(flag->binOpt == 1)
                    {
                    nr = read(fd, buffer, readCount);
                    while(nr != 0)
                        {
                        if(flag->caesarOpt == 1)
                            {
                            for(int i = 0; i < nr; i++)
                                {
                                if((buffer[i] > 65 && buffer[i] < 90) || (buffer[i] > 97 && buffer[i] < 122))
                                    {
                                    buffer[i] = buffer[i] + atoi(flag->shift);
                                    if((buffer[i] < 65 && buffer[i] > 90) || (buffer[i] < 97 && buffer[i] > 122))
                                        buffer[i] = buffer[i] - 25;
                                    }
                                }
                            }
                           
                        if(flag->rotateOpt == 1)
                            {
                            for(int i = 0; i < nr; i++)
                                    {
                                    buffer[i] = buffer[i] + atoi(flag->shift);
                                    }
                            }
                        
                        for(int i = 0; i < nr; i++)
                            writeToBinary((int)buffer[i]);
                        nr = read(fd, buffer, 255);
                        }
                    }*/
                while(readCount != 0 && nr != 0)
                    {
                    if(255 < readCount)
                        {
                        nr = read(fd, buffer, 255);
                        if(nr == -1)
                                {
                                perror("read");
                                return;
                                }
                        
                        nw = write(1, buffer, nr);
                        readCount = readCount - nw;
                        }
                    else 
                        {
                        nr = read(fd, buffer, readCount);
                        if(nr == -1)
                                {
                                perror("read");
                                return;
                                }
                        
                    
                        nw = write(1, buffer, nr);
                        readCount = readCount - nw;
                        }
                    }
                }
            else 
                {
                
                nr = read(fd, buffer, 255);
                while(nr != 0) 
                    {
                    if(nr == -1)
                        {
                        perror("read");
                        }
                    
                    size_t nw;
                    nw = write(1, buffer, nr);
                    nr = read(fd, buffer, 255);
                    nw = nw;
                    }
                }
            }
    
        write(1, "\n", 1);
        }
    }