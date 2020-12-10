binpath="bin"
g++ MutexDemo.cpp -pthread -g -o ${binpath}/MutexDemo
g++ ProducerConsumer.cpp -pthread -g -o ${binpath}/ProducerConsumer
g++ CountDownDemo.cpp -pthread -g -o ${binpath}/CountDownDemo
g++ SingletonDemo.cpp -pthread -g -o ${binpath}/SingletonDemo
g++ CopyOnWrite.cpp -pthread -g -o ${binpath}/CopyOnWrite
g++ ThreadPoolDemo.cpp -pthread -g -o ${binpath}/ThreadPoolDemo
