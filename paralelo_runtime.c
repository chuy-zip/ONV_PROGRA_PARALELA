// paralelo_runtime.c
#include <stdio.h>
#include <omp.h>

int main() {
    omp_set_num_threads(4);

    int i;
    int suma = 0;

    #pragma omp parallel for schedule(runtime) reduction(+:suma)
    for (i = 0; i < 16; i++) {
        suma += i;
        printf("Thread %d is running number %d\n", omp_get_thread_num(), i);
    }

    printf("Total: %d\n", suma);
    return 0;
}
