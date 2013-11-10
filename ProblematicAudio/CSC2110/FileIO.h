#if !defined (FILEOP)
#define FILEOP

   enum FileOp {READ, WRITE};

#endif

#if !defined (FILEIO_H)
#define FILEIO_H

#include "String.h"

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

namespace CSC2110
{

class FileIO
{
   private:
      FileOp operation;
      char delimiter;
      ifstream* infile;
      ofstream* outfile;
      bool ef;
      bool good;

      void setUp(const char* fle, FileOp op);

   public:
      FileIO(String* fle, FileOp op);
      FileIO(const char* file, FileOp op);
      FileIO(const char* file, char delim);
      ~FileIO();

      bool eof();
      String* readLine();
      void writeLine(String* line);
      void write(String* line);
      bool status();
      String* entireFile();
      ListArrayIterator<String>* getTokens();
};

}
#endif
