#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Global pointer to access array values inside the comparator functions
int* global_arr;

// Comparator for Odd Jumps: Sort by value ascending, then by index ascending
int compare_odd(const void* a, const void* b) {
    int idx1 = *(const int*)a;
    int idx2 = *(const int*)b;
    if (global_arr[idx1] != global_arr[idx2]) {
        return global_arr[idx1] - global_arr[idx2];
    }
    return idx1 - idx2;
}

// Comparator for Even Jumps: Sort by value descending, then by index ascending
int compare_even(const void* a, const void* b) {
    int idx1 = *(const int*)a;
    int idx2 = *(const int*)b;
    if (global_arr[idx1] != global_arr[idx2]) {
        return global_arr[idx2] - global_arr[idx1]; // Descending value
    }
    return idx1 - idx2; // Ascending index
}

// Helper function using a monotonic stack to find next valid jumps
void make_next_jumps(int* sorted_indices, int size, int* next_jumps) {
    int* stack = (int*)malloc(size * sizeof(int));
    int top = -1;

    for (int i = 0; i < size; i++) {
        int idx = sorted_indices[i];
        while (top >= 0 && stack[top] < idx) {
            next_jumps[stack[top]] = idx;
            top--;
        }
        stack[++top] = idx;
    }
    free(stack);
}

int oddEvenJumps(int* arr, int arrSize) {
    if (arrSize <= 1) return arrSize;

    global_arr = arr;

    // Allocate memory for tracking jump destinations
    int* next_odd = (int*)malloc(arrSize * sizeof(int));
    int* next_even = (int*)malloc(arrSize * sizeof(int));
    int* indices = (int*)malloc(arrSize * sizeof(int));

    for (int i = 0; i < arrSize; i++) {
        next_odd[i] = -1;
        next_even[i] = -1;
        indices[i] = i;
    }

    // Step 1: Compute next odd jumps using sorted indices + stack
    qsort(indices, arrSize, sizeof(int), compare_odd);
    make_next_jumps(indices, arrSize, next_odd);

    // Step 2: Compute next even jumps using sorted indices + stack
    for (int i = 0; i < arrSize; i++) indices[i] = i; // Reset indices
    qsort(indices, arrSize, sizeof(int), compare_even);
    make_next_jumps(indices, arrSize, next_even);

    // Step 3: DP processing from right to left
    bool* odd = (bool*)calloc(arrSize, sizeof(bool));
    bool* even = (bool*)calloc(arrSize, sizeof(bool));

    // Base Case: The final index is always a valid destination
    odd[arrSize - 1] = true;
    even[arrSize - 1] = true;
    int good_starting_indices = 1; // Count index arrSize-1

    for (int i = arrSize - 2; i >= 0; i--) {
        if (next_odd[i] != -1) {
            odd[i] = even[next_odd[i]];
        }
        if (next_even[i] != -1) {
            even[i] = odd[next_even[i]];
        }
        // Since the 1st jump is always an odd-numbered jump
        if (odd[i]) {
            good_starting_indices++;
        }
    }

    // Free all dynamically allocated memory
    free(next_odd);
    free(next_even);
    free(indices);
    free(odd);
    free(even);

    return good_starting_indices;
}
