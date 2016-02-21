OBJS = squareSolver workerThread
CC = g++-4.5
CFLAGS = -g -std=c++0x

all : $(OBJS)

2.4 : squareSolver2.cpp workerThread4.cpp
	$(CC) $(CFLAGS) workerThread4.cpp -o workerThread
	$(CC) $(CFLAGS) squareSolver2.cpp -o squareSolver

uber : workerThread3.cpp squareSolver
	$(CC) $(CFLAGS) workerThread3.cpp -o workerThread

optimized : workerThread2.cpp squareSolver
	$(CC) $(CFLAGS) workerThread2.cpp -o workerThread
	
squareSolver : squareSolver.cpp
	$(CC) $(CFLAGS) squareSolver.cpp -o squareSolver

workerThread : workerThread.cpp
	$(CC) $(CFLAGS) workerThread.cpp -o workerThread

clean:
	\rm squareSolver workerThread
