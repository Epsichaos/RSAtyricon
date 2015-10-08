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

    int i = 2;
    int result;
    mpz_t entier;
    mpz_init(entier);
    while(i<100) {
        mpz_set_ui(entier, i);
        result = millerRabin(entier);
        if(result == 1) {
            printf("i = %d est premier", i);
        }
        else {
            printf("i = %d est non premier", i);
        }
    }

//    keyGeneration();
//    cipherRSA();

//    decipherRSA();
    // temps
    tend=time(NULL);
    texec=difftime(tend,tbegin);

    printf("Temps d'exécution : %lf secondes ...\n", texec);
    return 0;
}
