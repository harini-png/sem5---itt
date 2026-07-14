include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int maximumGap(int* nums, int numsSize) {
    // If the array contains less than two elements, return 0
    if (numsSize < 2) {
        return 0;
    }

    // Step 1: Find the minimum and maximum values
    int min_val = nums[0];
    int max_val = nums[0];
    for (int i = 1; i < numsSize; i++) {
        if (nums[i] < min_val) min_val = nums[i];
        if (nums[i] > max_val) max_val = nums[i];
    }

    // If all elements are identical, the max gap is 0
    if (min_val == max_val) {
        return 0;
    }

    // Step 2: Calculate bucket size and the number of buckets
    int bucket_size = MAX(1, (max_val - min_val) / (numsSize - 1));
    int num_buckets = (max_val - min_val) / bucket_size + 1;

    // Step 3: Allocate arrays to store bucket properties
    int* bucket_min = (int*)malloc(num_buckets * sizeof(int));
    int* bucket_max = (int*)malloc(num_buckets * sizeof(int));
    int* bucket_has_element = (int*)calloc(num_buckets, sizeof(int));

    // Initialize bucket values
    for (int i = 0; i < num_buckets; i++) {
        bucket_min[i] = INT_MAX;
        bucket_max[i] = INT_MIN;
    }

    // Map each number from the input array into its respective bucket
    for (int i = 0; i < numsSize; i++) {
        int idx = (nums[i] - min_val) / bucket_size;
        bucket_min[idx] = MIN(bucket_min[idx], nums[i]);
        bucket_max[idx] = MAX(bucket_max[idx], nums[i]);
        bucket_has_element[idx] = 1;
    }

    // Step 4: Traverse buckets to find the maximum gap
    int max_gap = 0;
    int previous_max = min_val;

    for (int i = 0; i < num_buckets; i++) {
        // Skip empty buckets
        if (!bucket_has_element[i]) {
            continue;
        }
        // Gap is measured from current bucket min to previous bucket max
        max_gap = MAX(max_gap, bucket_min[i] - previous_max);
        previous_max = bucket_max[i];
    }

    // Free dynamically allocated memory
    free(bucket_min);
    free(bucket_max);
    free(bucket_has_element);

    return max_gap;
}
