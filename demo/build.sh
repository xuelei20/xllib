binpath="bin"
g++ MutexDemo.cpp -pthread -g -o ${binpath}/MutexDemo
g++ BlockQueueDemo.cpp -pthread -g -o ${binpath}/BlockQueueDemo
g++ CountDownDemo.cpp -pthread -g -o ${binpath}/CountDownDemo
g++ SingletonDemo.cpp -pthread -g -o ${binpath}/SingletonDemo
g++ CopyOnWrite.cpp -pthread -g -o ${binpath}/CopyOnWrite
