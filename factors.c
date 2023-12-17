#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>



typedef struct {
    int factor1;
    int factor2;
} Factorization;

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

Factorization factorize(int num) {
    Factorization result = {0, 0};
    for (int i = 2; i <= sqrt(num); ++i) {
        if (num % i == 0) {
            result.factor1 = min(i, num / i);
            result.factor2 = max(i, num / i);
            return result;
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: factors <file>\n");
        exit(EXIT_FAILURE);
    }

    char *input_file = argv[1];
    FILE *file = fopen(input_file, "r");

    if (file == NULL) {
        printf("File not found\n");
        exit(EXIT_FAILURE);
    }

    char buffer[256];
    time_t start_time = time(NULL);

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        int num = atoi(buffer);
        Factorization factors = factorize(num);

        if (factors.factor1 != 0) {
            printf("%d=%d*%d\n", num, min(factors.factor1, factors.factor2), max(factors.factor1, factors.factor2));

        }

        if (time(NULL) - start_time > 5) {
            printf("Time limit exceeded\n");
            fclose(file);
            exit(EXIT_FAILURE);
        }
    }

    fclose(file);
    return EXIT_SUCCESS;
}
