#include "ErrorLogManager.h"
using namespace std;

ErrorLogManager::ErrorLogManager(std::string file_name)
{
   create(file_name);
}

ErrorLogManager::~ErrorLogManager()
{
   close();
}

void ErrorLogManager::create(std::string file_name)
{
   log_file.open(file_name.c_str());
}

void ErrorLogManager::flush()
{
   log_file << log_buffer.str();
   log_file.flush();
   log_buffer.str("");
}

void ErrorLogManager::close()
{
   log_file.close();
}

void ErrorLogManager::logException(GameException& ge)
{
   log_buffer << "****EXCEPTION****\r\n";
   flush();

   log_buffer << getTimeString() << "\r\n" << ge.getMessage();
   flush();

   log_buffer << "*****************\r\n";
   flush();
}

void ErrorLogManager::logException(std::string exception_message)
{
   log_buffer << "****EXCEPTION MESSAGE****\r\n";
   flush();

   log_buffer << getTimeString() << "\r\n" << exception_message<<endl;
   flush();

   log_buffer << "*****************\r\n";
   flush();
}


void ErrorLogManager::logProgress(const char* msg)
{
   log_buffer << "****PROGRESS****\r\n";
   flush();

   log_buffer << getTimeString() << "\r\n" << msg << "\r\n";
   flush();

   log_buffer << "****************\r\n";
   flush();
}

void ErrorLogManager::logProgress(std::string msg)
{
   log_buffer << "****PROGRESS****\r\n";
   flush();

   log_buffer << getTimeString() << "\r\n" << msg << "\r\n";
   flush();

   log_buffer << "****************\r\n";
   flush();
}

void ErrorLogManager::logAssertionFailure(std::string src_file_name, int line_number)
{
   log_buffer << "****ASSERTION FAILURE****\r\n";
   flush();

   stringstream error_str;
   error_str << "Assertion Failed: " << "\r\nSrc File: " << src_file_name << "\r\nLine Number: " << line_number << "\r\n";
   string error_text = error_str.str();

   log_buffer << getTimeString() << "\r\n" << error_text;
   flush();

   log_buffer << "*************************\r\n";
   flush();
}

std::string ErrorLogManager::getTimeString()
{
   std::stringstream time_str;

   struct tm *pTime;
   time_t ctTime; 
   time(&ctTime);
   pTime = localtime(&ctTime);

   time_str << std::setw(2) << std::setfill('0') << pTime->tm_hour << ":";
   time_str << std::setw(2) << std::setfill('0') << pTime->tm_min << ":";
   time_str << std::setw(2) << std::setfill('0') << pTime->tm_sec;

   return time_str.str();
}

