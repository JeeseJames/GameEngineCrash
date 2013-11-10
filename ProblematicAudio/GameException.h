#if !defined (GAME_EXCEPTION)
#define GAME_EXCEPTION

#include <string>
#include <sstream>

class GameException
{
   private:
      std::string error_text;
      int error_number;

   public:
      GameException(int error_number, std::string error_desc, std::string src_file_name, int line_number);
      virtual ~GameException() throw () {};  //this method is not allowed to throw exceptions
      const char* getMessage();
      int getErrorNumber();
};

#endif