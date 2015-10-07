#ifndef MILLER_H
#define MILLER_H

int millerRabinStep(mpz_t a, mpz_t n);
int millerRabin(mpz_t n);
void primeKeyGeneration(mpz_t p);

#endif
