#include "ex2.h"

double dotp_naive(double* x, double* y, int arr_size) {
    double global_sum = 0.0;
    for (int i = 0; i < arr_size; i++)
        global_sum += x[i] * y[i];
    return global_sum;
}

// Critical Keyword
double dotp_critical(double* x, double* y, int arr_size) {
    double global_sum = 0.0;
    // TODO: Implement this function
    // Use the critical keyword here!
		#pragma omp parallel for
		for (int i=0; i< arr_size; i++) {
				#pragma omp critical
				//printf("thread_id = %d, line: %d\n", omp_get_thread_num(), __LINE__);
				{ 
						global_sum += x[i] * y[i];
						//printf("thread_id = %d, line: %d\n", omp_get_thread_num(), __LINE__);
				}
		}
    return global_sum;
}

// Reduction Keyword
double dotp_reduction(double* x, double* y, int arr_size) {
    double global_sum = 0.0;
    // TODO: Implement this function
    // Use the reduction keyword here!
		#pragma omp parallel for reduction(+: global_sum)
		for (int i=0; i<arr_size; i++) {
				global_sum = global_sum + x[i] * y[i];
		}
    return global_sum;
}

// Manual Reduction
double dotp_manual_reduction(double* x, double* y, int arr_size) {
    double global_sum = 0.0;
    // TODO: Implement this function
    // Do NOT use the `reduction` directive here!
		int NUM_THREAD = omp_get_num_threads();
		int TWO_POWER[10] = {
			0, 2, 4, 8, 16, 32, 64, 128, 256, 512
		};
		for (int i=0; i<10; i++) {
				if (NUM_THREAD < TWO_POWER[i]) NUM_THREAD = TWO_POWER[i];
		}
		double sum[NUM_THREAD];
		// for(int i=0; i<NUM_THREAD; i++) printf("%lf, %d\n", sum[i], __LINE__);
		#pragma omp parallel for
		for (int i=0; i<arr_size; i++ ) {
				int THREAD_IDX = omp_get_thread_num();
				sum[THREAD_IDX] = x[i] * y[i];
		}
		for (int i=1; i<NUM_THREAD; i*=2) {
				for (int j=0; j<NUM_THREAD; j+=i) {
						sum[j] = sum[j] + sum[i+j];
				}
		}
		global_sum = sum[0];
    return global_sum;
}
