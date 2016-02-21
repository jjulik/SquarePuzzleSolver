/*****************************************************************************
 *                    workerThread
 *                    ------------
 * Author:        Joseph Julik
 * Last Revision: 03-11-2011
 * Version:       0.1
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
    private:
        int sides[4];
        int orientation; //values 0-3, indicates which side is up
    public:
        puzzlePiece() {
        }
        puzzlePiece(int a, int b, int c, int d) {
            sides[0] = a;
            sides[1] = b;
            sides[2] = c;
            sides[3] = d;
            orientation = 0;
        }
        int getLeft() {
            return sides[((3 + orientation) &3)];
        }
        int getRight() {
            return sides[((1 + orientation) &3)];
        }
        int getBottom() {
            return sides[((2 + orientation) &3)];
        }
        int getTop() {
            return sides[orientation];
        }
        int getOrientation() {
            return orientation;
        }
        void setOrientation(int o) {
            orientation = o;
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
    if ((c != 1) && (c != 5) && (c != 9) && (c != 13)) {
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
        case 6:
            permutationArray = {6,0,1,2,3,4,5,7,8};
            break;
        case 7:
            permutationArray = {7,0,1,2,3,4,5,6,8};
            break;
        case 8:
            permutationArray = {8,0,1,2,3,4,5,6,7};
            break;
        default:
            printf("Unexpected case in worker thread\n");
            exit(0);
    }
    while (1) {
        for (i = 0; i < 9; i++) {
            piecesShifted_p[i] = pieces_p[permutationArray[i]];
        }
        if ((permutationArray[2] > threadNo) && (permutationArray[6] > threadNo) && (permutationArray[8] > threadNo)) {
        for (c[0] = 0; c[0] < 4; c[0]++) {
            piecesShifted_p[0]->setOrientation(c[0]);
        for (c[1] = 0; c[1] < 4; c[1]++) {
            piecesShifted_p[1]->setOrientation(c[1]);
        for (c[2] = 0; c[2] < 4; c[2]++) {
            piecesShifted_p[2]->setOrientation(c[2]);
        for (c[3] = 0; c[3] < 4; c[3]++) {
            piecesShifted_p[3]->setOrientation(c[3]);
        for (c[4] = 0; c[4] < 4; c[4]++) {
            piecesShifted_p[4]->setOrientation(c[4]);
        for (c[5] = 0; c[5] < 4; c[5]++) {
            piecesShifted_p[5]->setOrientation(c[5]);
        for (c[6] = 0; c[6] < 4; c[6]++) {
            piecesShifted_p[6]->setOrientation(c[6]);
        for (c[7] = 0; c[7] < 4; c[7]++) {
            piecesShifted_p[7]->setOrientation(c[7]);
        for (c[8] = 0; c[8] < 4; c[8]++) {
            piecesShifted_p[8]->setOrientation(c[8]);
            if (
check(piecesShifted_p[0]->getRight(), piecesShifted_p[1]->getLeft()) &&
check(piecesShifted_p[1]->getRight(), piecesShifted_p[2]->getLeft()) &&
check(piecesShifted_p[3]->getRight(), piecesShifted_p[4]->getLeft()) &&
check(piecesShifted_p[4]->getRight(), piecesShifted_p[5]->getLeft()) &&
check(piecesShifted_p[6]->getRight(), piecesShifted_p[7]->getLeft()) &&
check(piecesShifted_p[7]->getRight(), piecesShifted_p[8]->getLeft()) &&
check(piecesShifted_p[0]->getBottom(), piecesShifted_p[3]->getTop()) &&
check(piecesShifted_p[1]->getBottom(), piecesShifted_p[4]->getTop()) &&
check(piecesShifted_p[2]->getBottom(), piecesShifted_p[5]->getTop()) &&
check(piecesShifted_p[3]->getBottom(), piecesShifted_p[6]->getTop()) &&
check(piecesShifted_p[4]->getBottom(), piecesShifted_p[7]->getTop()) &&
check(piecesShifted_p[5]->getBottom(), piecesShifted_p[8]->getTop())) {
                    printf("(%d,%d) (%d,%d) (%d,%d)\n(%d,%d) (%d,%d) (%d,%d)\n(%d,%d) (%d,%d) (%d,%d)\n\n", permutationArray[0], piecesShifted_p[0]->getOrientation(), permutationArray[1], piecesShifted_p[1]->getOrientation(), permutationArray[2], piecesShifted_p[2]->getOrientation(), permutationArray[3], piecesShifted_p[3]->getOrientation(), permutationArray[4], piecesShifted_p[4]->getOrientation(), permutationArray[5], piecesShifted_p[5]->getOrientation(), permutationArray[6], piecesShifted_p[6]->getOrientation(), permutationArray[7], piecesShifted_p[7]->getOrientation(), permutationArray[8], piecesShifted_p[8]->getOrientation());
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
        if (next(permutationArray, 9, threadNo)) { //next returns 1 if there are no more permutations
            break;
        }
    }
    return 1;
}
