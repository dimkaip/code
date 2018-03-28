#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <float.h>

/// Υπολογισμός θερμοκρασιών πλάκας version 2

#define ROWS 10
#define COLS 20
#define TEMPERATURE_LEFT 1
#define TEMPERATURE_RIGHT 2
#define TEMPERATURE_UP 3
#define TEMPERATURE_DOWN 4
#define DIFF 10

// MATRIXES

float m0[ROWS][COLS];
float m1[ROWS][COLS];
int m2[ROWS][COLS];

//αρχικοποίση της m0
void init_m0()
{
    for(int i=0; i<ROWS; i++)
    {
        m0[i][0]=TEMPERATURE_LEFT;
        m0[i][COLS-1]=TEMPERATURE_RIGHT;
    }

    for(int j=0; j<COLS; j++)
    {
        m0[0][j]=TEMPERATURE_UP;
        m0[ROWS-1][j]=TEMPERATURE_DOWN;
    }
    //διόρθωση των γωνιακών στοιχείων στο μέσο όρο, επειδή ενδέχεται να έχουμε διαφορετικές θερμοκρασίες σε κάθε πλευρά.
    m0[0][0]=(float)(TEMPERATURE_LEFT+TEMPERATURE_UP)/2.0;
    m0[0][COLS-1]=(float)(TEMPERATURE_RIGHT+TEMPERATURE_UP)/2.0;
    m0[ROWS-1][0]=(float)(TEMPERATURE_LEFT+TEMPERATURE_DOWN)/2.0;
    m0[ROWS-1][COLS-1]=(float)(TEMPERATURE_RIGHT+TEMPERATURE_DOWN)/2.0;
}

void print_matrix_of_floats(float m[ROWS][COLS])
{
    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
            printf("%.2f ", m[i][j]);
        printf("\n");
    }
}

void print_matrix_of_integers(int m[ROWS][COLS])
{
    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)
            printf("%i ", m[i][j]);
        printf("\n");
    }
}


//Αντιγράφει ένα μητρώο σε ένα άλλο.
void copy(float from[ROWS][COLS],float to[ROWS][COLS])
{
    for(int i=0; i<ROWS; i++)
        for(int j=0; j<COLS; j++)
            to[i][j]=from[i][j];
}

//Αλλάζει το μητρώο σύμφωνα με τον τύπο χωρίς να πειράζει τις ακριανές τιμές.
void change(float m[ROWS][COLS])
{
    for(int i=1; i<ROWS-1; i++)
        for(int j=1; j<COLS-1; j++)
            m[i][j]=0.1*(m[i-1][j-1]+m[i-1][j]+m[i-1][j+1]+m[i][j-1]+2.0*m[i][j]+m[i][j+1]+m[i+1][j-1]+m[i+1][j]+m[i+1][j+1]);
}

void minmax(float m[ROWS][COLS], float*min, float* max)
{
    *min=FLT_MAX;
    *max=FLT_MIN;

    for(int i=1; i<ROWS; i++)
        for(int j=1; j<COLS; j++)
        {
            if(*min>m[i][j])*min=m[i][j];
            if(*max<m[i][j])*max=m[i][j];
        }
}

int return_class_of_int(float mij, int min, int max, float du)
{
    float f=mij-min;
    int i=f/du;
    if(i==10)i=DIFF-1;
    return i;
}

void normalize(float m[ROWS][COLS],int norm[ROWS][COLS], int onsize)
{
    float min,max;
    minmax(m,&min,&max);
    // διαφορική θερμοκρασία
    float du=(float)(max-min)/onsize;
    for(int i=1; i<ROWS; i++)
        for(int j=1; j<COLS; j++)
            norm[i][j]=return_class_of_int(m[i][j],min,max,du);
}

int main()
{
//αρχικοποίση της m0 με διόρθωση των γωνιακών.
    init_m0();
    printf("Εκτύπωση της m0\n");
    print_matrix_of_floats(m0);

//αντιγραφή στην m1
    copy(m0,m1);

//Αλλαγή της m1 σύμφωνα με τον τύπο
    change(m1);

    printf("Εκτύπωση της m1\n");
    print_matrix_of_floats(m1);

    printf("Εκτύπωση min και max του μητρώου m1\n");

    float min,max;
    minmax(m1,&min,&max);

    printf("min is:%.2f max is:%.2f \n", min,max);

    normalize(m1,m2,DIFF);

    printf("Εκτύπωση normalize of μητρώου m1=m2\n");
    print_matrix_of_integers(m2);

    return 0;
}














