/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>
#include <stdio.h>
#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int sortedValues[], int n)
{
    bool valueFound = false;
    int max = n-1;
    int min = 0;
    
    while (valueFound == false)
    {
        int mid = ((min + max) / 2);
        
        if (value < sortedValues[mid])
        {
            max = mid;
        }
        else if (value > sortedValues[mid])
        {
            min = mid;
        }
        else if (value == sortedValues[mid])
        {
            valueFound = true;
        }
        if (min == mid)
        {
            if (value == sortedValues[mid] || value == sortedValues[max])
            {
                valueFound = true;
            }
            else
            {
                valueFound = false;
            }
            break;
        }
        
    }
    return valueFound;
}

// Use Bubble Sort to sort the array, with worst case runtime O(n^2).
void sort(int values[], int n)
{
    // Temporary int to store value when swapping.
    int temp;

    // Keep looping through array until all numbers are sorted.
    for (int i = 0; i < n; i++)
    {
        // Loop through the array and move larger numbers to top
        for (int j = 0; j < (n - 1 - i); j++)
        {
            if (values[j] >= values[j+1])
            {
                temp = values[j+1];
                values[j+1] = values[j];
                values [j] = temp;
            }
        }
    }

    return;
}