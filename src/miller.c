// MILLER FUNCTIONS
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>
#include <unistd.h>

#define K_ITERATIONS 20
#define POSSIBLE_PRIME 1
#define NOT_PRIME 0

// return 0 if n is not prime, and 1 if it is probably prime
int millerRabinStep(mpz_t a, mpz_t n) {
    int i = 1;
    int s = 0;

    mpz_t aPOWER;
    mpz_t d;
    mpz_t nMinusOne;

    mpz_init(nMinusOne);
    mpz_sub_ui(nMinusOne, n, 1);

    mpz_init_set(d, nMinusOne);
    while (mpz_even_p(d)) {
        mpz_fdiv_q_2exp(d, d, 1);
        s++;
    }

    mpz_init(aPOWER);
    mpz_powm(aPOWER, a, d, n);
    if (mpz_cmp_ui(aPOWER, 1) == 0)  {
        mpz_clear(aPOWER);
        mpz_clear(d);
        mpz_clear(nMinusOne);
        return POSSIBLE_PRIME;
    }
    for(i=0; i < s-1; i++) {
        if (mpz_cmp(aPOWER, nMinusOne) == 0) {
            mpz_clear(aPOWER);
            mpz_clear(d);
            mpz_clear(nMinusOne);
            return POSSIBLE_PRIME;
        }
        mpz_powm_ui (aPOWER, aPOWER, 2, n);
    }
    if (mpz_cmp(aPOWER, nMinusOne) == 0) {
        mpz_clear(aPOWER);
        mpz_clear(d);
        mpz_clear(nMinusOne);
        return POSSIBLE_PRIME;
    }
    mpz_clear(aPOWER);
    mpz_clear(d);
    mpz_clear(nMinusOne);
    return NOT_PRIME;
}


int millerRabin(mpz_t n) {
    // initialisation of random seed
    gmp_randstate_t rand_state;
    gmp_randinit_default(rand_state);
    gmp_randseed_ui (rand_state, time(NULL));

    mpz_t a;
    int i = 0;
    mpz_init(a);
    for(i=0; i<K_ITERATIONS; i++) {
        do {
            mpz_urandomm(a, rand_state, n);
        } while (mpz_sgn(a) == 0);
        if (millerRabinStep(a, n) == NOT_PRIME) {
            mpz_clear(a);
            return NOT_PRIME;
        }
    }
    mpz_clear(a);
    return POSSIBLE_PRIME;
}

void primeKeyGeneration(mpz_t p) {
    gmp_randstate_t state;
    gmp_randinit_default(state);
    gmp_randseed_ui(state,time(NULL));

    int isPrime = NOT_PRIME;
    while(isPrime == NOT_PRIME) {
        mpz_set_ui(p,0);
        mpz_urandomb(p,state,1024);
        isPrime = millerRabin(p);
    }
}
