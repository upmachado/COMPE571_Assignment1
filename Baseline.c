#include <stdio.h>
#include <time.h>

// Case 1: Baseline: This case implements the WORKLOAD in a sequential way. In this case,
// implement a C file that performs the WORKLOAD without any parallelism.

long long int N[3] = {100000000,1000000000,10000000000};

int main() {
    int main_iter=0;
    double average_execution_time;
    long double sum = 0;
    for(int N_iter=0;N_iter<3;N_iter++){
        while(main_iter<20){
        //Starting clock
            clock_t start, end;
            double execution_time[20];
            start = clock();

            sum=0;
            //Do Work
            for (long double i = 1; i <= N[N_iter]; i++) {
                sum += i;
            }

            //End Clock
            end = clock();
            execution_time[main_iter] = ((double)(end - start))/CLOCKS_PER_SEC;
            average_execution_time+=execution_time[main_iter];
            main_iter++;
        }
        printf("Sum from 1 to [%lld] is: [%Lf]\n", N[N_iter], sum);
        printf("Average execution time of in 20 trials [%d] sum is [%f]\n",(N_iter+1), (average_execution_time/20));
        average_execution_time=0;
        main_iter=0;
    }
    return 0;
}
