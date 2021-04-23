#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
void decrypt(char arr[])
{
      int i;
      for(i = 0; i < strlen(arr); i++)
      {
            arr[i] = arr[i] + 10;
      }
}
 
void encrypt(char arr[])
{
      int i;
      for(i = 0; i < strlen(arr); i++)
      {
            arr[i] = arr[i] - 10;
      }
}
 
int main()
{
      char password[40]; 
      int ch;
      printf("Enter a Password:\t");
      scanf("%s", password);
      printf("\nPassword:\t%s\n",password);
      encrypt(password);
      printf("\nEncrypted Password:\t%s\n", password);
      decrypt(password);
      printf("\nDecrypted Password:\t%s\n", password);
      return 0;
}