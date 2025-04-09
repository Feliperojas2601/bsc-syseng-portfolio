#include<stdio.h>
#include<pthread.h>
#include<math.h>
#include<stdlib.h>
#include<unistd.h>

#define number_pthreads 10 

double pi; 
double sum_pthreads[number_pthreads]; 
int i_pthreads[number_pthreads]; 

double calculate_sign(int iteration) {

	double sum_sign; 

	if (iteration % 2) {

		sum_sign = ((double) -1 / (2 * iteration + 1)) ;
	
    } else {

		sum_sign = ((double) 1 / (2 * iteration + 1));
	
    }

	return 4 * sum_sign; 

}

void* calculate_pi(void *number_thread) {

	int thread_iteration_cons = *(int *)number_thread;
	double sum_iteration = 0;
    int iteration = thread_iteration_cons;
	sum_pthreads[thread_iteration_cons] = calculate_sign(iteration);

	do {
	
		iteration += number_pthreads;
		sum_iteration = calculate_sign(iteration);
		sum_pthreads[thread_iteration_cons] += sum_iteration;
		
    }
    while (iteration < 50000);

	return NULL;

}


int main(){

	int error_pthread;
	pthread_t pthreads[number_pthreads];

	for(int i = 0; i < number_pthreads; i++) {

		i_pthreads[i] = i; 
		error_pthread = pthread_create(&(pthreads[i]), NULL, calculate_pi, (void*)&i_pthreads[i]);
		if (error_pthread != 0) {
			printf("Error creando thread \n");
			return -1;
		}

	}

	for(int j = 0; j < number_pthreads; j++) {

		pthread_join(pthreads[j], NULL);
	
    }


	for(int k = 0; k < number_pthreads; k++) {

        pi += sum_pthreads[k];

    }

  	printf("%f\n",pi);

  	return 0;

}
