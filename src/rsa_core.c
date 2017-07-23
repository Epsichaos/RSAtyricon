// RSA CORE FUNCTIONS
#include <stdio.h>
#include <stdlib.h>
#include <gmp.h>
#include <time.h>

int cipherRSA() {
    printf("         File Encryption\n");
    printf("--------------------------------------\n");

    FILE* publicFile = fopen("out/public.rsa", "r");
    FILE* clearFile = fopen("source/Clair.txt", "r");
    FILE* cipheredFile = fopen("out/cipherFile.txt", "w");
    if(publicFile == NULL||clearFile == NULL||cipheredFile == NULL) {
        printf("Error while opening one of the 3 files required in cipherRSA\n");
        return -1;
    }

    // numbers of public key for encryption
    mpz_t n;
    mpz_t e;
    mpz_t m;
    mpz_t c;

    // buffer and caracters for the ciphering
    char buffer[128];
    int i = 0;
    char caract;

    // initialisation
    mpz_init2(n, 2048);
    mpz_init2(e, 2048);
    mpz_init2(m, 2048);
    mpz_init2(c, 2048);

    // allocation : we import n and e from the file where the public key is stored (i.e. public.rsa)
    mpz_inp_str(n,publicFile,16);
	mpz_inp_str(e,publicFile,16);

    printf("-> (n,e) has been imported from public.rsa\n\n");

    do {
        caract = fgetc(clearFile);
        if(caract != '\0' && caract != '\n') {
            buffer[i%128] = caract;
            if(i%128 == 126) {
                buffer[127]='\0';
                mpz_set_str(m, buffer, 62);
                mpz_powm(c,m,e,n);
                mpz_out_str(cipheredFile, 62,c);
                fputc('\n', cipheredFile);
            }
        }
        else {
            if(i%127 != 0) {
                buffer[i%128] = '\0';
            }
            mpz_set_str(m, buffer, 62);
            mpz_powm(c,m,e,n);
            mpz_out_str(cipheredFile, 62,c);
            fputc('\n', cipheredFile);
        }
        i++;
    } while(caract != '\0' && caract != '\n');
    printf("-> End of encryption. %d caracters have been encrypted in cipherFile.txt\n", i);
    printf("--------------------------------------\n");

    // clear memory
    mpz_clear(n);
    mpz_clear(e);
    mpz_clear(m);
    mpz_clear(c);

    // close files
    fclose(publicFile);
    fclose(clearFile);
    fclose(cipheredFile);

    return 0;
}

int decipherRSA() {
    printf("         File Decryption\n");
    printf("--------------------------------------\n");

    FILE* privateFile = fopen("out/prive.rsa", "r");
    FILE* cipheredFile = fopen("out/cipherFile.txt", "r");
    FILE* decipheredFile = fopen("out/decipheredFile.txt", "w");
    if(privateFile == NULL||cipheredFile == NULL||decipheredFile == NULL) {
        printf("Error while opening one of the 3 files required in decipherRSA\n");
        return -1;
    }

    // numbers of private key for decryption
    mpz_t n;
    mpz_t p;
    mpz_t q;
    mpz_t d;
    mpz_t c;
    mpz_t m;

    int i = 0;
    char buffer[500];
    char caract;

    // initialisation
    mpz_init2(n, 2048);
    mpz_init2(p, 2048);
    mpz_init2(q, 2048);
    mpz_init2(d, 2048);
    mpz_init2(c, 2048);
    mpz_init2(m, 2048);

    // allocation : we import p, q and d from the file where the private key is stored (i.e. prive.rsa)
    mpz_inp_str(p,privateFile,16);
	mpz_inp_str(q,privateFile,16);
    mpz_inp_str(d,privateFile,16);

    printf("-> (p,q,d) has been imported from prive.rsa\n\n");

    mpz_mul(n, p, q);

    do {
        caract = fgetc(cipheredFile);
        if(caract != '\n') {
            buffer[i] = caract;
            i++;
        }
        else {
            buffer[i]='\0';
            mpz_set_str(c, buffer, 62);
            mpz_powm(m,c,d,n);
            mpz_out_str(decipheredFile, 62, m);
            i = 0;
        }
    } while(caract != EOF);

    printf("-> End of decryption. Message has been decrypted in decipheredFile.txt\n");
    printf("--------------------------------------\n");

    // clear memory
    mpz_clear(p);
    mpz_clear(q);
    mpz_clear(d);
    mpz_clear(c);
    mpz_clear(m);

    // close files
    fclose(privateFile);
    fclose(cipheredFile);
    fclose(decipheredFile);

    return 0;
}
