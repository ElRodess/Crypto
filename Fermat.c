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

void testFermat(mpz_t n, mpz_t rep)
{
        gmp_randstate_t state;
        gmp_randinit_mt(state);
        gmp_randseed_ui(state, time(NULL));

        mpz_t i;
        mpz_init(i);
        mpz_set_si(i,1);

        mpz_t n2;
        mpz_init(n2);
        mpz_sub_ui(n2,n,1);

        mpz_t a;
        mpz_init(a);

        mpz_t r;
        mpz_init(r);

        mpz_t n3;
        mpz_init(n3);
        mpz_sub_ui(n3,n,3);

        while(mpz_cmp(i,rep)<=0 && mpz_cmp_si(n,2)!= 0  && mpz_cmp_si(n,3)!=0)
        {
                mpz_urandomm(a,state,n3);
                mpz_add_ui(a,a,2);
                S_and_M(a,n,n2,r);
                if(mpz_cmp_si(r,1)!=0)
                {
                        printf("Le nombre est composé \n");
                        return ;
                }
                mpz_add_ui(i,i,1);
        }

        printf("Le nombre est premier \n");
        mpz_clear(i);
        mpz_clear(n2);
        mpz_clear(a);
        mpz_clear(r);
        mpz_clear(n3);
        gmp_randclear(state);
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
		    testFermat(n,rep);
        mpz_clear(n);
        mpz_clear(rep);
        return 0;
}
