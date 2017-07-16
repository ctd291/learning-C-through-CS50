// pset1 mario.c program
// build a pyramid with blocks, loops and user input

#include <cs50.h>
#include <stdio.h>

int hight = 0, space;

int main(void)
{
    printf("Give me a hight for a pyrimad:\n");
    // a loop to set up the pyrimad, it will reject number less the 0 and greater then 23
    do 
        {
            hight = get_int();
            if (hight < 0 || hight > 23)
            {
                printf("Invalid number, it needs to be between 0 and 23:\n");
            }
        }
    while(hight < 0 || hight > 23); // the bounderies of the pyrimad
    
    // this sets up what needs to be displayed for each row, every increase in i is a new row
    for (int i = 0; i < hight; i++)
        {
            // prints out how many blank spaces are needed per row
            for (space = hight - 1; space >= i; space--)
                {
                    printf(" ");
                }
            // prints the first set of blocks    
            for ( int n = 0; n <= i; n++)
                {
                printf("#");    
                }
            // prints the blank space between the blocks    
            for ( int j = 0; j < 2; j++)
                {
                    printf(" ");
                }
            // prints the final set of blocks
            for (int n = 0; n <= i; n++)
                {
                    printf("#");
                }
            // resets the line for the next row    
            printf("\n");
        }
        
    return 0;
}
