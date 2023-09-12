#include <stdio.h>

// Case 1: Baseline: This case implements the WORKLOAD in a sequential way. In this case,
// implement a C file that performs the WORKLOAD without any parallelism.

// Summation function
int workLoad(int N) {
    int sum = 0;
    for (int i = 1; i <= N; i++) {
        sum += i;
    }
    return sum;
}

int main() {
    int N;
    
    printf("Enter N: ");
    scanf("%d", &N);
    
    int work = workLoad(N);
    
    printf("Sum from 1 to [%d] is: [%d]\n", N, work);
    
    return 0;
}