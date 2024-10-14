#include <iostream>
#include <list>
#include <climits>

struct Block {
    int start;
    int size;
};

std::list<Block> freeList = { {0, 10}, {20, 30}, {60, 20} };

// Enum for the different strategies
enum Strategy {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT
};

// Function for memory allocation based on the strategy
void allocateMemory(int requestSize, Strategy strategy) {
    auto selectedBlock = freeList.end();

    // Variables to track the best/worst fit size if needed
    int bestSize = INT_MAX;
    int worstSize = 0;

    for (auto it = freeList.begin(); it != freeList.end(); ++it) {
        // Check if the block is large enough to satisfy the request
        if (it->size >= requestSize) {
            // First Fit: Select the first block that satisfies the request
            if (strategy == FIRST_FIT) {
                selectedBlock = it;
                break;
            }
            // Best Fit: Select the smallest block that satisfies the request
            if (strategy == BEST_FIT && it->size < bestSize) {
                selectedBlock = it;
                bestSize = it->size;
            }
            // Worst Fit: Select the largest block that satisfies the request
            if (strategy == WORST_FIT && it->size > worstSize) {
                selectedBlock = it;
                worstSize = it->size;
            }
        }
    }

    // Allocate memory from the selected block, if any
    if (selectedBlock != freeList.end()) {
        std::cout << "Allocating " << requestSize << " from block starting at " << selectedBlock->start << "\n";
        selectedBlock->start += requestSize;
        selectedBlock->size -= requestSize;

        // If the block is fully used, remove it from the list
        if (selectedBlock->size == 0) {
            freeList.erase(selectedBlock);
        }
    } else {
        std::cout << "No suitable block found for allocation of size " << requestSize << "\n";
    }
}

// Main function to test the different strategies
int main() {
    std::cout << "First Fit Strategy:\n";
    allocateMemory(15, FIRST_FIT);

    std::cout << "\nBest Fit Strategy:\n";
    allocateMemory(15, BEST_FIT);

    std::cout << "\nWorst Fit Strategy:\n";
    allocateMemory(15, WORST_FIT);

    return 0;
}
