#include<stdio.h>
#include<stdlib.h>
int compare(const void *a, const void *b) {
    return (*(int *)a - *(int *)b);
}

int threeSumClosest(int* nums, int n, int target) {
    qsort(nums, n, sizeof(int), compare);
    int sum = nums[0] + nums[1] + nums[2];
    int diff = abs(target - sum);

    for (int i = 0; i < n - 2 && diff != 0; i++) {
        int l = i + 1;
        int r = n - 1;
        while (l < r) {
            int tempSum = nums[i] + nums[l] + nums[r];
            int tempDiff = tempSum - target;

            if (abs(tempDiff) < diff) {
                diff = abs(tempDiff);
                sum = tempSum;
            }
            if (tempDiff == 0)
                break;
            else if (tempDiff > 0)
                r--;
            else
                l++;
        }
    }
    return sum;
}

