#include "String.h"
#include "ListArray.h"

#include <stdlib.h>
#include <iostream>
#include <fstream>
using namespace std;

using namespace CSC2110;

//need a constructor that takes a const char* as a parameter as well!
String::String(const char* s) 
{
   int length = (int) strlen(s);

   str = new char[length + 1];
   for (int i = 0; i < length; i++)
   {
      str[i] = s[i];
   }

   str[length] = 0;
   len = length;  //length does not include the null terminator
}

//makes a new copy of the char array
String::String(char* s) 
{
   int length = (int) strlen(s);

   str = new char[length + 1];
   for (int i = 0; i < length; i++)
   {
      str[i] = s[i];
   }

   str[length] = 0;
   len = length;
}

String::~String()
{
   delete[] str;
}

int String::length()
{
   return len;
}

void String::printString()
{
   cout << str << endl;
}

int String::parseInt()
{
   return atoi(str);
}

float String::parseFloat()
{
   return atof(str);
}

//num_chars does not include the null terminator
String* String::intToString(int i, int num_chars)
{
   char* i_ascii = new char[num_chars + 1]; //include a place for the null terminator

   sprintf(i_ascii,"%d", i); //converts to decimal base

   String* str = new String(i_ascii);
   delete[] i_ascii;
   return str;
}

String* String::floatToString(float f, int places)
{
   places = places % 10;
   if (places <= 1) places = 2;

   char* f_ascii = new char[30];

   char* format = new char[6];
   format[0] = '%';
   format[1] = '0';
   format[2] = '.';
   format[3] = places + 48;
   format[4] = 'f';
   format[5] = 0;

   sprintf(f_ascii, format, f);  
   String* str = new String(f_ascii);
   delete[] format;
   delete[] f_ascii;
   return str;
}

char* String::toCharArray()
{
   int len = length();
   char* s = new char[len + 1];

   for (int i = 0; i <= len; i++)
   {
      s[i] = str[i];
   }

   return s;
}

String* String::append(String* str)
{
   char* first = toCharArray();
   char* second = str->toCharArray();

   int len_first = length();
   int len_second = str->length();
   char* app = new char[len_first + len_second + 1];

   for (int i = 0; i < len_first; i++)
   {
      app[i] = first[i];
   }

   for (int i = len_first; i < len_first + len_second; i++)
   {
      app[i] = second[i - len_first];
   }

   app[len_first + len_second] = 0;

   String* result = new String(app);
   delete[] app;
   delete[] first;
   delete[] second;

   return result;
}

char String::charAt(int index) //zero-based
{
   if (index < 0 || index >= len)
   {
      return 0;
   }

   return str[index];
}

int String::indexOf(char token, int start)
{
   int index = start;
   int len = length();
   while (index < len)
   {
      char test = str[index];
      if (test == token)
      {
         return index;
      }
      index++;
   }

   return index;
}

ListArrayIterator<String>* String::getTokens(char token)
{
   int num_tokens = numTokens(token);
   ListArray<String>* strings = new ListArray<String>();

   int start = 0;
   for (int j = 0; j < num_tokens; j++)
   {
      int index = indexOf(token, start);  //the index of the next token
      char* temp = new char[index - start + 1];

      for (int i = start; i < index; i++)
      {
         temp[i - start] = charAt(i);
      }
      temp[index - start] = 0;  //set null terminator
      start = index + 1;

      String* str = new String(temp);  
      strings->add(str);

      delete[] temp;
   }
    
   ListArrayIterator<String>* token_iter = strings->iterator();
   delete strings;
   return token_iter;
}

int String::numTokens(char token)
{
   int count = 1;
   int len = length();
   for (int i = 0; i < len; i++)
   {
      char test = str[i];
      if (test == token)
      {
         count++;
      }
   }
   return count;
}

String* String::convertToString(string* str)
{
   int len = str->length();
   char* buffer = new char[len + 1];
   str->copy(buffer, len, 0);
   buffer[len] = 0;
   String* temp = new String(buffer);
   delete[] buffer;
   return temp;
}

int String::compare(String* one, String* two)
{
   int one_length = one->length();
   int two_length = two->length();

   int length = one_length;
   if (two_length < one_length)
   {
      length = two_length;
   }

   for(int i = 0; i < length; i++) 
   {
      char one_char = one->charAt(i);
      char two_char = two->charAt(i);

      if (one_char != two_char)
      {
         return (one_char - two_char);
      }
   }

   //equal up to the length of the shortest string, now compare lengths
   if (one_length == two_length)
   {
      return 0;  //exact equality
   }
   else if (one_length < two_length)
   {
      return -1;
   }
   else
   {
      return 1;
   }
}

String* String::readTextFromKeyboard()
{
   string text = "";
   getline(cin, text);
   int len = text.length();
   char* temp = new char[len + 1];
   text.copy(temp, len, 0);
   temp[len] = 0;
   String* str = new String(temp);
   delete[] temp;
   return str;
}
