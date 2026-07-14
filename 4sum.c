#include <stdio.h>
#include <stdlib.h>

// Comparator function for qsort
int compare(const void *a, const void *b) {
    long long num1 = *(const int *)a;
    long long num2 = *(const int *)b;
    if (num1 < num2) return -1;
    if (num1 > num2) return 1;
    return 0;
}

int** fourSum(int* nums, int numsSize, int target, int* returnSize, int** returnColumnSizes) {
    // Allocate memory for the result list
    int capacity = 1000;
    int** result = (int**)malloc(capacity * sizeof(int*));
    *returnColumnSizes = (int*)malloc(capacity * sizeof(int));
    *returnSize = 0;

    if (numsSize < 4) return result;

    // Sort the array in ascending order
    qsort(nums, numsSize, sizeof(int), compare);

    for (int i = 0; i < numsSize - 3; i++) {
        // Skip duplicates for the first number
        if (i > 0 && nums[i] == nums[i - 1]) continue;
        
        for (int j = i + 1; j < numsSize - 2; j++) {
            // Skip duplicates for the second number
            if (j > i + 1 && nums[j] == nums[j - 1]) continue;

            int left = j + 1;
            int right = numsSize - 1;

            while (left < right) {
                // Use long long to prevent integer overflow for sum
                long long sum = (long long)nums[i] + nums[j] + nums[left] + nums[right];

                if (sum == target) {
                    // Allocate memory for the quadruplet
                    int* quad = (int*)malloc(4 * sizeof(int));
                    quad[0] = nums[i];
                    quad[1] = nums[j];
                    quad[2] = nums[left];
                    quad[3] = nums[right];

                    // Store it in the result array
                    if (*returnSize >= capacity) {
                        capacity *= 2;
                        result = (int**)realloc(result, capacity * sizeof(int*));
                        *returnColumnSizes = (int*)realloc(*returnColumnSizes, capacity * sizeof(int));
                    }

                    (*returnColumnSizes)[*returnSize] = 4;
                    result[*returnSize] = quad;
                    (*returnSize)++;

                    // Move pointers and skip duplicates for the third and fourth numbers
                    left++;
                    right--;
                    while (left < right && nums[left] == nums[left - 1]) left++;
                    while (left < right && nums[right] == nums[right + 1]) right--;
                } else if (sum < target) {
                    left++;
                } else {
                    right--;
                }
            }
        }
    }
    return result;
}
