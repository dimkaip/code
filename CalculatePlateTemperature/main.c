#include <stdio.h>
#include <stdlib.h>


/// Υπολογισμός θερμοκρασιών πλάκας

#define ROWS 10
#define COLS 20
#define TEMPERATURE_LEFT 1
#define TEMPERATURE_RIGHT 2
#define TEMPERATURE_UP 3
#define TEMPERATURE_DOWN 4

// MATRIXES

float m0[ROWS][COLS];
float m1[ROWS][COLS];

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

void print_m0()
{
    for(int i=0; i<ROWS; i++)
    {
        for(int j=0; j<COLS; j++)printf("%.2f ", m0[i][j]);
        printf("\n");
    }
}

int main()
{
    printf("αρχικοποίση της m0\n");
//αρχικοποίση της m0 με διόρθωση των γωνιακών.
    init_m0();
    print_m0();


    return 0;
}















