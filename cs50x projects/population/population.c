#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

// Define a constant for the minimum start size
#define MIN_START_SIZE 9

int main(void)
{
    // Prompt for start size
    long start_size;
    do
    {
        start_size = get_long("Start size:\n");
    }
    while (start_size < MIN_START_SIZE);

    // Prompt for end size
    long end_size;
    do
    {
        end_size = get_long("End size:\n");
    }
    while (end_size < start_size);

    // Calculate number of years until we reach end size
    long current_size = start_size;
    long years = 0;
    while (current_size < end_size)
    {
        // Use formula to calculate new population size
        current_size = current_size + (current_size / 3) - (current_size / 4);
        years++;
    }

    // Print number of years
    printf("Years: %li\n", years);
}