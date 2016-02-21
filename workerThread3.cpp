/*****************************************************************************
 *                    workerThread
 *                    ------------
 * Author:        Joseph Julik
 * Last Revision: 06-26-2012
 * Version:       0.2
 * Description:
 *     A child process of squareSolver, used to solve square puzzles
*****************************************************************************/
#include <cstdio>
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

#define SWAP(a, b) a = a + b - (b = a)

class puzzlePiece {
    public:
        int sides[4];
        puzzlePiece() {
        }
        puzzlePiece(int a, int b, int c, int d) {
            sides[0] = a;
            sides[1] = b;
            sides[2] = c;
            sides[3] = d;
        }
};

int next(int v[], int n, int firstValue) {
    /* Find the largest i */
    int i = n - 2;
    while ((i >= 0) && (v[i] > v[i + 1])) {
        --i;
    }
    /* If i is smaller than 0, then there are no more permutations. */
    if (i < 0) {
        return 1;
    }
    /* Find the largest element after vi but not larger than vi */
    int k = n - 1;
    while (v[i] > v[k]) {
        --k;
    }
    SWAP(v[i], v[k]);
    /* Swap the last n - i elements. */
    int j;
    k = 0;
    for (j = i + 1; j < (n + i) / 2 + 1; ++j, ++k) {
        SWAP(v[j], v[n - k - 1]);
    }
    if(v[0] != firstValue) {
        return 1;
    }
    return 0;
}

int check(int a, int b) {
    int d = a - b;
    if ((d != 1) && (d != -1)) {
        return 0;
    }
    int c = a + b;
    if ((c != 13) && (c != 9) && (c != 5) && (c != 1)) {
        return 0;
    }
    return 1;
}

int cToi(int c) {
    return (c - 48);
}

int main(int argc, char *argv[]) {
    ifstream inputFile(argv[2], ios::in | ios::binary | ios::ate);
    puzzlePiece pieces[9];
    puzzlePiece *pieces_p[9];
    puzzlePiece *piecesShifted_p[9];
    int permutationArray[9];
    int fileSize;
    int threadNo = atoi(argv[1]);
    int c[9];
    int i, j; //for loop counters
    int tmp; //temporary int storage, for use in loops
    char *fileBlock;
    if (inputFile.is_open()) {
        fileSize = (int) inputFile.tellg();
        fileBlock = new char[fileSize];
        inputFile.seekg(0, ios::beg);
        inputFile.read(fileBlock, fileSize);
        inputFile.close();
        for (i = 0; i < 9; i++) {
            tmp = i * 5;
            pieces[i] = puzzlePiece(cToi(fileBlock[tmp]), cToi(fileBlock[tmp + 1]), cToi(fileBlock[tmp + 2]), cToi(fileBlock[tmp + 3]));
            pieces_p[i] = &pieces[i];
        }
        delete fileBlock;
    } else {
        printf("Failed to open file: %s\n", argv[2]);
        exit(0);
    }
    //permutationArray represents the current state of the puzzle
    switch (threadNo) {
        case 0:
            permutationArray = {0,1,2,3,4,5,6,7,8};
            break;
        case 1:
            permutationArray = {1,0,2,3,4,5,6,7,8};
            break;
        case 2:
            permutationArray = {2,0,1,3,4,5,6,7,8};
            break;
        case 3:
            permutationArray = {3,0,1,2,4,5,6,7,8};
            break;
        case 4:
            permutationArray = {4,0,1,2,3,5,6,7,8};
            break;
        case 5:
            permutationArray = {5,0,1,2,3,4,6,7,8};
            break;
        default:
            printf("Unexpected case in worker thread\n");
            exit(0);
    }
    int tots = 0;
    while (1) {
        for (i = 0; i < 9; i++) {
            piecesShifted_p[i] = pieces_p[permutationArray[i]];
        }
        if ((permutationArray[2] > threadNo) && (permutationArray[6] > threadNo) && (permutationArray[8] > threadNo)) {
            for (c[0] = 0; c[0] < 4; c[0]++) { for (c[1] = 0; c[1] < 4; c[1]++) { 
            	if (check(piecesShifted_p[0]->sides[(1+c[0])&3], piecesShifted_p[1]->sides[(3+c[1])&3])) {
            		for (c[2] = 0; c[2] < 4; c[2]++) {
                		if (check(piecesShifted_p[1]->sides[(1+c[1])&3], piecesShifted_p[2]->sides[(3+c[2])&3])) {
                    			for (c[3] = 0; c[3] < 4; c[3]++) { 
                    				if (check(piecesShifted_p[0]->sides[(2+c[0])&3], piecesShifted_p[3]->sides[c[3]])) {
                    					for (c[4] = 0; c[4] < 4; c[4]++) { 
                    						 if (check(piecesShifted_p[3]->sides[(1+c[3])&3], piecesShifted_p[4]->sides[(3+c[4])&3]) &&
                    						 	check(piecesShifted_p[1]->sides[(2+c[1])&3], piecesShifted_p[4]->sides[c[4]])) {
                    							for (c[5] = 0; c[5] < 4; c[5]++) {
                        							if (check(piecesShifted_p[4]->sides[(1+c[4])&3], piecesShifted_p[5]->sides[(3+c[5])&3]) &&
                            								check(piecesShifted_p[2]->sides[(2+c[2])&3], piecesShifted_p[5]->sides[c[5]])) {
                            								for (c[6] = 0; c[6] < 4; c[6]++) { 
                            									if (check(piecesShifted_p[3]->sides[(2+c[3])&3], piecesShifted_p[6]->sides[c[6]])) {
                            										for (c[7] = 0; c[7] < 4; c[7]++) { 
                            											if (check(piecesShifted_p[4]->sides[(2+c[4])&3], piecesShifted_p[7]->sides[c[7]]) &&
                            												check(piecesShifted_p[6]->sides[(1+c[6])&3], piecesShifted_p[7]->sides[(3+c[7])&3])) {
                            												for (c[8] = 0; c[8] < 4; c[8]++) {
                                												if (check(piecesShifted_p[5]->sides[(2+c[5])&3], piecesShifted_p[8]->sides[c[8]]) &&
                                    													check(piecesShifted_p[7]->sides[(1+c[7])&3], piecesShifted_p[8]->sides[(3+c[8])&3])) {
                                                                                        tots++;
                                    													//printf("(%d,%d) (%d,%d) (%d,%d)\n(%d,%d) (%d,%d) (%d,%d)\n(%d,%d) (%d,%d) (%d,%d)\n\n", permutationArray[0], c[0], permutationArray[1], c[1], permutationArray[2], c[2], permutationArray[3], c[3], permutationArray[4], c[4], permutationArray[5], c[5], permutationArray[6], c[6], permutationArray[7], c[7], permutationArray[8], c[8]);
                                    												}
                                    											}
                                    										}
                                    									}
                                    								}
                                    							}
                                    						}
                                    					}
                                    				}
                                    			}
                                    		}
                                    	}
                                    }
                                }}}}}
        if (next(permutationArray, 9, threadNo)) { //next returns 1 if there are no more permutations
            break;
        }
    }
    //printf("%d\n", tots);
    return tots;
}
