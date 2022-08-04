#include <iostream>
#include <iomanip>
#include <deque>
#include <string>
#include <stack>
#include <algorithm>
using namespace std;


typedef struct 
{ 
    int id;         // id starts at 1
    string lp;      // license plate of car
    int no_mv;      // number times the car has been moved
}CAR; 

void get_input_vals(const string &line, char &act, string &lp);
void arrival(const CAR &car, deque<CAR> &D);
void departure(const string &lp, deque<CAR> &D, stack<CAR> &S);


int main()
{
//declare all needed variables
string line, lp;
CAR car;
deque<CAR> garage;
stack<CAR> street;
char action;
int n=1; //used to count car id

//cin each vehicle, find action and lp with get_input_vals
//then call arrival or departure depending on action
while(getline(cin, line))
    {
    get_input_vals(line, action, lp);
    if(action == 'A')
        {
        car.id = n++;
        car.lp = lp;
        car.no_mv = 0;
        arrival(car, garage);
        }
    else if(action == 'D')
        departure(lp, garage, street);
    else
        cout << endl << "'" << action << "': Invalid Action!" << endl;
    line.clear();
    lp.clear();
    }


return 0;
}


/*******************************************************
get_input_vals

purpose: takes input string line and puts the first char into
        act, and then the rest into lp
arguments:const string, char, string
*******************************************************/
void get_input_vals(const string &line, char &act, string &lp)
{
act = line[0];
char c; //used to transfer parts of string to new string
        // unsure if this is needed, but it made it work better
for(int i = 2; line[i] != ':'; i++) 
    {
    c = line[i];
    lp.push_back(c);
    }

}

/*******************************************************
arrival

purpose: adds new car object to deque, and prints that car has
        arrives, or that the 10 car garage is full
arguments: car struct, and deque<CAR> object
*******************************************************/
void arrival(const CAR &car, deque<CAR> &D)
{
int count = D.size();
//print what car has arrived
cout<< "Car " << car.id << " with license plate \"" << car.lp << "\" has arrived." << endl  << endl;
//if D has 10 CAR objects, print garage is full
//else add it to the deque
if(count == 10)
    {
    cout << "\t But the garage was full!" << endl;
    }
else
    {
    D.push_front(car);
    }

}

/*******************************************************
departure

purpose: removes given car from deque, and if not found prints message
        moves cars in front of car leaving into stack to hold their place, 
        and then moves them back into the deque.
arguments: const string, deque<CAR> object, and stack<CAR> object
*******************************************************/
void departure(const string &lp, deque<CAR> &D, stack<CAR> &S)
{
deque<CAR>::iterator temp;
//end() points to the variable after the last one, so always subtract 1
temp = D.end() - 1;
int i = 0;
//set place to something out of bounds, to see if it was actually found or not
int place = 13;
//finds place in the deque from the back, or from least recent car
while(temp != D.begin())
    {
    if(temp->lp == lp)
        {
        place = i--;
        }
    i++;
    temp--;
    }


CAR tempCar; //temporary struct obj to transfer data
int j =0;
//if out bounds still, car was not found, print error
if(place == 13)
    {
    cout << "No car with the license plate \"" << lp << "\" is in the garage." << endl;
    }
//else remove all cars from in front of it by putting them in a LIFO stack
//this is easy transfer in and out.
else
    {
    while( j != place)
        {
        temp = D.end()-1;//start from least recent car
        //transfer into temp struct
        tempCar.id = temp->id; 
        tempCar.lp = temp->lp; 
        tempCar.no_mv = temp->no_mv; 
        tempCar.no_mv++;//increase the times moved
        //add to stack and then remove from deque
        S.push(tempCar);
        D.pop_back();
        j++;
        }
    //now last element is the car to be moved, print message and pop it from deque
    temp = D.end()-1;
    temp->no_mv++;
    cout << "Car " << temp->id << " with license plate \"" << temp->lp << "\" has departed," << endl
            << "\t car was moved " << temp->no_mv << " times in the garage." << endl  << endl ;
    D.pop_back();

    //now a loop to put the cars in the stack back into the deque
    while(!S.empty())
        {
        tempCar = S.top();
        S.pop();
        D.push_back(tempCar);
        }
    }


}


