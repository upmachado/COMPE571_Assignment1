#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/wait.h>


int NUM_TASKS[3] = {2,4,8};
long long int N[3] = {100000000,1000000000,10000000000};
int main_iter=0;
int N_iter;
int NUM_TASKS_iter;
double average_execution_time;
sem_t mutex;
sem_t work;


int main(){
    long double sum=0;
    for(NUM_TASKS_iter=0;NUM_TASKS_iter<3;NUM_TASKS_iter++){
        for(N_iter=0;N_iter<3;N_iter++){
            while(main_iter<20){
                // Starting clock
                clock_t start, end;
                double execution_time[20];
                start = clock();

                //Dividing the work
                long double equal_work = N[N_iter] / NUM_TASKS[NUM_TASKS_iter];
                long double partial_sum = 0;
                sum=0;

                //Pipe engage
                int fd[2];
                pipe(fd);

                // Initialize the semaphore
                // Initialize the semaphores
                if (sem_init(&mutex, NUM_TASKS[NUM_TASKS_iter], 1) != 0) {
                    perror("sem_init");
                    exit(1);
                }
                if (sem_init(&work, 1, 1) != 0) {
                    perror("sem_init");
                    exit(1);
                }


                // Create NUM_TASK child processes and doing the work
                for (long double i = 0; i < NUM_TASKS[NUM_TASKS_iter]; i++) {
                    long double start_num = i * equal_work + 1;
                    long double end_num = (i + 1) * equal_work;

                    if(fork()==0){
                        sem_wait(&mutex);
                        for(long double j = start_num;j<=end_num;j++){
                            partial_sum=partial_sum+j;
                        }
                        close(fd[0]);
                        write(fd[1],&partial_sum,sizeof(partial_sum));
                        sem_post(&mutex);  
                        exit(0);
                    }
                }

                //Waiting for Children
                while(wait(NULL) > 0);
                //Final Summation
                for (long double i = 0; i < NUM_TASKS[NUM_TASKS_iter]; i++) {
                    close(fd[1]);
                    long double child_partial_sum;
                    read(fd[0], &child_partial_sum, sizeof(child_partial_sum));
                    sum += child_partial_sum;
                }

                // End Clock
                end = clock();
                execution_time[main_iter] = ((double)(end - start)) / CLOCKS_PER_SEC;
                average_execution_time+=execution_time[main_iter];

                sem_destroy(&mutex);
                sem_destroy(&work);
                main_iter++;
            }
            printf("Sum from 1 to [%lld] with [%d] tasks is [%Lf]\n", N[N_iter], NUM_TASKS[NUM_TASKS_iter],sum);
            printf("Average Execution time 20 trials: [%f]\n", average_execution_time/20);
            main_iter=0;
            average_execution_time=0;
        }
    }
    return 0;
}
