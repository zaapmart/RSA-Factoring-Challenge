#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <inttypes.h>
#include <time.h>

typedef struct {
    uint64_t factor1;
    uint64_t factor2;
} Factorization;

Factorization factorize(uint64_t num) {
    Factorization result = {0, 0};
    for (uint64_t i = 2; i <= sqrt(num); ++i) {
        if (num % i == 0) {
            result.factor1 = i;
            result.factor2 = num / i;
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
        uint64_t num = strtoull(buffer, NULL, 10);
        Factorization factors = factorize(num);

        if (factors.factor1 != 0) {
            printf("%" PRIu64 "=%" PRIu64 "*%" PRIu64 "\n", num, factors.factor1, factors.factor2);
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
