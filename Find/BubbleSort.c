#include <stdio.h>
#include <cs50.h>
#include <string.h>

#DEFINE ARRAY_LENGTH 8

int main (void)
{
    int array [8] = {3, 5, 2, 7, 9, 1, 123, 0};
    int temp;
    
    for (int i = 0; i < 7; i++)
    {
        for (int n = 0; n < (7 - i); n++)
        {
            if (array[n] >= array[n+1])
            {
                temp = array[n+1];
                array[n+1] = array[n];
                array [n] = temp;
            }
        }
        for (int j = 0; j < 8; j++)
        {
            printf ("%d ", array[j]);
        }
        printf("\n");    
    }
    for (int i = 0; i < 8; i++)
    {
        printf ("%d ", array[i]);
    }
    printf("\n");
    
}
