#if !defined (STRING_H)
#define STRING_H

#include <string>
#include <string.h>
#include "ListArrayIterator.h"

namespace CSC2110
{

class String
{
   private:
      char* str;
      int len;

   public:
      String(char* str);
      String(const char* str);
      ~String();

      int length();
      void printString();
      char* toCharArray();
      String* append(String* other);
      char charAt(int index);
      int indexOf(char token, int start);
      ListArrayIterator<String>* getTokens(char token);
      int numTokens(char token);
      static String* convertToString(std::string* s);
      int parseInt();
      float parseFloat();
      static String* intToString(int i, int num_chars);
      static String* floatToString(float f, int places);
      static int compare(String* one, String* two);
      static String* readTextFromKeyboard();
};

}
#endif
