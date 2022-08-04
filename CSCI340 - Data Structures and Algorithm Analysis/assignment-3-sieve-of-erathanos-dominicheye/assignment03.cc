#include <iostream>
#include <set>
#include <iomanip>

using std::set;
#define NO_ITEMS 16
#define ITEM_W 5

void sieve(set<int>& s, int n)
	{
	for(int i = 2; i < n; i++)
		{
		s.insert(i);
		}
	
	set<int>::iterator nextPrime = s.begin();
	set<int>::iterator divider;
	
	
	for(int i = 2; i * i < n; i++)
		{
		//logic behind this is that iterator is at next value there, so it 
		//i continues until it hits the next prime number which is where the iterator is
		if(i == *nextPrime)
			{
			nextPrime++; //go to next number in the set
			divider = nextPrime;
			int k;
			while(divider != s.end())
				{
				k = *divider;
				divider++; //go to next element
				if((k % i) == 0)
					{
					s.erase(k); //delete element if divisible by i
					}
				
				}
			
			}
		
		}
	}

void print_primes(const set<int>& s)
	{
	int count = 0;
	for(set<int>::iterator print = s.begin(); print != s.end(); print++)
		{
		std::cout << std::setw(ITEM_W) << *print;
		count++;
		if(count == NO_ITEMS)
			{
			std::cout << std::endl;

			count = 0;
			}
		
		}
	}

int
main()
	{
	std::cout << "Upper limit for the set of primes: 2000"<< std::endl << std::endl;
	set<int> sieve1;
	sieve(sieve1, 2000);

	print_primes(sieve1);
	std::cout << std::endl;
	return 0;
	}
