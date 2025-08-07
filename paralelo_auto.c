#include <stdio.h>
#include <time.h>
#include <omp.h>

#define N 1000

void process_iteration(int i) {
    
    usleep((i % 10) * 1000);
}

int main() {
    double start = omp_get_wtime();
    
    #pragma omp parallel for schedule(auto)
    for(int i = 0; i < N; i++) {
        process_iteration(i);
    }

    double end = omp_get_wtime();
    
    printf("Tiempo secuencial: %.4f segundos\n", end - start);
    return 0;
}