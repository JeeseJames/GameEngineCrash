#if !defined (ERRORLOG_MANAGER)
#define ERRORLOG_MANAGER

#include "GameException.h"
#include <iostream>
#include <time.h>
#include <iomanip>
#include <fstream>

#ifndef THROW_EXCEPTION
#define THROW_EXCEPTION(error_num, error_desc) throw GameException(error_num, error_desc, __FILE__, __LINE__);
#endif

#ifndef ASSERT
#define ASSERT(expr) if (!expr) {error_log_manager->logAssertionFailure(__FILE__, __LINE__);}
#endif

class ErrorLogManager
{
   private:
      std::stringstream log_buffer;
      std::ofstream log_file;

      void create(std::string file_name);

      void flush();
      void close();

      std::string getTimeString();

   public:
      ErrorLogManager(std::string file_name);
      virtual ~ErrorLogManager();

      void logException(GameException& ge);
	  void logException(std::string exception_message);
      void logAssertionFailure(std::string src_file_name, int line_number);
      void logProgress(const char* msg);
	  void logProgress(std::string msg);
};

#endif
