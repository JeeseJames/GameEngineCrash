#include "FileIO.h"
using namespace CSC2110;

bool FileIO::status()
{
   return good;
}

void FileIO::setUp(const char* fle, FileOp op)
{
   good = true;
   operation = op;

   if (operation == READ)
   {
      infile = new ifstream(fle);

      if (!infile->good())
      {
         good = false;
         return;
      }
   }
   else
   {
      outfile = new ofstream(fle);

      if (!outfile->good())
      {
         good = false;
         return;
      }
   }

   ef = false;
}

FileIO::FileIO(String* fle, FileOp op)  
{
   char* fle_char = fle->toCharArray();
   setUp(fle_char, op);
   delete[] fle_char;
}

FileIO::FileIO(const char* fle, FileOp op) 
{
   setUp(fle, op);
}

FileIO::FileIO(const char* fle, char delim)  //assumed to be a read
{
   good = true;
   infile = new ifstream(fle);

   if (!infile)
   {
      cout << "error opening file" << endl;
      good = 0;
      return;
   }

   delimiter = delim;
   operation = READ;
   ef = false;
}

FileIO::~FileIO()
{
   if (operation == READ)
   {
      infile->close();
      delete infile;
   }
   else
   {
      outfile->close();
      delete outfile;
   }
}

String* FileIO::entireFile()
{
   String* cr = new String("\n");
   String* line = readLine();

   while(!eof())
   {
      String* str = line->append(cr); 
      delete line;
      line = str;
      str = readLine();
      String* temp = line->append(str);
      delete str;
      delete line;
      line = temp;
   }

   delete cr;
   return line;
}

bool FileIO::eof()
{
   return ef;
}

String* FileIO::readLine()
{
   String* line = NULL;

   if (operation != READ)  //opened for writing so read disallowed
   {
       return NULL;
   }

   if (!ef)
   {
      string text;
      getline(*infile, text);

      line = String::convertToString(&text);

      if (infile->eof())
      {
         ef = true;
      }
   }

   return line;
}

void FileIO::writeLine(String* line)
{
   if (operation == WRITE)
   {
      char* text = line->toCharArray();
      *outfile << text << "\r\n";  //probably just \n here
      delete[] text;
   }
}

void FileIO::write(String* line)
{
   if (operation == WRITE)
   {
      char* text = line->toCharArray();
      *outfile << text;
      delete[] text;
   }
}

// read a whole line and return an iterator for its tokens
ListArrayIterator<String>* FileIO::getTokens()
{
   if (operation != READ)  //opened for reading so writing disallowed
   {
      return NULL;
   }

   ListArrayIterator<String>* tokens;

   if (!ef)
   {
      string text;
      getline(*infile, text);

      String* line = String::convertToString(&text);

      tokens = line->getTokens(delimiter);
      delete line;

      if (infile->eof())
      {
         ef = true;
      }
   }

   return tokens;
}

