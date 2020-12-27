#ifndef XUEL_LOGFILE_H
#define XUEL_LOGFILE_H

#include "noncopyable.h"
#include "File.h"

#include <memory>
#include <string>

namespace xuel
{

class LogFile : noncopyable
{
public:
  LogFile();

  std::string getLogName();
  void append(const char* data);
  void flush(); 

private:
  std::unique_ptr<File> m_file;
  std::string m_baseName;
};

} // namespace

#endif // XULE_
