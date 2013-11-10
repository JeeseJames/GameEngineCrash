#include "Random.h"
#include "time.h"
#include <stdlib.h>
using namespace CSC2110;

Random* Random::random = new Random();

Random::Random()
{
   srand (time(NULL));
}

Random::~Random()
{}

Random* Random::getRandomNumberGenerator()
{
   return random;
}

int Random::getRandomInt(int lower, int upper)
{
   int diff = upper - lower + 1;
   int random_num = rand()%diff;  
   random_num = random_num + lower;  //gives a number between lower and upper, inclusive
   return random_num;
}