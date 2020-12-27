set(xxDemo "CountDownDemo")
add_executable(${xxDemo} ${xxDemo}.cpp)
target_link_libraries(${xxDemo} xuel_comm)

set(xxDemo "stringHelperDemo")
add_executable(${xxDemo} ${xxDemo}.cpp)
target_link_libraries(${xxDemo} xuel_comm)

set(xxDemo "ThreadPoolDemo")
add_executable(${xxDemo} ${xxDemo}.cpp)
target_link_libraries(${xxDemo} xuel_comm)

set(xxDemo "FileDemo")
add_executable(${xxDemo} ${xxDemo}.cpp)
target_link_libraries(${xxDemo} xuel_comm)

set(xxDemo "LoggerDemo")
add_executable(${xxDemo} ${xxDemo}.cpp)
target_link_libraries(${xxDemo} xuel_comm)

set(xxDemo "LogFileDemo")
add_executable(${xxDemo} ${xxDemo}.cpp)
target_link_libraries(${xxDemo} xuel_comm)
