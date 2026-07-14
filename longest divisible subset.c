#include<stdio.h>
#include <stdlib.h>
int compare(const void* a, const void* b) {
    int num1 = *(const int*)a;
    int num2 = *(const int*)b;
    if (num1 < num2) return -1;
    if (num1 > num2) return 1;
    return 0;
}
int* largestDivisibleSubset(int* nums, int numsSize, int* returnSize) {
    if (numsSize == 0) {
        *returnSize = 0;
        return NULL;
    }
    qsort(nums, numsSize, sizeof(int), compare);
    int* dp = (int*)malloc(numsSize * sizeof(int));
    int* parent = (int*)malloc(numsSize * sizeof(int));

    int max_size = 1;
    int max_idx = 0;
    for (int i = 0; i < numsSize; i++) {
        dp[i] = 1;
        parent[i] = -1;
    }
    for (int i = 1; i < numsSize; i++) {
        for (int j = 0; j < i; j++) {
            // Check if it's divisible and if extending it yields a larger subset
            if (nums[i] % nums[j] == 0 && dp[j] + 1 > dp[i]) {
                dp[i] = dp[j] + 1;
                parent[i] = j;
            }
        }
        if (dp[i] > max_size) {
            max_size = dp[i];
            max_idx = i;
        }
    }
    *returnSize = max_size;
    int* result = (int*)malloc(max_size * sizeof(int));
    int curr = max_idx;
    for (int i = max_size - 1; i >= 0; i--) {
        result[i] = nums[curr];
        curr = parent[curr];
    }
    free(dp);
    free(parent);

    return result;
}
