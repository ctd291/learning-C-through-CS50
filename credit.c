// runs a checksum to see if the number entered is a credit card and is valid. It also identifies the brand of CC
/* Luhn’s algorithm, for more check out CS50.net

    Multiply every other digit by 2, starting with the number’s second-to-last digit, and then add those products' digits together.

    Add the sum to the sum of the digits that weren’t multiplied by 2.

    If the total’s last digit is 0 (or, put more formally, if the total modulo 10 is congruent to 0), the number is valid!
*/

#include <cs50.h>
#include <stdio.h>
#include <math.h>

long long cc_number, cc_temp;
int counter = 0, temp_number = 0, total_number = 0;

int main(void)
{
    do
        {
            printf("Please enter a credit card number and ill check if it is valid:");
            cc_number = cc_temp = get_long_long();
        }
    while (cc_number < 0);
    while(cc_number > 0 ) // sets up the loop to run through every digit of the number given
        {
            temp_number = cc_number % 10; // this assignment saves of the right most digit of the given number
            if (counter % 2 == 1) // checks to see if the digit need to be multiplied by 2 
                {
                    temp_number *= 2; // multiplies current digit by 2
                    while (temp_number >= 10) // checks if the digit is greater then 10, if so it splits up the digits then adds them in next line
                        {
                            temp_number = (temp_number % 10) + 1; //since the highest a digit to be multiplied is 9, you just need to module by 10 and add a 1 to get the sum of both digits
                        }
                    total_number += temp_number; // adds current digit to total checksum number
                    cc_number /= 10; // this math division moves the current digit left E.I. 123/10 becomes 12 
                    counter++; //keeps track of how long the number is, needed for checking brand of CC 
                }
            else if(counter % 2 == 0) // this loop adds the current digit 
                {
                    cc_number = cc_number/10; // this math division moves the current digit left EI 123/10 becomes 12
                    counter++; //keeps track of how long the number is, needed for checking brand of CC 
                    total_number += temp_number; // adds current digit to total
                }
        }
    if (total_number % 10 == 0) // this is the checksum for the CC if total_number's last digit is 0, if so then it is a valid CC number
        {
            if (counter == 15) // checks for amex condition
                {
                    long long x = cc_temp / 10e12; // this fomula identifies the first 2 digits of the CC 
                    if (x == 34 || x == 37) // all AMEX cards start with these 2 numbers
                        {
                            printf("AMEX\n");
                        }
                }
            if (counter == 16) // checks Mastercard condition
                {
                   long long x = cc_temp / 10e13; // this fomula identifies the first 2 digits of the CC
                   if (51 <= x && x <= 55) // all mastercard number start 51 through 55
                        {
                            printf("MASTERCARD\n");
                        }
                }
            if (counter == 13 || counter == 16) // checks Visa condition, since visa are 13 digit and 16 digit long cards
                {
                    long long x = cc_temp / 10e14; // checks 16 digit long number
                    long long y = cc_temp / 10e11; // checks 13 digit long number
                    if (x == 4 || y == 4) // all visa numbers start with the number 4
                        {
                            printf("VISA\n");
                        }
                }
        }
    else
        {
            printf("INVALID\n"); // if the checksum fails, this line is displayed
        }
}
