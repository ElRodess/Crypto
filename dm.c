#include <gmp.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

void S_and_M(mpz_t a,mpz_t n,mpz_t h, mpz_t r)
{
    char * bin = mpz_get_str(NULL,2,h);  //On passe l'expo de la base 10 en binaire
    int i;                               // et on l'enregistre dans bin
    mpz_set(r,a); // on initialise le resultat à a
    for(i = 1; i < strlen(bin);i++) // pour tout les bits de bin
    {                              // on applique l'algo donné
		mpz_mul(r,r,r);
		mpz_mod(r,r,n);
		if(bin[i] == '1')
		{
			mpz_mul(r,r,a);
			mpz_mod(r,r,n);
		}
	}
}

void M2Pow(mpz_t s,mpz_t S_pow) // Fonction qui rentre 2^s dans S_pow
{
  int i = 0;
  mpz_set_ui(S_pow,1); // on initialise S_pow à 2^0
  while(mpz_cmp_si(s,i) > 0 ) // On multiplie S_pow par 2 tant que i < s
  {
    mpz_mul_ui(S_pow,S_pow,2);
    i++;
  }
}

void Decomp(mpz_t x,mpz_t s,mpz_t t) // Fonction qui décompose
{                                    // un entier x en 2^s * t
	mpz_t y,S_pow;
	mpz_init(y);
	mpz_set_ui(y,0);

	mpz_init(S_pow);

	while(mpz_cmp(y,x)!=0) // Tant que on trouve pas 2^s * t = x
	{
        mpz_set_ui(t,1); //On recommence avec t = 1
        mpz_mul(y,S_pow,t);// y = 2^s * t (on test les valeurs)
        while(mpz_cmp(y,x) < 0)// On arrette de tester quand 2^s * t > x
        {                      //
			mpz_add_ui(t,t,2); // t est impair donc on l'incremente de 2 en 2
			M2Pow(s,S_pow);
			mpz_mul(y,S_pow,t);
        }
        mpz_add_ui(s,s,1); // on test avec la puissante de 2 suivante
	}

	mpz_sub_ui(s,s,1);
	mpz_clear(y);
	mpz_clear(S_pow);
}

void testFermat(mpz_t n, mpz_t rep)
{
	gmp_randstate_t state; 	//On initialise le rand avec time
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
			mpz_clear(i);mpz_clear(n2);
			mpz_clear(a);mpz_clear(r);
			mpz_clear(n3);gmp_randclear(state);
			return ;
		}
		mpz_add_ui(i,i,1);
	}

	printf("Le nombre est premier \n");
	mpz_clear(i);mpz_clear(n2);
	mpz_clear(a);mpz_clear(r);
	mpz_clear(n3);gmp_randclear(state);
}

void Miller_Rabin(mpz_t n, mpz_t rep)
{
	if(mpz_get_ui(n) % 2 == 0)   //Si N pair alors renvoyer composé sauf si N=2
	{
		if(mpz_cmp_ui(n,2) == 0)
			printf("Le nombre est premier \n");
        else
            printf("Le nombre est composé \n");
        return;
	}

	int i=1;
	mpz_t a,y,s,t,n1,n2,deux;
	
	gmp_randstate_t state;     //On initialise le rand avec time
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
		if(mpz_cmp_si(y,1)!=0 && mpz_cmp(y,n1)!=0) //on regarde si y congrue a 1 mod n
		{											// ou a n-1 mod n = -1 mod n
			for(int j=1;mpz_cmp_ui(s,j)>=0;j++)
			{
				mpz_set(n2,y);
				S_and_M(y,n,deux,y);
				if(mpz_cmp_si(y,1)==0) //Si y congrue a 1 mod n alors il est composé
				{
					printf("Le nombre est composé\n");
					mpz_clear(a);mpz_clear(y);
					mpz_clear(s);mpz_clear(t);
					mpz_clear(n1);mpz_clear(n2);
					mpz_clear(deux);gmp_randclear(state);
					return;
				}
				if(mpz_cmp(y,n1)==0) //Si y congrue a -1 mod n on sort de la boucle
				break;
			}
			if(mpz_cmp(y,n1)!=0)  
			{
				printf("Le nombre est composé \n");
				mpz_clear(a);mpz_clear(y);
				mpz_clear(s);mpz_clear(t);
				mpz_clear(n1);mpz_clear(n2);
				mpz_clear(deux);gmp_randclear(state);
				return;
			}

		}
		i++;
	}
	printf("Le nombre est premier \n");
	
	mpz_clear(a);mpz_clear(y);
	mpz_clear(s);mpz_clear(t);
	mpz_clear(n1);mpz_clear(n2);
	mpz_clear(deux);gmp_randclear(state);
}

int main()
{
	int t=1;
	mpz_t n;
	mpz_init(n);
	mpz_t rep;
	mpz_init(rep);
	printf("########## Test de primalité ##########\n");
    while(t==1)
    {
        printf("\n");
        printf("Choisir votre entier à tester : ");
        gmp_scanf("%Zd", &n);
        if(mpz_cmp_ui(n,1)<=0)
        {	
			printf("\n Veuillez choisir un entier supérieur à 1 !");
		}
		else
		{
			printf("Choisir le nombre de répétitions souhaité : ");
			gmp_scanf("%Zd", &rep);
			printf("#########################################################\n");
			printf("Miller_Rabin : ");
			Miller_Rabin(n,rep);
			printf("\n");
			printf("Fermat : ");
			testFermat(n,rep);
			printf("#########################################################\n");
			printf("taper 1 pour tester un autre nombre !");
			scanf("%d",&t);
		}	
	}
	mpz_clear(n);	
	mpz_clear(rep);
	return 0;
}
