#include <stdio.h>

int main() {
    int i;
    int suma = 0;
    for (i = 0; i < 16; i++) {
        suma += i;
        printf("Thread %d, sparcial sum = %d\n", i, suma);
    }
    printf("Suma total: %d\n", suma);
    return 0;
}