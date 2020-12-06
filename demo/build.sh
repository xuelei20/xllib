binpath="bin"
g++ MutexDemo.cpp -pthread -o ${binpath}/MutexDemo
g++ BlockQueueDemo.cpp -pthread -o ${binpath}/BlockQueueDemo
g++ CountDownDemo.cpp -pthread -o ${binpath}/CountDownDemo
g++ SingletonDemo.cpp -pthread -o ${binpath}/SingletonDemo
