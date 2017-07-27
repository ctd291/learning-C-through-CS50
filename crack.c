// what a crappy way to write code! this program works... somehow for up to 4 chars to guess the password.
// Theoretically you could change the parameters to include special chars in ascii and not just alphabet chars.
// Also one could expand the inner loop to make the length greater then 4, which is what ive chosen.

#include <stdio.h>
#include <unistd.h>
#include <crypt.h>
#include <cs50.h>
#include <string.h>
#include <unistd.h>
#define _XOPEN_SOURCE
string hash, pw;

// sets up the initial length of the password to brute force, this case its 4, not sure if you need the first 'A'
char password[4] = {'A',0,0,0};

//string alpha ="ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"; // debaited using a different index to run through

//if you know the salt thats half the battle
string salt = "50";
// a mess of variables used for the loops, y z l are used for the three inner loops
int h = 0, n = 0, i = 0, x = 52, y = 0, z = 0, l = 0;

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        // explains the usage of program
        printf("usage: ./crack hash\n");
        return 1 ;
    }
    // set the the typed hash to a string for comparison later
    hash = argv[1];
    for (int j = 0; j < 4; j++) // index loop for length of password, increasing j increases the length of the brute force
    {
        for(i = 0; i <= j; i++) //sets up the initial char 'A' for each index loop
                {
                    password[i] = 'A';
                } 
        y = 0, z = 0;
        while (password[j] < 'z') // this make the program loop till the last char in the array is 'z'
        {
                    if (password[0] == 'z') // first of the inner loop, checks the for left char
                        {
                            // these lines of code just sets the array of chars to check, in this case its A-Z and a-z
                            if (y < 26)  
                            {
                                password[1] = 'A' + y;    
                            }
                            else
                            {
                                password[1] = y + 71;
                            }
                            y++; // increases a var for the char in the password
                            if (password[1] == 'z' && j >= 2) // second part of the loop, the j >= 2 makes sure you dont add outside of your given array
                            {
                                y = 0; // this line resets the previous char to the initial starting char, one would just add more loops like this for a longer password check
                                if ( z < 26)
                                {
                                    password[2] = 'A' + z;    
                                }
                                else
                                {
                                    password[2] = z + 71;
                                }
                                z++;
                                if (password[2] == 'z' && j >= 3)
                                {
                                    z = 0;
                                    if (l < 26)
                                    {
                                        password[3] = 'A' + l;   
                                    }
                                    else
                                    {
                                        password[3] = l + 71;
                                    }
                                    l++; // final var for the loops
                                }
                            }
                        }
                    n = j; // not needed, you could just use j
                    
                    // this is the primary loop that does all the work, looping over the length of the test array, this case its 52 chars, for the first char in the password repeting however many times as needed. In out example its 52*52*52*52(52^4)
                    for (i = 0; i < x; i++)
                    {
                        if (i < 26)
                        {
                            password[j - n] = i + 'A';
                        }
                        if (i >= 26)
                        {
                            password[j - n] = i + 71;
                        }
                        //printf("%s ", password); // used for debugging, soo many infinite loops 
                        
                        h++; // counter for iteration
                        pw = crypt(password, salt); // encrypts the current iteration of the password and assigns it to a string
                        if (strcmp(pw, hash) == 0) // compares the given hash and current iteration of password
                        {
                            printf("%s\n", password); // displays correct password
                            return 0; // exits program
                        }
                    }
                }
        }
    //printf("%i ", h); used for debugging, displays how many combinations were used
    //printf("%s", pw);
    printf("password not found\n");
    }

    
    
