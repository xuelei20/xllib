set(comm_SRCS
  BlockingQueue.hpp
  CountDown.cpp
  CurrentThread.cpp
  File.cpp
  stringHelper.cpp
  ThreadPool.cpp
  )

add_library(xuel_comm ${comm_SRCS})
target_link_libraries(xuel_comm pthread)
