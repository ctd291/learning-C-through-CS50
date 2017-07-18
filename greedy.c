// tell you how many coins will be needed for an amount of money given

#include <cs50.h>
#include <stdio.h>
#include <math.h>

float change1;
int coin_counter = 0, change2 = 0.0, quarter = 25, dime = 10, nickle = 5, penny = 1;

int main(void)
{
    do 
        {
            printf("give me some change to convert:");
            change1 = get_float();
            if (change1 < 0 )
            {
                printf("Invalid amount, please give a positive number\n");
            }
        }
    while(change1 < 0); // checks for negative numbers
    
    change2 = round(change1*100.0); // converts user input to cents and rounds
    
    while (change2 > 0) // insures all the change is accounted for
    {
        while (change2 >= quarter)
            {
                coin_counter++;
                change2 -= quarter;
            }
        while (change2 >= dime)
            {
                coin_counter++;
                change2 -= dime;
            }
        while (change2 >= nickle)
            {
                coin_counter++;
                change2 -= nickle;
            }
        while (change2 >= penny)
            {
                coin_counter++;
                change2 -= penny;
            }
    }
    printf("%i\n", coin_counter); // outputs the amount of coins needed
}
