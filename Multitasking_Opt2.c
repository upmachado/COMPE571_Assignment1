#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>

int NUM_TASKS[3] = {2, 4, 8};
long long int N[3] = {100000000, 1000000000, 10000000000};
int main_iter = 0;
int N_iter;
int NUM_TASKS_iter;
double average_execution_time;
sem_t mutex;
sem_t work;

int main() {
    long double sum = 0;

    for (NUM_TASKS_iter = 0; NUM_TASKS_iter < 3; NUM_TASKS_iter++) {
        for (N_iter = 0; N_iter < 3; N_iter++) {
            while (main_iter < 20) {
                // Starting clock
                clock_t start, end;
                double execution_time[20];
                start = clock();

                // Dividing the work
                long double equal_work = N[N_iter] / NUM_TASKS[NUM_TASKS_iter];
                long double partial_sum = 0;
                sum = 0;

                // Initialize the semaphores

                // Create NUM_TASK child processes and do the work
                for (long double i = 0; i < NUM_TASKS[NUM_TASKS_iter]; i++) {
                    long double start_num = i * equal_work + 1;
                    long double end_num = (i + 1) * equal_work;
                    
                    // Construct the command string
                    char command[256]; // Adjust the size as needed
                    snprintf(command, sizeof(command), "./BaselinePara.o %Lf %Lf", start_num, end_num);

                    // Open the external program with the constructed command
                    FILE *fp = popen(command, "r");

                    // Read the output of the external program
                    long double child_partial_sum;
                    fscanf(fp, "%Lf", &child_partial_sum);
                    sum += child_partial_sum;

                    // Close the popen file pointer
                    pclose(fp);
                }

                // End Clock
                end = clock();
                execution_time[main_iter] = ((double)(end - start)) / CLOCKS_PER_SEC;
                average_execution_time += execution_time[main_iter];

                // Destroy semaphores (if needed)
                main_iter++;
            }

            printf("Sum from 1 to [%lld] with [%d] tasks is [%Lf]\n", N[N_iter], NUM_TASKS[NUM_TASKS_iter], sum);
            printf("Average Execution time 20 trials: [%f]\n", average_execution_time / 20);

            main_iter = 0;
            average_execution_time = 0;
        }
    }
    return 0;
}
