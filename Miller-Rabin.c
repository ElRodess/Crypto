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

void M2Pow(mpz_t s,mpz_t S_pow)
{
  int i = 0;
  while(mpz_cmp(i,s) < 0 )
  {
    mpz_mul_ui(s,s,2);
    i++;
  }
}

void Decomp(mpz_t x,mpz_t s,mpz_t t)
{
mpz_t y; mpz_t S_pow;
mpz_init(y);mpz_init(S_pow);
mpz_set_ui(y,0);
while(mpz_cmp(x,y)!=0)
{
  mpz_add_ui(s,s,1);
  mpz_set_ui(t,1);
  mpz_mul(y,S_pow,t);
  while(mpz_cmp(x,y) > 0)
  {
    mpz_add_ui(t,t,2);
    M2Pow(s,S_pow);
    mpz_mul(y,S_pow,t);
  }
}
mpz_clear(y);mpz_clear(S_pow);
}

void Miller_Rabin(mpz_t n, mpz_t rep)
{
  mpz_t s;mpz_t t;mpz_t x;
  mpz_init(s);mpz_init(t);mpz_init(x);
  mpz_set_ui(s,1);mpz_set_ui(t,1);mpz_sub_ui(x,n,1);
  Decomp(x,s,t);
  gmp_printf("s = %Zd \n t= %Zd\n", &s,&t);
  mpz_clear(s);mpz_clear(t);mpz_clear(x);
}
int main()
{
        mpz_t n;
        mpz_init(n);
        mpz_t rep;
        mpz_init(rep);
        printf("Choisir votre entier à tester : ");
        gmp_scanf("%Zd", &n);
      /*  printf("Choisir le nombre de répétitions souhaité : ");
        gmp_scanf("%Zd", &rep); */
        Miller_Rabin(n,rep);
        mpz_clear(n);
        mpz_clear(rep);
        return 0;
}
