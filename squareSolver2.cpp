/*****************************************************************************
 *                    squareSolver
 *                    ------------
 * Author:        Joseph Julik
 * Last Revision: 03-11-2011
 * Version:       0.1
 * Description:
 *     Automatically solves square puzzles
*****************************************************************************/
#include <cstdio>
#include <sys/time.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>

#define SHM_KEY 20103947

using namespace std;

class commonThread {
	public:
	
		commonThead() {
			vop[0].sem_num = 0;
			vop[0].sem_op = 1;
			vop[0].sem_flg = 0;
			pop[0].sem_num = 0;
			pop[0].sem_op = -1;
			pop[0].sem_flg = 0;
		}
		
		void initSHM () {
			shmID = shmget(SHM_KEY, 8, 0666 | IPC_CREAT);
			shmSem = semget(IPC_PRIVATE, 1, IPC_CREAT | 0666);
			vOperation(shmSem, 0);
		}
		
	private:
		static int shmID;
		static int shmSem;
		struct sembuf vop[1]; //a V operation
		struct sembuf pop[1]; //a P operation
};

int commonOperations::shmID;
int commonOperations::shmSem;

class masterThread: public commonThread {
	public:
	
		masterThread() {
		
		}
	private:
	
};

class slaveThread: public commonThread {
	public:
		
		slaveThread() {
		
		}
	private:
	
};

int main (int argc, char *argv[]) {
    char param1[] = "./workerThread";
    char param2[] = "0";
    char *paramList[4];
    timeval tim;
    double beginTime, endTime;
    pid_t workerPIDs[9] = {0,0,0,0,0,0,0,0,0};
    pid_t returnPIDs[9];
    pid_t tmpPID;
    int returnStatus[9];
    int i;
    int threadCount = 6; //set to 6 to remove some redundant solutions
    if (argc < 2) {
        printf("Error - no file specified\nProper usage: squareSolver fileName\n");
        exit(0);
    } else {
        paramList[0] = param1;
        paramList[1] = param2;
        paramList[2] = argv[1];
        paramList[3] = NULL;
        gettimeofday(&tim, NULL);
        beginTime = tim.tv_sec + (tim.tv_usec / 1000000.0);
        for (i = 0; i < threadCount; i++) {
            tmpPID = fork();
            sprintf(paramList[1], "%1d", i);
            if ((int)(tmpPID) > 0) {
                workerPIDs[i] = tmpPID;
            } else {
                if (execvp("./workerThread", paramList) < 0) {
                    printf("Thread launch failed\n");
                    exit(1);
                }
            }
        }
    }
    for (i = 0; i < threadCount; i++) {
        returnPIDs[i] = wait(&returnStatus[i]);
    }
    gettimeofday(&tim, NULL);
    endTime = tim.tv_sec + (tim.tv_usec / 1000000.0);
    printf("Time elapsed: %f\n", endTime - beginTime);

    exit(1);
}
