/* Recover searches a raw memory file for jpg's that are stored back to back.
** More stuff here
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    // checks to make sure the argument is correct
    if(argc != 2)
    {
        fprintf(stderr, "Usage: ./recover card.raw\n");
        return 1;
    }
    // creates the variables need for running the program

    // this is the pointer to the raw memory data
    char *raw_infile = argv[1];
    //this is for keeping track of the jpg's
    int jpg_counter = 0;
    // creates an array for the names of the files to be created
    char name[9] = {0};
    //not sure of this is correct since we will be using it later
    FILE *outptr = NULL;

    // opens the raw data and makes sure is the program has enough memory
    FILE *raw_pointer = fopen(raw_infile, "r");
    if (raw_pointer == 0)
    {
        fprintf(stderr, "Could not open %s.\n", raw_infile);
        return 2;
    }
    // creates an array for the tempory buffer of data
    unsigned char *buffer = malloc(512);

    // this is the primary loop for the program it will continue until fread cant reading anymore
    while(fread(buffer, 512, 1, raw_pointer) == 1)
    {
        // checks the first 4 bytes of the buffer to check for the signiture of a jpg
        if (buffer[0] == 0xff &&
            buffer[1] == 0xd8 &&
            buffer[2] == 0xff &&
            (buffer[3] & 0xf0) == 0xe0)
        {
            printf("found a jpg %i\n", jpg_counter);
            //this funtion creates names for every new jpg file starting at 1
            sprintf(name,"%.3i.jpg", jpg_counter);

            // checks if this is the first file found, if not then it closes the last jpg file open
            if ( jpg_counter > 0)
            {
                fclose(outptr);
            }

            // opens/creates a new file to write data into
            outptr = fopen(name, "w");
            if (outptr == NULL)
                    {
                        fprintf(stderr, "Could not open %s.\n", name);
                        return 3;
                    }
            //printf("%s\n", name);  troubleshooting
            jpg_counter++;
        }

        // this if condition makes sure the program doesnt start writing until the first jpg signiture is found
        if (jpg_counter > 0)
            {
                fwrite(buffer, 512, 1, outptr);
            }
    }
    //frees memory and closes files
    free(buffer);
    fclose(raw_pointer);
    fclose(outptr);
}
