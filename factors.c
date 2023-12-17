#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

typedef struct {
    mpz_t factor1;
    mpz_t factor2;
} Factorization;

void factorize(mpz_t num, Factorization *result) {
    mpz_t sqrt_num;
    mpz_init(sqrt_num);
    mpz_sqrt(sqrt_num, num);

    mpz_set_ui(result->factor1, 0);
    mpz_set_ui(result->factor2, 0);

    mpz_t i;
    mpz_init(i);

    for (mpz_set_ui(i, 2); mpz_cmp(i, sqrt_num) <= 0; mpz_add_ui(i, i, 1)) {
        if (mpz_divisible_p(num, i)) {
            mpz_set(result->factor1, i);
            mpz_divexact(result->factor2, num, i);
            return;
        }
    }

    mpz_clear(sqrt_num);
    mpz_clear(i);
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

    Factorization factors;
    mpz_init(factors.factor1);
    mpz_init(factors.factor2);

    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        mpz_t num;
        mpz_init_set_str(num, buffer, 10);

        factorize(num, &factors);

        if (mpz_cmp_ui(factors.factor1, 0) != 0) {
            gmp_printf("%Zd=%Zd*%Zd\n", num, factors.factor1, factors.factor2);
        }

        if (time(NULL) - start_time > 5) {
            printf("Time limit exceeded\n");
            mpz_clear(num);
            mpz_clear(factors.factor1);
            mpz_clear(factors.factor2);
            fclose(file);
            exit(EXIT_FAILURE);
        }

        mpz_clear(num);
    }

    mpz_clear(factors.factor1);
    mpz_clear(factors.factor2);
    fclose(file);
    return EXIT_SUCCESS;
}
