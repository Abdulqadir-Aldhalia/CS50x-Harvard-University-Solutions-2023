#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    // Check for valid arguments
    if (argc != 2)
    {
        printf("Usage: ./recover image\n");
        return 1;
    }

    // Open input file
    FILE *inputFile = fopen(argv[1], "r");
    if (!inputFile)
    {
        printf("Unable to open file\n");
        return 1;
    }

    // Initialize variables
    int block_counter = 0;
    FILE *img = NULL;
    char filename[8];
    BYTE buffer[512];

    // Loop through input file
    while (fread(buffer, sizeof(buffer), 1, inputFile))
    {
        // Check for JPEG header
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // Close previous output file if any
            if (img)
            {
                fclose(img);
            }

            // Create new output file name
            sprintf(filename, "%03i.jpg", block_counter++);

            // Open new output file
            img = fopen(filename, "w");
        }

        // Write to output file if open
        if (img)
        {
            fwrite(buffer, sizeof(buffer), 1, img);
        }
    }

    // Close files
    fclose(inputFile);
    fclose(img);

    // Return success
    return 0;
}