#include <cs50.h>
#include <stdio.h>
#include <string.h>

bool checkSum(char *a);
int checkCredit(char *a);
bool checkInput(char *a);

int main(void)
{
    string a;

    do{
       a =get_string("please enter the number");
    } while(!checkInput(a));

    if(checkSum(a))
    {
        if(checkCredit(a)==0) {printf("AMEX\n"); return 0; }
        if(checkCredit(a)==1) {printf("MASTERCARD\n"); return 0;}
        if(checkCredit(a)==2) {printf("VISA\n"); return 0;}
    }
    printf("INVALID\n");
    return 0;

}

bool checkSum(char *a){

    int len=strlen(a);
    int sum=0;
    int sum2=0;
     for(int i=len-2; i>=0; i-=2)
    {
        int temp=(a[i]-'0')*2;
        while(temp%10!=temp)
        {
            int n=temp%10;
            sum+=n;
            temp/=10;

        }
        sum+=temp;
    }

     for(int j=len-1; j>=0; j-=2)
    {
        sum2+=a[j]-'0';
    }

        int b=sum+sum2;
        if(b%10==0)
        {
            return true;
        }
        else return false;
}

int checkCredit(char *a)
{
    int len=strlen(a);

    if(((a[0]-'0'==3&&(a[1])-'0'==7&&len==15)||
    ((a[0])-'0'==3&&(a[1])-'0'==4))&&len==15)
    {
        return 0;
    }

    if((a[0]-'0'==5&&a[1]-'0'==1&&len==16)||
    ((a[0]-'0'==5&&a[1]-'0'==2&&len==16))||
    ((a[0]-'0'==5&&a[1]-'0'==3&&len==16))||
    ((a[0]-'0'==5&&a[1]-'0'==4&&len==16))||
    ((a[0]-'0'==5&&a[1]-'0'==5&&len==16)))
    {
        return 1;
    }

    if( (((a[0])-'0'==4)&& len==13)||(((a[0])-'0'==4)&&len==16) )
    {
        return 2;
    }

    return 400;
}

bool checkInput(char *a)
{
    int len=strlen(a);
    for(int i=0; i<len;i++)
    {
        if(a[i]<48 || a[i]>57)
        {
            return false;
        }
    }
     return true;
}
