// Example program showing that seeding works consistently
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main()
{
  int x = 0;
  int i=0;
  srand(123457);
  while(i <= 10) {
      x = rand() % 10 + 1;
      std::cout << "mod 10 +1: " << x << "\n";
      ++i;
  }
  i=0;
  while (i <= 10) {
      x = rand();
      std::cout << "rand: " << x << "\n";
      ++i;
  }
  exit(0);
}
