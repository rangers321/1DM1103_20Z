#include<stdio.h>
#include<stdlib.h>
#include<math.h>

void main(int argc, char **argv)
    {
        //Wczytywanie
        FILE *fin1;
        FILE *fin2;
        float tab1[100], tab2[100];
        float l1, l2, w, k;
        int i=0, j=0;

        fin1=fopen(argv[1], "r");
        fin2=fopen(argv[2], "r");
        
        for(i=0; i<8; i++)
            {
                fscanf(fin1, "%f", &l1);
                tab1[i]=l1;
            }    
            
        
        for(j=0; j<5; j++)
            {
                fscanf(fin2, "%f", &l2);
                tab2[j]=l2;
            }

        //Liczenie
        float a, b, c;
        a=(tab1[2]*tab2[2])+(tab1[3]*tab2[3]);
        b=(tab1[4]*tab2[2])+(tab1[5]*tab2[3]);
        c=(tab1[6]*tab2[2])+(tab1[7]*tab2[3]);
        printf("(%f) [%f %f %f]\n", tab2[4], a, b, c);
    }