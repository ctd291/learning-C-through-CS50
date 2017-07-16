//pset1 water
// simple program to calculated water consumption through variables
// 

#include <cs50.h>
#include <stdio.h>

int min, bottles; 

int main(void)
{
    printf("I would like to tell you how much water you consume in the shower!\n");
    printf("Please supply me with a number:");
    min = bottles = get_int();
    bottles *= 12; 
    printf("If it takes you %i minutes to shower then you will consume %i bottles of water!\n", min, bottles);
}
