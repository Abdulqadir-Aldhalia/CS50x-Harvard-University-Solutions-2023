#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void convert(string input);
int n=0;
int main(void)
{
    string input = get_string("Enter a positive integer: ");
    n = strlen(input);

    for (int i = 0; i<n; i++)
    {
        if (!isdigit(input[i]))
        {
            printf("Invalid Input!\n");
            return 1;
        }
    }
      n=n-1;

    // Convert string to int
    convert(input);
}

void convert(string input)
{
  // TODO
    if(n<0)
    {
        return;

    }

      char j=input[n];
      int i= j - '0';
      n--;
      convert(input);
      printf("%i",i);

}