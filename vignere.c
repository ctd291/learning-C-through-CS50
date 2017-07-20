//  program that encrypts text from cs50

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
string key;

int main (int argc, string argv[])
{
    // we only want 2 command line arguments from the user
    if (argc != 2)
    {
        printf("usage: ./vignere key\n");
        return 1 ;
    }
    key = argv[1];
    //save the length of the key used for looping the key 
    int j = strlen(key);
    // puts the key into a array of ints
    int code[j];
    // this loops normalizes the key to 0-25, a = 0, b = 1 etc....
    for (int i = 0; i < j; i++)
    {
        if (isalpha(key[i]))
        {
            if (isupper(key[i]))
            {
                code[i] = (key[i] - 'A');
                
            }
            if (islower(key[i]))
            {
                code[i] = (key[i] - 'a');
            }
        }
        else 
        {
            printf("not a valid key, try again.\n");
            return 1;
        }
    }
    printf("plaintext:");
    // gets input from user
    string text = get_string();
    printf("ciphertext:");
    // sets up a loop to run through the string given by the user
    for (int i = 0, h = 0; i < strlen(text); i++)
    {
        // this checks the position of the var in the code array, making sure it loops around the key
        if (h >= j)
        {
            h = h % j;
        }
        if ( isalpha(text[i]))
        {
            if (isupper(text[i]))
            {
                text[i] += code[h];
                // this statemnet loops back around the alphabit if the program goes past 'Z'
                if (text[i] > 90)
                {
                    text[i] = (text[i] % 90) + 64;
                }
                printf("%c", text[i]);
            }
            if (islower(text[i]))
            {
                // since get_string stores the input of each char in an array with a max of +128, this moves them into an integar 
                int overflow = text[i] + code[h];
                if (overflow > 122)
                {
                    overflow = (overflow % 122) + 96;
                }
                printf("%c", overflow);
            }
            // moves the position of which key to use
            h++;
        }
        // displays all non-alpha chars
        if (! isalpha(text[i]))
            {
                printf("%c", text[i]);
            }
    }
    printf("\n");
}
