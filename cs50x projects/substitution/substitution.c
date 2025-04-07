#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

bool checkLitters(string key[]);
bool checkNumbers(string key[]);
bool checkRepated(string key[]);
string encipher (string key,string input);

int main(int argc, string key[])
{
      bool check=true;

      if(checkLitters(key)==false){
        printf("Key must containd alphabetic charecters.\n");
        return 1;
          }

      //check spaces
      if(argc>2){
        check=false;
        printf("spaces is not allowed\n");
        return 1;
         }


      if(checkRepated(key)==false){
        printf("Key must not contain repated charechters.\n");
        check=false;
        return 1;
           }


      if(checkNumbers(key)==false){
         printf("Key must containd 26 charecters.\n");
         check=false;
         return 1;
          }


      string text=get_string("write the plain text\n");
      string keys=key[1];
      string result=encipher(keys,text);
       printf("ciphertext: %s\n",result);;





      }


    bool checkLitters(string key[]){

      int length =strlen(key[1]);

      for (int i=0;i<length;i++){

        if(isalpha(key[1][i])==false){
          return false;
        }
      }
        return true;
    }


    bool checkNumbers(string key[]){

       int length =strlen(key[1]);

        if(length!=26){

          return false;

        }

      else return true;

      }

    bool checkRepated(string key[]){

      int length=strlen(key[1]);
      bool check=true;

      for(int i=0; i<length;i++){

        for(int j=i+1;j<length;j++){

          if(key[1][i]==key[1][j]){

            check=false;
            break;
               }

           }

       }
         return check;

    }

 string encipher (string key,string input)
{
    for(int s=0;s<26;s++)
    {
        key[s]=toupper(key[s]);
    }
    bool test=false;
    string in=input;
    int i=0;
    char letters[]={'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z'};
    while(i!=strlen(in))
    {
        if(isupper(in[i]))
        {
            test=true;
            in[i]=tolower(in[i]);
        }
        else
        {
            test=false;
        }
        for(int j=0;j<26;j++)
        {
            string key2=key;

            if(in[i]==letters[j])
            {

                in[i]=key2[j];

            }

        }
        if(test==false)
        {
            in[i]=tolower(in[i]);
        }else if(test==true)
        {
            in[i]=toupper(in[i]);
        }
        i++;

    }
    return in;

}


