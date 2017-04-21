#include <gmp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void S_and_M(mpz_t a,mpz_t n,mpz_t h, mpz_t r)
{
    char * bin = mpz_get_str(NULL,2,h);                  //On passe l'expo de la base 10 en binaire
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
  mpz_set_ui(S_pow,1);
  while(mpz_cmp_si(s,i) > 0 )
  {
    mpz_mul_ui(S_pow,S_pow,2);
    i++;
  }
}

void Decomp(mpz_t x,mpz_t s,mpz_t t)
{
mpz_t y,S_pow;
mpz_init(y);
mpz_set_ui(y,0); 

mpz_init(S_pow);

while(mpz_cmp(y,x)!=0)
{
        mpz_set_ui(t,1);
    mpz_mul(y,S_pow,t);
        while(mpz_cmp(y,x) < 0)
        {
        mpz_add_ui(t,t,2);
        M2Pow(s,S_pow);
                mpz_mul(y,S_pow,t);
        }
        mpz_add_ui(s,s,1);
}

mpz_sub_ui(s,s,1);
mpz_clear(y);
mpz_clear(S_pow);
}

void Miller_Rabin(mpz_t n, mpz_t rep)
{
        if(mpz_get_ui(n) % 2 == 0)                                //Si N pair alors renvoyer composé sauf si N=2
        {
                if(mpz_cmp_ui(n,2) == 0)       
                        printf("Le nombre est premier \n");
        else
            printf("Le nombre est composé \n");
        return;
        }
        
        int i=1;
        mpz_t a,y,s,t,n1,n2,deux;
        
        gmp_randstate_t state;                //On initialise le rand avec time
        gmp_randinit_mt(state);
        gmp_randseed_ui(state, time(NULL)); 
  
        mpz_init(a);
                
        mpz_init(y);
  
        mpz_init(s);   
        mpz_set_ui(s,1);
        
        mpz_init(deux);   
        mpz_set_ui(deux,2);
       
        mpz_init(t);
  
        mpz_init(n1);
        mpz_sub_ui(n1,n,1);
        
        mpz_init(n2);
        mpz_sub_ui(n2,n,2);
        
        Decomp(n1,s,t);
        mpz_sub_ui(s,s,1);
        while(mpz_cmp_ui(rep,i)>=0)
        {
                mpz_urandomm(a,state,n1);
                mpz_add_ui(a,a,1);
                S_and_M(a,n,t,y);
                if(mpz_cmp_si(y,1)!=0 && mpz_cmp(y,n1)!=0)
                {
                        
                        for(int j=1;mpz_cmp_ui(s,j)>=0;j++)
                        {
                                mpz_set(n2,y);
                                S_and_M(y,n,deux,y);
                                if(mpz_cmp_si(y,1)==0)
                                {
                                        printf("Le nombre est composé\n");
                                        mpz_clear(a);
									    mpz_clear(y);
									    mpz_clear(s);
                                        mpz_clear(t);
									    mpz_clear(n1);
									    mpz_clear(n2);
									    mpz_clear(deux);
									    gmp_randclear(state);
                                        return;
                                }
                                if(mpz_cmp(y,n1)==0)
                                        break;
                        }
                        if(mpz_cmp(y,n1)!=0)
                        {
                              printf("Le nombre est composé \n");
                                      mpz_clear(a);
									  mpz_clear(y);
									  mpz_clear(s);
                                      mpz_clear(t);
									  mpz_clear(n1);
									  mpz_clear(n2);
									  mpz_clear(deux);
									  gmp_randclear(state);
						      return; 
                        }
                        
                }
                i++;
        }
        printf("Le nombre est premier \n");
        
        mpz_clear(a);
        mpz_clear(y);
        mpz_clear(s);
        mpz_clear(t);
        mpz_clear(n1);
        mpz_clear(n2);
        mpz_clear(deux);
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
        Miller_Rabin(n,rep);
        mpz_clear(n);
        mpz_clear(rep);
        return 0;
}
