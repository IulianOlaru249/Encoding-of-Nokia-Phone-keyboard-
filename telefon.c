#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>


typedef struct
{
    char gresit[100];
    char corect[100];
} Dex;

char *incripteaza( char c[], int taste[10][5])
{    
    //prevL verifica daca doua caractere sunt pe 
    //aceeasi tasta
    int prevL=INT_MAX, asciiC, mare, lng;
    char *rez1 = malloc ( 1024 * sizeof(char));
    strcpy(rez1, "");

    for(int l = 0; l < strlen(c); l++) //pt fiecare caracter din prop
    { 
        //obtinem codul ascii si presupunem
        //ca e litera mica
        asciiC = (int)c[l];
        mare = 0;

        if(asciiC >= 65 && asciiC <= 90 ) //daca este litera mare
        {
            mare=1;
            asciiC+=32; //cautam in matricea de taste ca si cum ar fi mica
        }

        if(asciiC == 32) //daca am gasit caracterul spatiu
        {
            strcat(rez1, "0");

            //daca e spatiu intre litere, nu conteaza
            //ca sunt pe acelasi buton
            prevL=INT_MAX; 
        }

        for( int i = 2; i <= 9; i++) //caut pe fiecare buton (linie)
            for( int j = 1; j <= 4; j++) //de cate ori a fost apasat (coloana)
            {
                if( taste[i][j] == asciiC)
                {
                    //daca doua litere consecutive au fost
                    //pe aceiasi linie din matrice inseamna
                    //ca sunt pe acelasi buton, deci le separam cu #.
                    //daca e litera mare, nu e nevoie de #
                    if(prevL == i && mare == 0) 
                    {
                        strcat(rez1, "#");
                    }

                    if(mare == 1)
                    {
                        strcat(rez1, "1");
                    }
        
                    for(int k = 1; k <= j; k++)
                    {    
                        lng = strlen(rez1);
                        rez1[lng] = i+ '0';
                        rez1[lng + 1] = '\0';
                    }
                    
                    prevL=i;  //resetam linia     
                }
            }
    }

    return rez1;
}


void decriptare( char a[], int taste[10][5] )
{    
    int seq, k, mare, ok=0;

    for( int l = 0; l < strlen(a); l++)
    {
        mare=0;

        //daca l-am gasit pe 1 si se afla inaintea unei secvente
        //secventa va fi litera mare
        if( (int)a[0] == (int)'1' && ok ==0 && l >= 1 )
        {
            mare = 1;
            ok = 1;
        }

        seq = 0; 

        // incepem cautarea secvntei de la caracterul urmator
        k = l + 1;

        while( (int)a[l] == (int)a[k])
        {
            seq++;
            k++;
        }

        l += seq;
        seq++;
        
        if( (int)a[l] == (int)'0' )
        {
            printf(" ");
        }
            
        //daca 1 preceda o secventa, inseamna ca secventa
        //reprezinta o litera mare
        if( (int)a[l-seq] == (int)'1')
        {
            mare = 1;
        }
        
        //daca nu este niciunul dintre caracterele speciale
        if( (int)a[l] != (int)'0' && (int)a[l] != (int)'#'
            && (int)a[l] != (int)'1')  
        {
            //afisam caracterul corespunzator codului ascii 
            //din matricea de taste 
            if( mare == 0 )
                printf("%c", taste[ (char)a[l] - '0' ][seq] );
            else
                printf("%c", taste[ (char)a[l] - '0' ][seq] - 32);
        }
    }

}


char *inlocuieste( char *s, int n, Dex *dex) 
{       
    char *rez3 = malloc( 1024 * sizeof(char) );
    
    //token va retine fiecare cuvant din propozitie
    char *token = strtok( s, " " );
    strcpy(rez3, ""); 

    int corect;
    while(token != NULL) //cat timp sunt cuvinte in propozitie
    {
        corect = 1;
        for( int i = 0; i < n; i++)
        {
            //daca am gasit un cuvant gresit
            if ( strcmp( token, dex[i].gresit ) == 0 ) 
            {
                //voi pune in vectorul rezultat versiunea corecta
                strcat( rez3, dex[i].corect );
                strcat( rez3, " " );
                corect = 0;
                break;
            }   
        }
            
        if( corect == 1) //daca nu am gasit cuvant gresit
        {
            //voi pune in vectorul rezultat cuvantul in sine
            strcat( rez3, token );
            strcat( rez3, " " );
        }   
            
        token = strtok (NULL, " "); //continua sa cauti
    } 
    
    rez3[ strlen(rez3) - 1] = '\0';
    return rez3;
}   

//imparte mesajul in secvente, avand 
//delimitator caracterul spatiu.
//se ignora #
void faNumere( char *s, int *k, long long *num)
{
    int cif;
    
    *k = 0;

    for( int i = 0; i < strlen(s); i++)
    {
        if( s[i] != '#' )
        {
            cif = s[i] - '0';
            if( cif == 0 && (s[i+1] - '0') != 0 
                    && i + 1 != strlen(s) )
            {
                *k += 1;
            }
            else
            {
                num[*k] = num[*k] * 10 + cif;
            }
        }
    }
}


long long cmmdc(long long a, long long b)
{
    long long c;

    while( b)
    {
        c = a % b;
        a = b;
        b = c;
    }

    return a;
}

int gasesteNumarMagic( char *s)
{
    int sum = 0;
    for( int i = 0; i < strlen(s); i++)
    {
        if( s[i] != '#')
        {
            sum += s[i] - '0';
        }
    }

    return sum % 9;
}


long long *grupeaza( char *s4, int *nrGrupe)
{
    long long *num4 = calloc( 1024, sizeof( long long));
    char *aux = malloc( strlen(s4) * sizeof(char) );

    int N, k = 0, scos = 0, lng;

    lng = strlen(s4);

    N = gasesteNumarMagic( s4); 

    //este nevoie de un vector auxiliar pentru a nu
    //strica mesajul initial in momentul in care 
    //scoatem caracterul #
    strcpy(aux, s4);

    //scoate toate caracterele # din mesaj
    for( int i = 0; i < lng; i++)
    {
        if( aux[i] == '#')
        {
            scos++;
            for( int j = i; j <= lng; j++)
            {
                aux[j] = aux[j+1];
            }
        }
    }
  
    lng -= scos; //update la lungime

    //conditii in care mesajul nu este perfect
    if( N == 0)
    {
        free( num4);
        return 0;
    }
    if( N > lng)
    {
        free( num4);
        return 0;
    }
    if( lng % N != 0)
    {
        free( num4);
        return 0;
    }

    for( int i = 0; i < lng; i++)
    {
        if( i % N == 0)
        {
            //daca s-a format o grupare cu N elemente
            //incepe sa construiesti o noua grupare
            //pe pozitia urmatoare din vector
            k++; 
        }
        //fiecare grupare este cosiderata un 
        //numar de forma long lon
        num4[k] = num4[k] * 10 + ( aux[i] - '0');
    }

    free( aux);
    *nrGrupe = k + 1;
    return num4;
}

//functia de comparare pt qsort
int comp (const void* p1, const void* p2)
{ 
    long long i1 = *(long long*) p1;
    long long i2 = *(long long*) p2;
    if (i1 > i2) 
    {
        return -1;
    }
    else
    {
        if (i1 == i2) 
            {
                return 0;
            }
            else 
            {
                return 1;
            }
    }
}

int main(void){
    
    //Matrice pt interpretarea datelor.
    //nr liniei = tasta care a fost apasata
    //nr coloanei = de cate ori a fost apasata
    int taste[10][5]={
        {0,   0,   0,   0,   0},
        {0,   0,   0,   0,   0},
        {0,  97,  98,  99,   0},
        {0, 100, 101, 102,   0},
        {0, 103, 104, 105,   0},
        {0, 106, 107, 108,   0},
        {0, 109, 110, 111,   0},
        {0, 112, 113, 114, 115},
        {0, 116, 117, 118,   0},
        {0, 119, 120, 121, 122},
    };

//CITIRE TASK 1
    char *t1 = malloc( 1024 * sizeof( char));
    fgets(t1, 1024, stdin);
    t1[ strlen(t1) - 1] = '\0';

//task1
    char *rez1 = incripteaza( t1, taste);

//CITIRE TASK 2
    char *t2 = malloc( 1024 * sizeof(char));
    fgets(t2, 1024, stdin);
    t2[ strlen(t2) - 1] = '\0';

//CITIRE TASK 3    
    char *t3 = malloc ( 1024 * sizeof(char) );
    fgets(t3, 1024, stdin);
    t3[ strlen(t3) - 1] = '\0';

//CITIRE DICTIONAR
    int n;

    scanf("%d", &n);
   
    Dex *dex = malloc( n * sizeof(Dex)); 
    
    for( int i = 0; i < n; i++)
    {
        scanf( "%s", dex[i].gresit);
        scanf( "%s", dex[i].corect);
    }

 
//task 3
    char *rez3 = inlocuieste(t3, n, dex); 
    char *rez3inc = incripteaza( rez3, taste);



//CITIRE TASK 4    
    char *t4;
    t4 = malloc( 1024 * sizeof(char) ); 
    getchar();
    fgets(t4, 1024, stdin);
    t4[ strlen(t4) - 1] = '\0';
    t4 = realloc ( t4, strlen(t4) * sizeof(char) );
    
    int  prim, nr, k, skip = 0;
    long long *num = calloc( 100 , sizeof(int)) ;
    
    char * t4inc = incripteaza(t4, taste);
    
    int nrGrupe = 0;
    char *t4b;
    t4b = malloc( 1024 * sizeof(char) );
    strcpy( t4b , t4inc);
    t4b = realloc( t4b, strlen(t4b) * sizeof(char) );

//task 4


    faNumere( t4inc, &k, num);

    //k este pozitia in sir, nu numarul de elemente
    nr = k + 1;
    if(num[0] == 0) //ignoram daca primul element e 0
    {
        skip = 1;
        nr--;
    }

    long long compMax = INT_MIN;
    int pozMax;

    for( int i = 0 + skip ; i <= k ; i++)
    {
        if(num[i] > compMax)
        {
            compMax = num[i];
            pozMax = i + 1;
        }
    }    
   
    
    prim = 1; 
    for(int i = 0 + skip; i < k; i++)
    {
        for(int j = i + 1; j <= k; j++)
        {
            if(cmmdc( num[i], num[j] ) != 1 )
            {
                prim = 0;
                break;
            }
        }
    }


      long long *grupe = grupeaza(t4b, &nrGrupe);
      qsort( grupe, nrGrupe, sizeof( long long), comp);

//AFISARE       
    //task1
    printf( "%s\n", rez1);
    free(t1);
    free(rez1);
  
    //task2
    decriptare( t2, taste);
    free(t2);
    printf("\n");


    //task3
    printf("%s\n", rez3inc);
    free(rez3inc);
    free(rez3);
    free(t3);
    free(dex);

  
    //task4
    printf("%d\n", nr);

    for(int i = 0 + skip; i <= k ; i++)
    {
        printf("%lld ", num[i]);
    }
    printf("\n");

    printf("%lld %d\n", compMax, pozMax);
    
    if(prim)
    {
        printf("1\n");
    }
    else
    {
        printf("0\n");
    }


    for( int i = 0; i < nrGrupe - 1; i++)
    {
        printf("%lld ", grupe[i]);
    }

    //daca nu s-a asit nicio grupa inseamna
    //ca funcia a returnat 0, deci mesajul
    //nu e perfect
    if( nrGrupe == 0) 
    {
        printf("0\n");
    }

    free(t4);
    free(t4inc);
    free(num);
    free(t4b);
    free(grupe);
}
