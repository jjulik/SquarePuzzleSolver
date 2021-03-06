/*****************************************************************************
 *                    squareSolver
 *                    ------------
 * Author:        Joseph Julik
 * Last Revision: 06-26-2012
 * Version:       0.2
 * Description:
 *     Automatically solves square puzzles
*****************************************************************************/
#include <cstdio>
#include <sys/time.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

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
    int solutions = (WEXITSTATUS(returnStatus[0]) + returnStatus[1] + returnStatus[2] + returnStatus[3] + returnStatus[4] + returnStatus[5]) / 256;
    printf("%d", solutions);
    //printf(">>%d\n>>%d\n>>%d\n>>%d\n>>%d\n>>%d\n", (int)returnPIDs[0], (int)returnPIDs[1], (int)returnPIDs[2], (int)returnPIDs[3], (int)returnPIDs[4], (int)returnPIDs[5]);
    gettimeofday(&tim, NULL);
    endTime = tim.tv_sec + (tim.tv_usec / 1000000.0);
    //printf("Time elapsed: %f\n", endTime - beginTime);

    return solutions;
}
