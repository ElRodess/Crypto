#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <gmp.h>

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

int main(int argc, char **argv)
{
    mpz_t a,n,h,r;
    mpz_init(a); 
    mpz_init(n);
    mpz_init(h);
    mpz_init(r);
    mpz_set_ui(a,4);
    mpz_set_ui(n,10);
    mpz_set_ui(h,9);
    S_and_M(a,n,h,r);
    gmp_printf("%Zd ^ %Zd mod %Zd = %Zd \n", &a,&h,&n,&r);
    mpz_clear(a);
    mpz_clear(n);
    mpz_clear(h);
    mpz_clear(r);
    return(0);
}
