#include "ex1.h"

void v_add_naive(double* x, double* y, double* z) {
    #pragma omp parallel
    {
        for(int i=0; i<ARRAY_SIZE; i++)
            z[i] = x[i] + y[i];
    }
}

// Adjacent Method
void v_add_optimized_adjacent(double* x, double* y, double* z) {
    // TODO: Implement this function
    // Do NOT use the `for` directive here!
		int THREAD_NUM = omp_get_num_threads();

		#pragma omp parallel
		{
				int thread_id = omp_get_thread_num();
				int step = THREAD_NUM;
				for (int i=thread_id; i<ARRAY_SIZE; i+=step) {
								z[i] = x[i] + y[i];
			 	}
		}
}

// Chunks Method
void v_add_optimized_chunks(double* x, double* y, double* z) {
    // TODO: Implement this function
    // Do NOT use the `for` directive here!
		int THREAD_NUM = omp_get_num_threads();
		#pragma omp parallel
		{
				int thread_id = omp_get_thread_num();
				int start = thread_id * THREAD_NUM;
				for (int i=start; i<THREAD_NUM; i++) {
						z[i] = x[i] + y[i];
				}
		}
		for (int i=THREAD_NUM * THREAD_NUM; i<ARRAY_SIZE; i++) {
				z[i] = x[i] + y[i];
		}
}
