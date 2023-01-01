#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{

    // Check for invalid usage
    if (argc != 2)
    {
        printf("Usage: ./recover IMAGE\n");
        return 1;
    }

    FILE *f = fopen(argv[1], "r");
    if (f != NULL)
    {
        // Array to store the char bytes & // Read the file bytes
        unsigned char blocks[512];
        // track num imgs generated
        int c_i = 0;

        // output file
        FILE *o_f = NULL;

        // allocation mem for reading
        char *f_name = malloc(8 * sizeof(char));

        while (fread(blocks, sizeof(char), 512, f))
        {
            // check if bytes indicate start of JPEG
            // Condition for JPEG image
            if (blocks[0] == 0xff
                && blocks[1] == 0xd8
                && blocks[2] == 0xff && (blocks[3] & 0xf0) == 0xe0)
            {
                sprintf(f_name, "%03i.jpg", c_i);
                o_f = fopen(f_name, "w");
                c_i++;
            }

            if (o_f != NULL)
            {
                fwrite(blocks, sizeof(char), 512, o_f);
            }
        }
        free(f_name);
        fclose(f);
        fclose(o_f);

        return 0;
    }
    else
    {
        printf("File not found.\n");
        return 2;
    }
}