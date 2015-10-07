// KEY FUNCTIONS
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>
#include <unistd.h>
#include "miller.h"

int keyGeneration() {

    gmp_randstate_t state;
	gmp_randinit_default(state);
	gmp_randseed_ui(state,time(NULL));

    // declaration of MPZ variables
    mpz_t p;
    mpz_t q;
    mpz_t n;
    mpz_t pMinusOne;
    mpz_t qMinusOne;
    mpz_t phi;
    mpz_t e;
    mpz_t pgcdEPhi;
    mpz_t d;

    // initialisation
    mpz_init2(p, 2048);
	mpz_init2(q, 2048);
	mpz_init2(n, 2048);
    mpz_init2(pMinusOne, 2048);
    mpz_init2(qMinusOne, 2048);
    mpz_init2(phi, 2048);
    mpz_init2(e, 2048);
    mpz_init2(pgcdEPhi, 2048);
    mpz_init2(d, 2048);

    FILE* privateFile=fopen("prive.rsa","w+");
	FILE* publicFile=fopen("public.rsa","w+");
    if(privateFile == NULL||publicFile == NULL) {
        printf("Error in opening private or public file ! \n");
        return -1;
    }
    primeKeyGeneration(p);
    gmp_printf("p = %Zd\n",p);
    sleep(2);
    primeKeyGeneration(q);
    gmp_printf("q = %Zd\n",q);

    // p & q are the 2 prime number to construct n
    // n = p * q
    mpz_mul(n,p,q);

    // define pMinusOne & qMinusOne
    mpz_sub_ui(pMinusOne,p,1);
    mpz_sub_ui(qMinusOne,q,1);

    // define phi = pMinusOne * qMinusOne
    mpz_mul(phi, pMinusOne, qMinusOne);

    // find e : pgcd(e, d) = 1
    mpz_urandomb(e,state,2048);
    mpz_gcd(pgcdEPhi,e,phi);
    while(mpz_cmpabs_ui(pgcdEPhi,1) != 0) {
        mpz_urandomb(e,state,2048);
        mpz_gcd(pgcdEPhi,e,phi);
    }

    // find d : ed = 1 mod(phi)
    mpz_invert(d,e,phi);

    // write on the private file
    mpz_out_str(privateFile,10,p);
    fputs("\n",privateFile);
    mpz_out_str(privateFile,10,q);
    fputs("\n",privateFile);
    mpz_out_str(privateFile,10,d);

    // write on the public file
    mpz_out_str(publicFile,10,n);
    fputs("\n",publicFile);
    mpz_out_str(publicFile,10,e);

    // clear the memory
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(n);
    mpz_clear(pMinusOne);
    mpz_clear(qMinusOne);
    mpz_clear(phi);
    mpz_clear(e);
    mpz_clear(pgcdEPhi);
    mpz_clear(d);

    // close the files
    fclose(privateFile);
    fclose(publicFile);

    return 0;
}
