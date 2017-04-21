#include <gmp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void S_and_M(mpz_t a,mpz_t n,mpz_t h, mpz_t r)
{
    char * bin = mpz_get_str(NULL,2,h);
    int i;
    mpz_set(r,a);
    for(i = 1; i < strlen(bin);i++)
    {
		mpz_mul(r,r,r);
		mpz_mod(r,r,n);
			if(bin[i] == '1')
			{
			mpz_mul(r,r,a);
			mpz_mod(r,r,n);
			}
	}
}

int main()
{
        mpz_t n;
        mpz_init(n);
        mpz_t rep;
        mpz_init(rep);
        printf("Choisir votre entier à tester : ");
        gmp_scanf("%Zd", &n);
        printf("Choisir le nombre de répétitions souhaité : ");
        gmp_scanf("%Zd", &rep);
        mpz_clear(n);
        mpz_clear(rep);
        return 0;
}
