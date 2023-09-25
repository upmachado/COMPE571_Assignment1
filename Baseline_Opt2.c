#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	long double start_num = strtold(argv[1], NULL);
    long double end_num = strtold(argv[2], NULL);
	long double sum = 0;
	//printf("Start and End: [%Lf] [%Lf]\n", &argv[0],&argv[1]);
    for (long double i = start_num; i <= end_num; i++) {
    	sum += i;
    }
    printf("%Lf\n", sum);
    return 0;
}
