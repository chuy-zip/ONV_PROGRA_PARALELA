// paralelo_runtime.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <omp.h>

omp_sched_t get_sched_type(const char* name) {
    if (strcmp(name, "static") == 0)
        return omp_sched_static;
    else if (strcmp(name, "dynamic") == 0)
        return omp_sched_dynamic;
    else if (strcmp(name, "guided") == 0)
        return omp_sched_guided;
    else if (strcmp(name, "auto") == 0)
        return omp_sched_auto;
    else
        return -1;
}

int main() {
    char* threads_env = getenv("OMP_NUM_THREADS");
    char* sched_env = getenv("OMP_SCHEDULE");
    int chunk_size = 1; // default
    omp_sched_t sched_type = -1;

    if (threads_env != NULL)
        printf("OMP_NUM_THREADS = %s\n", threads_env);
    else
        printf("OMP_NUM_THREADS not set\n");
    if (sched_env != NULL) {
        // Parse format: "static,2"
        char* copy = strdup(sched_env);  // Safe copy
        char* token = strtok(copy, ",");

        if (token != NULL) {
            sched_type = get_sched_type(token);

            char* chunk_str = strtok(NULL, ",");
            if (chunk_str != NULL)
                chunk_size = atoi(chunk_str);

            if (sched_type != -1) {
                omp_set_schedule(sched_type, chunk_size);
            }
        }

        free(copy);
    }

    int actual_chunk;
    omp_sched_t actual_type;
    omp_get_schedule(&actual_type, &actual_chunk);

    printf("OMP_SCHEDULE = %s\n", sched_env ? sched_env : "not set");
    printf("Runtime schedule used: ");
    switch (actual_type) {
        case omp_sched_static: printf("static"); break;
        case omp_sched_dynamic: printf("dynamic"); break;
        case omp_sched_guided: printf("guided"); break;
        case omp_sched_auto: printf("auto"); break;
        default: printf("unknown"); break;
    }
    printf(", chunk size: %d\n", actual_chunk);


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
