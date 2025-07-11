#include <stdio.h>
#include <stdbool.h>

#define SIZE 50

struct Block {
    int allocated; // 0 = free, 1 = allocated
};

struct Block memBlock[SIZE];

int checkSequential(int start, int length) {
    if (start + length > SIZE) return 0;
    for (int i = start; i < start + length; i++) {
        if (memBlock[i].allocated == 1)
            return 0;
    }
    return 1;
}

void sequentialAllocation() {
    int start, length;
    char choice;

    do {
        printf("Enter start block: ");
        scanf("%d", &start);
        printf("Enter file length: ");
        scanf("%d", &length);

        if (!checkSequential(start, length)) {
            printf("Cannot allocate: Blocks already used or out of range.\n");
        } else {
            for (int i = start; i < start + length; i++) {
                memBlock[i].allocated = 1;
            }
            printf("File allocated (Sequential):\n");
            for (int i = start; i < start + length; i++) {
                printf("Block %d -> Allocated\n", i);
            }
        }

        printf("Allocate another file? (y/n): ");
        scanf(" %c", &choice);

    } while (choice == 'y' || choice == 'Y');
}

int main() {
    sequentialAllocation();
    return 0;
    
}
