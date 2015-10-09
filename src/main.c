#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>
#include <unistd.h>
#include "key.h"
#include "miller.h"
#include "rsa_core.h"

/* COMPILE with
gcc miller.c main.c key.c rsa_core.c -lgmp

pour openssl :
-L/usr/lib -lssl -lcrypto
*/

int main(int argc, char* argv[]) {

    // temps start
    time_t tbegin,tend;
    double texec=0.;
    tbegin=time(NULL);

    printf("--------------------------------------------------------------\n");
    printf("|                     RSA IMPLEMENTATION                     |\n");
    printf("--------------------------------------------------------------\n");


    keyGeneration();
    cipherRSA();
    decipherRSA();

    // temps
    tend=time(NULL);
    texec=difftime(tend,tbegin);

    printf("[Execution time] %d seconds\n", (int) texec);
    return 0;
}
