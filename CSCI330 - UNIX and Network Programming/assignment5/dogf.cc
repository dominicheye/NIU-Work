#include "dog.h"


//writes the int fiven as a binary number to standard output
void writeToBinary(int n) 
    { 
    // char array to store binary
    char cArray[8] = {48,48,48,48,48,48,48,48}; //48 is 0 in ASCII
    // counter for binary array 
    int k = 7; 
    int m;
    while (n > 0)
        { 
        // storing remainder in binary array 
        m = n % 2; //find remainder, gives next LSB
        cArray[k] = m + 48; // add to array, with +48 to make
        n = n / 2; //reduce n by 2, effectively removing the LSB
        k--; //decrease k so that the next array spot taken is the next sig. bit
        }
     
    write(1, cArray, 8); //write the byte to standard output
    } 


//writes the int given as a hex number to standard output
void writeToHex(int n)
    {
    int rem, i=1; //rem is part of the hex number, but in decimal, i is place in array
    char hex[2]; //array to hold hex num
    while (i > -1)   // Do this 2 times, i =1 and i =0, bc we need 2 digits for one byte.
        {
        rem = n % 16; // Get the remainder.
        if (rem > 9) //if hex nums are greater then 10 you have to use letters
            {
                //put the big number into the array, storing it as a letter
                switch (rem)
                    {
                    case 10: hex[i] = 'a'; break;
                    case 11: hex[i] = 'b'; break;
                    case 12: hex[i] = 'c'; break;
                    case 13: hex[i] = 'd'; break;
                    case 14: hex[i] = 'e'; break;
                    case 15: hex[i] = 'f'; break;
                    }
            }
        else //if its 1-9, can be stored into array normally
            {
            hex[i] = char(rem + 48); // Converts integer (0-9) to ASCII code.
            // x + 48 is the ASCII code for x digit
            }
        n = n/16; //reduce it by 16 to get to the next digit
        i--; //go to the next sig. spot in array
        }
    write(1, hex, 2); //write hex to standard outputs
    }


//looks for the optional parameters given and stores them and their arguments
void findFlags(Flags *flag, int argc, char* argv[])
    {
    int opt;
    /************
     * could put in comments for each of these, but it is pretty self explanatory
     * for each time getopt is run, opt stores the return of getopt, and then the switch
     * statement chooses which argument was given. turns on the flag if given, and 
     * also stores an argument (usually a number) in a second varaible from the struct
     * with optarg.
     * default is whenever a -something is not s n c r x or b
     ***********/
    while( (opt = getopt(argc, argv, "s:n:c:r:xb")) != -1)
        {
        switch(opt)
            {
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
                cerr << "The given flag of -" << opt << " is not allowed." << endl;
            }
        }
    }


//reads the file with whatever parameters are given
void readFile(Flags *flag, int optind, char* argv[], int argc, int bufferSize)
    {
    int nr; //for read
    size_t nw; //for write
    char *buffer = new char[bufferSize]; //creates buffer at size given
    //first decide what case we have for output
    int caseNum = 0; //case for not binary or hex
    if(flag->binOpt == 1) //case for binary
        caseNum = 1;
    if(flag->hexOpt == 1) //case for hex
        caseNum = 2;

    for(int i = optind; i < argc; i++) //read all files with loop
        {
        int fd = open(argv[i], O_RDONLY); //open file
        //check to see if file opened
        if(fd == -1) 
            {
            perror("open");
            }
        
        /*******************
         this if-else statement is for -n (if means -n is present, else is not)
         *******************/
        if(flag->readOpt == 1) 
            {
            int readCount = atoi(flag->readSize);//switch char to int
            //switch statement for the different cases
            switch(caseNum)
                {
                case 0: //not binary or hex
                    while(readCount != 0 && nr != 0) //until we reached full argument or the file ends
                        {
                        if(bufferSize < readCount) //if the buffersize is smaller, then read full buffer size
                            {
                            nr = read(fd, buffer, bufferSize); //read
                            if(nr == -1) //check to see if it read
                                    {
                                    perror("read");
                                    return;
                                    }
                            //apply -c or -r if necessary (if statement inside function)
                            caesarSwitch(flag, buffer, nr);
                            rotate(flag, buffer, nr);
                            //write everything you read
                            nw = write(1, buffer, nr);
                            readCount = readCount - nw; //remove how much you wrote from readCount
                            }
                        else //if readCount is smaller only read up to readCount
                            {
                            nr = read(fd, buffer, readCount); //read
                            //apply -c or -r if necessary (if statement inside function)
                            caesarSwitch(flag, buffer, nr);
                            rotate(flag, buffer, nr);

                            if(nr == -1)//check to see if it read
                                    {
                                    perror("read");
                                    return;
                                    }
                            //write everything read
                            nw = write(1, buffer, nr);
                            readCount = readCount - nw; //remove write count from readCount (should go to 0)
                            }//end of else
                        }//end of while loop
                    break;
                
                case 1: //binary case
                    nr = read(fd, buffer, readCount); //read
                    while(readCount != 0) //until readCount is fulfilled
                        {
                        //apply -c or -r if necessary (if statement inside function)
                        caesarSwitch(flag, buffer, nr);
                        rotate(flag, buffer, nr);
                        for(int i = 0; i < readCount; i++)//for each char in buffer, send to function to be written as binary
                            writeToBinary((int)buffer[i]);
                            
                        readCount = readCount - nr;//remove all read from readCount
                        nr = read(fd, buffer, bufferSize); //read more
                        }
                    break;
                case 2:
                    nr = read(fd, buffer, bufferSize); //read
                    
                    while(nr != 0 && readCount > 0 )
                        {
                        //apply -c or -r if necessary (if statement inside function)
                        caesarSwitch(flag, buffer, nr);
                        rotate(flag, buffer, nr);
                        if(nr <= readCount) // if nr is smaller, then only write that much
                            {
                            for(int m = 0; m < nr; m++)//for each char in buffer, send to function to be written as hex
                                writeToHex((int)buffer[m]); 
                            }
                        else // if readCount was smaller then write readCount amount
                            {
                            for(int m = 0; m < readCount; m++)//for each char in buffer, send to function to be written as hex
                                writeToHex((int)buffer[m]);   
                            }
                        readCount = readCount - nr;//subract amount read from readCount
                        nr = read(fd, buffer, bufferSize);//read again
                        }
                    break;
                }
            }//end of if(flag->bufOpt == 1)
        else 
            {
            switch(caseNum)
                {
                case 0: //if not binary or hex
                    nr = read(fd, buffer, 255);//read
                    while(nr != 0) //until everything is read
                        {
                        if(nr == -1)//check to see if it read
                            {
                            perror("read");
                            }
                        //apply -c or -r if necessary (if statement inside function)
                        caesarSwitch(flag, buffer, nr);
                        rotate(flag, buffer, nr);

                        nw = write(1, buffer, nr); //write everything read to standard output
                        nr = read(fd, buffer, 255); //read again
                        nw = nw; //just to get rid of warning that nw was not used
                        }
                    break;
                
                case 1: //for binary
                    nr = read(fd, buffer, bufferSize);//read as much as possible
                    while(nr != 0)//until everything is read
                        {
                        //apply -c or -r if necessary (if statement inside function)
                        caesarSwitch(flag, buffer, nr);
                        rotate(flag, buffer, nr);
                        for(int i = 0; i < nr; i++)//send all char read to binary function
                            writeToBinary((int)buffer[i]);
                            
                        nr = read(fd, buffer, bufferSize);//read again
                        }
                    break;
                case 2: //for hex
                    nr = read(fd, buffer, bufferSize); //read as much as possible
                    while(nr != 0)//until everything is read
                        {
                        //apply -c or -r if necessary (if statement inside function)
                        caesarSwitch(flag, buffer, nr);
                        rotate(flag, buffer, nr);
                        for(int i = 0; i < nr; i++)//send all char read to hex function
                            writeToHex((int)buffer[i]);
                            
                        nr = read(fd, buffer, bufferSize);//read agian
                        }
                    
                    break;
                }//end of else(if(flag->bufOpt == 1))
        
            close(fd);// close file
            }
        write(1, "\n", 1);//write a newline to make output pretty
        }//end of for loop
    delete[] buffer;//delete the buffer since it was dynamically stored
    }




//checks to see if -c was present, if so moves all alphabetical char by flag->shift
void caesarSwitch(Flags *flag, char *buffer, int nr)
    {
    if(flag->caesarOpt == 1) //check for flag
        {
        for(int i = 0; i < nr; i++)//for all characters
            {
            if((buffer[i] > 65 && buffer[i] < 90) || (buffer[i] > 97 && buffer[i] < 122))//checks to see if a-z or A-Z
                {
                buffer[i] = buffer[i] + atoi(flag->shift); //shift the char by flag->shift
                if((buffer[i] < 65 && buffer[i] > 90) || (buffer[i] < 97 && buffer[i] > 122))//checks to see if outside a-z or A-Z
                    buffer[i] = buffer[i] - 25; //if so then shift back 25 to get to correct letter, otherwise will be weird ASCII thingy
                }
            }
        }
    }








//checks to see if -r was present, if so moves all char by flag->shift
void rotate(Flags *flag, char *buffer, int nr)
    {
    if(flag->rotateOpt == 1)//check for flag
        {
        for(int i = 0; i < nr; i++)//for all characters
                {
                buffer[i] = buffer[i] + atoi(flag->shift);//shift the char by flag->shift
                }
        }
    }
