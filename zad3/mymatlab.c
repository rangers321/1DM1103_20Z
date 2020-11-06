#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>

struct macierz
{
    int r;
    int c;
    float tab[200][20];
};


void wczytaj(FILE *fin, struct macierz *m)
{
    fscanf(fin, "%d", &m->r);
    fscanf(fin, "%d", &m->c);

    for(int i = 0; i<(*m).r; i++)
        for(int j = 0; j<(*m).c; j++)
            {
                fscanf(fin, "%f", &(*m).tab[i][j]);
            }      
}

void wczytaj1(FILE *fin1, struct macierz *m1)
{
    fscanf(fin1, "%d", &m1->r);
    fscanf(fin1, "%d", &m1->c);

    for(int i = 0; i<(*m1).r; i++)
        for(int j = 0; j<(*m1).c; j++)
            {
                fscanf(fin1, "%f", &(*m1).tab[i][j]);
            }      
}

void wypisz(struct macierz m)
{
    int i, j;
    printf("[ ");
    for(i = 0; i<m.r; i++)
        {
            for(j=0; j<m.c; j++)
                {
                    printf("%5.2f ", m.tab[i][j]);
                }
            if(i < (m.r-1))
            printf("\n ");
        }
    printf("]\n");
}

void zapisz(struct macierz m)
{
    FILE *fin;
    fin=fopen("do_b.txt", "w+");
    fprintf(fin, "%d\n", m.r);
    fprintf(fin, "%d\n", m.c);

    for(int i = 0; i<m.r; i++)
        {    
            for(int j = 0; j<m.c; j++)
                {
                    fprintf(fin, "%6.2f", m.tab[i][j]);
                }
            fprintf(fin, "\n");
        }
    printf("Macierz zapisana do pliku do_b.txt\n");
}

void zapisz1(float m)
{
    FILE *fin;
    fin=fopen("do_b.txt", "w+");
    fprintf(fin, "%.2f\n", m);

    printf("Norma zapisana do pliku do_b.txt\n");
}

float norm(struct macierz m)
{
    float s=0;
    for(int i = 0; i<m.r; i++)
        {
            for(int j=0; j<m.c; j++)
                {
                    s+= m.tab[i][j] * m.tab[i][j];
                }
        }
    return sqrt(s);
}

struct macierz suma(struct macierz m, struct macierz m1)
{
    struct macierz sum;

    if(m.r == m1.r && m.c == m1.c)
        {
            struct macierz sum;
            sum.r = m.r;
            sum.c = m.c;
            for(int i = 0; i<m.r; i++)
                {
                    for(int j=0; j<m.c; j++)
                        {
                            sum.tab[i][j] = m.tab[i][j] + m1.tab[i][j];
                        }
                }
        }
        else
        printf("Nie można dodać macierzy - niewłaściwe wymiary!\n");
    return sum;
}

struct macierz subtract(struct macierz m, struct macierz m1)
{
    struct macierz sub;
    
    if(m.r == m1.r && m.c == m1.c)
        {
            sub.r = m.r;
            sub.c = m.c;
            for(int i = 0; i<m.r; i++)
                {
                    for(int j=0; j<m.c; j++)
                        {
                            sub.tab[i][j] = m.tab[i][j] - m1.tab[i][j];
                        }
                }
        }
        else
        printf("Nie można odjąć macierzy - niewłaściwe wymiary!\n");
    return sub;
}

struct macierz product(struct macierz m, struct macierz m1)
{
    struct macierz prod;
    int a = 0; 
    if(m.c == m1.r)
    {
        prod.r = m.r;
        prod.c = m1.c;

        for(int i = 0; i<m.r; i++)
        {
            for(int j=0; j<m1.c; j++)
            {
                for(a = 0; a<m.c; a++)
                {
                    prod.tab[i][j] = prod.tab[i][j] + (m.tab[i][a] * m1.tab[a][j]);
                }
            }
        }
    }
    else
    printf("Nie można wymnozyć macierzy - niewłaściwe wymiary!\n");
    
    return prod;
}

struct macierz skalar(struct macierz m, float a)
{
    struct macierz skal;
    skal.r = m.r;
    skal.c = m.c;

    for(int i = 0; i<m.r; i++)
        {
            for(int j=0; j<m.c; j++)
                {
                    skal.tab[i][j] = m.tab[i][j] * a;
                }
        }
return skal;
}


int main(int argc, char *argv[])
{
    struct macierz mac;
    struct macierz mac1;
    FILE *fin;
    FILE *fin1;

    if(strcmp(argv[1], "norm") == 0)
    {   
        fin = fopen(argv[2], "r");
        wczytaj(fin, &mac); 
        
        if(argc == 4)
        {
            zapisz1(norm(mac));
        }
        else
        {
            printf("Norma macierzy %s = %f\n", argv[2], norm(mac));
        }
        fclose(fin);
    }
    else if(strcmp(argv[1], "sum") == 0)
    {
        fin = fopen(argv[2], "r");
        fin1 = fopen(argv[3], "r");
        wczytaj(fin, &mac);
        wczytaj1(fin1, &mac1);
        struct macierz sum = suma(mac, mac1);
        
        if(argc == 5)
        {
            zapisz(sum);
        }
        else
        {
            printf("Suma macierzy %s i %s = \n", argv[2], argv[3]);
            wypisz(sum);
        }
        fclose(fin);
        fclose(fin1);
    }
    else if(strcmp(argv[1], "subtract") == 0)
    {
        fin = fopen(argv[2], "r");
        fin1 = fopen(argv[3], "r");
        wczytaj(fin, &mac);
        wczytaj1(fin1, &mac1);
        struct macierz sub = subtract(mac, mac1);

        if(argc == 5)
        {
            zapisz(sub);
        }
        else
        {
            printf("Różnica macierzy %s i %s = \n", argv[2], argv[3]);
            wypisz(sub);
        }
        fclose(fin);
        fclose(fin1);
    }
    else if(strcmp(argv[1], "prod") == 0)
    {
        fin = fopen(argv[2], "r");
        fin1 = fopen(argv[3], "r");
        wczytaj(fin, &mac);
        wczytaj1(fin1, &mac1);
        struct macierz prod = product(mac, mac1);
        if(argc == 5)
        {
            zapisz(prod);
        }
        else
        {
            printf("Macierz %s * macierz %s = \n", argv[2], argv[3]);
            wypisz(prod);
        }
        fclose(fin);
        fclose(fin1);
    }
    else if(strcmp(argv[1], "multiply") == 0)
    {
        float x = atof(argv[3]);
        fin = fopen(argv[2], "r");
        wczytaj(fin, &mac);
        struct macierz skal = skalar(mac, x);
        if(argc == 5)
        {
            zapisz(skal);
        }
        else
        {
            printf("Macierz %s * %.2f =\n", argv[2], x);
            wypisz(skal);
        }
        fclose(fin);
    }
    else
        printf("Nierozpoznany argument %s, oczekiwałem:\nsum\nsubtract\nprod\nmultiply\nnorm\n", argv[1]);
    
    return 0;
}