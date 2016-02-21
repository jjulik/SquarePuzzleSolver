OBJS = squareSolver workerThread
CC = g++
CFLAGS = -g -std=c++0x

all : $(OBJS)

optimized : workerThread2.cpp squareSolver
	$(CC) $(CFLAGS) workerThread2.cpp -o workerThread
	
squareSolver : squareSolver.cpp
	$(CC) $(CFLAGS) squareSolver.cpp -o squareSolver

workerThread : $(WORKER)
	$(CC) $(CFLAGS) workerThread.cpp -o workerThread

clean:
	\rm squareSolver workerThread
