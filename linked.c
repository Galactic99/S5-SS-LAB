#include <stdio.h>
#include <stdlib.h>

#define SIZE 50

struct Block {
    int allocated;
    int next;
};

struct Block memBlock[SIZE];

int findFreeBlock() {
    for (int i = 0; i < SIZE; i++) {
        if (memBlock[i].allocated == 0)
            return i;
    }
    return -1;
}

void linkedAllocation() {
    int length;
    char choice;
    
    do {
        int startBlock = -1, prevBlock = -1;

        printf("Enter file length: ");
        scanf("%d", &length);

        if (length <= 0 || length > SIZE) {
            printf("Invalid file length.\n");
            continue;
        }

        for (int i = 0; i < length; i++) {
            int block = findFreeBlock();
            if (block == -1) {
                printf("Disk full. Allocation failed.\n");
                int current = startBlock;
                while (current != -1) {
                    int next = memBlock[current].next;
                    memBlock[current].allocated = 0;
                    memBlock[current].next = -1;
                    current = next;
                }
                startBlock = -1;
                prevBlock = -1;
                break;
            }

            memBlock[block].allocated = 1;
            memBlock[block].next = -1;

            if (prevBlock != -1) {
                memBlock[prevBlock].next = block;
            } else {
                startBlock = block;
            }

            prevBlock = block;
        }

        if (startBlock != -1) {
            printf("File allocated (Linked):\n");
            int current = startBlock;
            while (current != -1) {
                printf("Block %d -> ", current);
                current = memBlock[current].next;
            }
            printf("NULL\n");
        }

        printf("Allocate another file? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');
}

int main() {
    linkedAllocation();
    return 0;
}

