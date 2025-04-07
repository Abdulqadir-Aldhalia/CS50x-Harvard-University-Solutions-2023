#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x;
    do{
        x=get_int("Inter the higth");

     } while(x<1||x>8);

      int i=2;
      int count=x;

      while (count>0){

        for(int a=count-1;a>0;a--){printf(" ");}
        for(int j=i/2;j>0;j--)
        {
           printf("#");
        }
         printf("  ");
         for(int j=i/2;j>0;j--)
         {

            printf("#");
        }

        i+=2;
        count--;
        printf("\n");
      }
}