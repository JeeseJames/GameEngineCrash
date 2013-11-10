#include "GameException.h"

GameException::GameException(int error_number, std::string error_desc, std::string src_file_name, int line_number)
{
   this->error_number = error_number;
   std::stringstream error_str;
   error_str << "Error Number: " << error_number << "\r\nError Desc: " << error_desc << "\r\nSrc File: " << src_file_name << "\r\nLine Number: " << line_number << "\r\n";
   error_text = error_str.str();
}

const char* GameException::getMessage()
{
   return error_text.c_str();
}

int GameException::getErrorNumber()
{
   return error_number;
}
