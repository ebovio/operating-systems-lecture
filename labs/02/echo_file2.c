#include <stdio.h>
#include <stdlib.h>  /* For exit() function */
int main()
{
   char sentence[1000];
   char openFile[100];

   FILE *fptr;

   printf("Enter a file name: \n");
   gets(openFile);

   fptr = fopen(openFile, "w");
   if(fptr == NULL)
   {
      printf("Error!");
      exit(1);
   }

   printf("Enter a sentence:\n");
   gets(sentence);

   fprintf(fptr,"%s", sentence);
   fclose(fptr);

   return 0;
}
