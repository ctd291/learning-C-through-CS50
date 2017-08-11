/**
 * helpers.c
 *
 * Helper functions for Problem Set 3.
 */
 
#include <cs50.h>

#include "helpers.h"

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    /* This is the linear search method, very simple
    
    for(int i = 0; i < n; i++)
    {
        if (value == values[i])
        {
            return true;
        }
    }
    */
    
    // TODO: implement a searching algorithm
    // this is a binary search method, more complicated searches is O(logn)
    int min = 0, max = n, mid, i = n; 
    while (i > 0)
    {
        i /= 2;
        mid = (max + min)/2;
        if (value == values[mid])
            {
                return true;
            }
        else if (values[mid] > value)
        {
            max = mid;
            max--;
        }
        else if (values[mid] < value)
        {
            min = mid;
            min++;
        }
    }
    
    return false;
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    // TODO: implement a sorting algorithm
    
    // sorts in linear time, since the max number is 65536 that is the max array
    {
        // this initializes the entire array of 65536 to 0 since we are using it as an idex
        int sortingArray[65536] = {0};
        // starting at array[0], it takes the value and puts it in the index array. This loops for the entire length of the array 
        for (int i = 0, j = 0; i < n; i++)
        {
            j = values[i];
            //since we only care about the index number, if there is dublicates of a number it will just add to the index
            sortingArray[j]++;
        }
        // this cycles through the entire sorting array starting at 0 and ending at 65536
        // if the sorting index is greater then 1 it will assign that value to the start of the values[] array
        // after the assignment it will decrease the index by 1, so if there are dublicates it will acount fo them
        for (int i = 0, j = 0; j < n; i++)
        {
            while (sortingArray[i] > 0)
            {
                values[j] = i;
                j++;
                sortingArray[i]--;
            }
        }
    }
    
    return;
}
