#include<stdio.h>
#include<pthread.h>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>
#include<omp.h>

#define number_pthreads 16
#define pad 8

double pi; 
double sum_pthreads[number_pthreads*pad]; 

void* calculate_pi(int number_thread) {

	int thread_iteration_cons = number_thread;
	int start = (1600000000 / number_pthreads) * thread_iteration_cons;
	int end = (1600000000 / number_pthreads) * (thread_iteration_cons + 1);
	int iteration = start; 

	do {
		sum_pthreads[thread_iteration_cons*pad] += ((double) 4 / ((2 * iteration) + 1));
		iteration++; 
		sum_pthreads[thread_iteration_cons*pad] += ((double) -4 / ((2 * iteration) + 1));
		iteration++;
    }
    while (iteration < end);

	return NULL;

}


int main(){

	for (int i = 0; i < number_pthreads*pad; i++) {

        sum_pthreads[i] = 0;

    }

    #pragma omp parallel num_threads(number_pthreads)
    {

        int id = omp_get_thread_num();
        calculate_pi(id);

    }

	for(int k = 0; k < number_pthreads*pad; k++) {

        pi += sum_pthreads[k];

    }

  	printf("%2.11f\n",pi);

  	return 0;

}