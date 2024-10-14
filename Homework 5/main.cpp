#include <iostream>
#include <list>
#include <climits>

struct Block {
    int start;
    int size;
};

std::list<Block> freeList = { {0, 10}, {20, 30}, {60, 20} };

// Variables to track memory usage
int totalMemory = 60;          // Total memory size for the example
int usedMemory = 0;            // Memory currently in use
int allocationCount = 0;       // Number of successful allocations
int deallocationCount = 0;     // Number of successful deallocations
int allocationFailures = 0;    // Number of allocation failures
int totalFree = 60;            // Total free memory
int largestFreeBlock = 0;      // Size of the largest free block

// Enum for the different strategies
enum Strategy {
    FIRST_FIT,
    BEST_FIT,
    WORST_FIT
};

// Function to update the largest free block and total free memory
void updateFreeMemoryStats() {
    totalFree = 0;
    largestFreeBlock = 0;
    for (const auto& block : freeList) {
        totalFree += block.size;
        if (block.size > largestFreeBlock) {
            largestFreeBlock = block.size;
        }
    }
}

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
        usedMemory += requestSize;
        selectedBlock->start += requestSize;
        selectedBlock->size -= requestSize;
        allocationCount++;

        // If the block is fully used, remove it from the list
        if (selectedBlock->size == 0) {
            freeList.erase(selectedBlock);
        }

        // Update free memory statistics
        updateFreeMemoryStats();
    } else {
        std::cout << "No suitable block found for allocation of size " << requestSize << "\n";
        allocationFailures++;
    }
}

// Function for deallocating memory
void deallocateMemory(int start, int size) {
    // Just simulating a simple deallocation: adding the block back
    std::cout << "Deallocating " << size << " starting at " << start << "\n";
    freeList.push_back({start, size});
    usedMemory -= size;
    deallocationCount++;

    // Update free memory statistics
    updateFreeMemoryStats();
}

// Function to print the final memory statistics
void printMemoryStats() {
    float utilization = (static_cast<float>(usedMemory) / totalMemory) * 100;

    std::cout << "\n--- Results ---" << std::endl;
    std::cout << "Memory Used: " << utilization << "%" << std::endl;
    std::cout << "Free Memory: " << totalFree << std::endl;
    std::cout << "Largest Free Block: " << largestFreeBlock << std::endl;
    std::cout << "Total Allocations: " << allocationCount << std::endl;
    std::cout << "Total Deallocation: " << deallocationCount << std::endl;
    std::cout << "Allocation Failures: " << allocationFailures << std::endl;
}

// Main function to test the strategies and memory statistics
int main() {
    std::cout << "First Fit Strategy:\n";
    allocateMemory(15, FIRST_FIT);

    std::cout << "\nBest Fit Strategy:\n";
    allocateMemory(15, BEST_FIT);

    std::cout << "\nWorst Fit Strategy:\n";
    allocateMemory(15, WORST_FIT);

    // Simulate a deallocation
    deallocateMemory(15, 15);

    // Print the memory statistics at the end
    printMemoryStats();

    return 0;
}
