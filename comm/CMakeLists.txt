set(comm_SRCS
  BlockingQueue.hpp
  CountDown.cpp
  CurrentThread.cpp
  File.cpp
  LogFile.cpp
  Logger.cpp
  LogStream.cpp
  ProcessInfo.cpp
  stringHelper.cpp
  ThreadPool.cpp
  Timestamp.cpp
  )

add_library(xuel_comm ${comm_SRCS})
target_link_libraries(xuel_comm pthread)
