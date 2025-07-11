#include <stdio.h>

#define SIZE 50

struct Block {
    int allocated;
};

struct Block memBlock[SIZE];

int findFreeBlock() {
    for (int i = 0; i < SIZE; i++) {
        if (memBlock[i].allocated == 0)
            return i;
    }
    return -1;
}

void indexedAllocation() {
    int length;
    char choice;

    do {
        int indexBlock;
        int dataBlocks[SIZE];
        int allocated = 0;

        printf("Enter file length: ");
        scanf("%d", &length);

        if (length <= 0 || length >= SIZE) {
            printf("Invalid length.\n");
            continue;
        }

        indexBlock = findFreeBlock();
        if (indexBlock == -1) {
            printf("No free block for index.\n");
            continue;
        }

        memBlock[indexBlock].allocated = 1;

        for (int i = 0; i < length; i++) {
            int block = findFreeBlock();
            if (block == -1) {
                printf("Not enough blocks. Allocation failed.\n");
                for (int j = 0; j < allocated; j++) {
                    memBlock[dataBlocks[j]].allocated = 0;
                }
                memBlock[indexBlock].allocated = 0;
                break;
            }
            memBlock[block].allocated = 1;
            dataBlocks[i] = block;
            allocated++;
        }

        if (allocated == length) {
            printf("File allocated (Indexed):\n");
            printf("Index block: %d\n", indexBlock);
            printf("Points to blocks: ");
            for (int i = 0; i < length; i++) {
                printf("%d ", dataBlocks[i]);
            }
            printf("\n");
        }

        printf("Allocate another file? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');
}

int main() {
    indexedAllocation();
    return 0;
}

