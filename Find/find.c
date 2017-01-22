/**
 * find.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Prompts user for as many as MAX values until EOF is reached, 
 * then proceeds to search that "haystack" of values for given needle.
 *
 * Usage: ./find needle
 *
 * where needle is the value to find in a haystack of values
 */
       
#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

#include "helpers.h"

// Maximum amount of hay
const int MAX = 65536;

int main(int argc, string argv[])
{
    // Ensure proper usage
    if (argc != 2)
    {
        printf("Usage: ./find needle\n");
        return -1;
    }

    // Remember needle
    int needle = atoi(argv[1]);

    // Fill haystack
    int size;
    int haystack[MAX];
    for (size = 0; size < MAX; size++)
    {
        // Wait for hay until EOF (Control-D)
        printf("\nhaystack[%i] = ", size);
        int straw = GetInt();
        if (straw == INT_MAX)
        {
            break;
        }
     
        // Add hay to stack
        haystack[size] = straw;
    }
    printf("\n");

    // Sort the haystack
    sort(haystack, size);
    
    // Try to find needle in haystack
    if (search(needle, haystack, size))
    {
        printf("\nFound needle in haystack!\n\n");
        return 0;
    }
    else
    {
        printf("\nDidn't find needle in haystack.\n\n");
        return 1;
    }
}
