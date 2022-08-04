#include "josephus.h"

int main()
{
//declare all needed variables
args Jo1;
list<string> List1;
int count = 0;
size_t i = 0;
size_t j;
list<string>::iterator p;
//fill the struct and the list.
init_vals(List1, Jo1);

//loop to delete a person every M people, and print it every K eliminations
while(List1.size() != 1)
    {
    //find next postion of person to be eliminated
    j=(i+(Jo1.M-1))%List1.size();
    //if the number of people eliminated is a multiple of 7 print
    if(count % Jo1.K == 0)
        print_list(List1, count);
    //set position at i and at p
    i = j;
    p = List1.begin();
    advance(p,j);
    //delete person
    List1.erase(p);
    //if the position was the last one, it would be outside bounds now, so restart at 0
    if(i >= List1.size())
        i=0;
    //increase the amount of eliminations
    count++;
    }
//final print
print_list(List1, count);

return 0;
}