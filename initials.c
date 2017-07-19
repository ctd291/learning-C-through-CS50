

#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

string name;
int i = 0;

int main(void)
{
    //printf("Give me your name and initialize it:");
    // gets input 
    name = get_string();
    // makes sure the string is valid
    if (name == NULL)
    {
        printf("not a valid entry\n");
        return 1;
    }
    // runs the each element of the string
    while (i < strlen(name))
    {
        // checks the very first element for a letter 
        if (isalpha(name[i]) && i == 0)
        {
            printf("%c", toupper(name[i]));
        }
        // checks for a gap in the input
        if (name[i] == ' ')
        {
            i++;
            // checks for end of input
            if (i > strlen(name))
            {
                printf("\n");
                return 0;
            }
            //this nested statement checks if the next element is a letter
            if (isalpha(name[i]))
            {
                printf("%c", toupper(name[i]));    
            }
        }
        //moves on to the next char in the string
        else 
        {
            i++;
        }
    }
    printf("\n");
}
