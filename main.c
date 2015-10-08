#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>
#include <unistd.h>
#include "key.h"
#include "miller.h"
#include "rsa_core.h"


int main(int argc, char* argv[]) {

    // temps start
    time_t tbegin,tend;
    double texec=0.;
    tbegin=time(NULL);

    printf("--------------------------------------------------------------\n");
    printf("|                     RSA IMPLEMENTATION                     |\n");
    printf("--------------------------------------------------------------\n");

/*
// test of function milleRabin
    int i = 2;
    int result;
    mpz_t entier;
    mpz_init(entier);
    while(i<100) {
        mpz_set_ui(entier, i);
        result = millerRabin(entier);
        if(result == 1) {
            printf("i = %d est premier\n", i);
        }
        else {
            printf("i = %d est non premier\n", i);
        }
        i++;
    }
*/
    keyGeneration();
    cipherRSA();

    decipherRSA();
    // temps
    tend=time(NULL);
    texec=difftime(tend,tbegin);

    printf("[Execution time] %d seconds\n", (int) texec);
    return 0;
}
