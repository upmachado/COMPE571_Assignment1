#include <stdio.h>
#include <pthread.h>


#define NUM_THREADS 2
#define N 100000000


long double final_sum = 0;
pthread_mutex_t lock; // Mutex for synchronization


void* thread_function(void* arg) {
   long start = *(int*)arg;
   long local_sum = 0;


   for (long i = start; i < N; i += NUM_THREADS) {
       local_sum += i;
   }


   pthread_mutex_lock(&lock);
   final_sum += local_sum;
   pthread_mutex_unlock(&lock);


   pthread_exit(NULL);
}


int main() {
   clock_t start, end;
   start = clock();
   pthread_t threads[NUM_THREADS];
   int thread_args[NUM_THREADS];
   // Mutex is used for performing synchronization
   // If successful, the pthread_mutex_init() and pthread_mutex_destroy() functions return zero
   pthread_mutex_init(&lock, NULL);


   // Create threads
   for (int i = 0; i < NUM_THREADS; i++) {
       thread_args[i] = i;
       pthread_create(&threads[i], NULL, thread_function, &thread_args[i]);
   }


   // Wait for threads to finish
   for (int i = 0; i < NUM_THREADS; i++) {
       pthread_join(threads[i], NULL);
   }


   pthread_mutex_destroy(&lock);


   printf("Multithreading Sum: %Lf\n", final_sum);
   end = clock();
   double cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
   printf("Multithreading_func() took %f seconds to execute \n", cpu_time_used);
   return 0;
}
