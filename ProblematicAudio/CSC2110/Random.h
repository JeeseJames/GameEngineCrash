#if !defined (RANDOM_H)
#define RANDOM_H

namespace CSC2110
{

class Random
{
   private:

      Random();
      virtual ~Random();
      static Random* random;

   public:

      static Random* getRandomNumberGenerator();
      int getRandomInt(int lower, int upper);
};

}

#endif
