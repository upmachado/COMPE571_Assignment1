#include <stdio.h>
#include <time.h>

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
    //Starting clock
    clock_t start, end;
    double execution_time;
    start = clock();

    //Get N from user
    int N;
    printf("Enter N: ");
    scanf("%d", &N);
    
    //Do Work
    int work = workLoad(N);

    //End Clock
    end = clock();
    execution_time = ((double)(end - start))/CLOCKS_PER_SEC;

    //Inform user
    printf("Sum from 1 to [%d] is: [%d]\n", N, work);
    printf("Time taken to execute in seconds : [%f]", execution_time);
    
    return 0;
    
}
