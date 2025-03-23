#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>

uint8_t smallPrimes[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97};
uint32_t millerRabinConstants[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

uint64_t mpow(unsigned __int128 base, uint64_t exponent, const uint64_t modulus){

	unsigned __int128 result = 1;

	while(exponent > 0){
    	if(exponent % 2 == 1){
        	result = (base * result) % modulus;
        	--exponent;
    	} else{
        	base = (base * base) % modulus;
        	exponent /= 2;
    	}
	}

	return result;

}


_Bool trialDivision(const uint64_t n) {

    for (uint8_t i = 0; i < sizeof(smallPrimes) / sizeof(smallPrimes[0]); ++i) {
        if (n % smallPrimes[i] == 0) {
            return 0;
        }
    }

    return 1;

}

_Bool fermat(const uint64_t n) {

    if (mpow(2, n - 1, n) != 1){
            return 0;
    }

    if (mpow(3, n - 1, n) != 1){
            return 0;
    }

    return 1;

}

_Bool millerRabin(const uint64_t n) {

    uint64_t d = n - 1;
    uint8_t s = 0;

    while (d % 2 == 0) {
        d /= 2;
        ++s;
    }

    for (uint8_t i = 0; i < sizeof(millerRabinConstants) / sizeof(millerRabinConstants[0]); ++i) {

        uint32_t a = millerRabinConstants[i];
        uint64_t x = mpow(a, d, n);
        uint64_t y = 0;

        for (uint8_t j = 0; j < s; ++j) {
            y = mpow(x, 2, n);
            if (y == 1 && x != 1 && x != n - 1) {
                    return 0;
            }
            x = y;
        }

        if (y != 1) {
            return 0;
        }

    }

    return 1;

}

_Bool test(const uint64_t n) {

    if (trialDivision(n)) {
        if (fermat(n)) {
            if (millerRabin(n)) {
                return 1;
            }
        }
    }

    return 0;

}

int main() {

    FILE *f = fopen("C:/primes.txt", "a");

    if (f == NULL) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    uint64_t input;

    printf("Enter an upper limit: ");
    scanf("%" PRIu64, &input);

    for (uint64_t i = 101; i <= input; i += 2) {
        if (test(i)) {
            fprintf(f, "%" PRIu64 "\n", i);
        }
    }

    fclose(f);
    return 0;

}
