#include <stdio.h>

int main ()
{
   FILE * fp;
  
   fp = fopen ("data.txt","w");

   char str[]="Rahul Khatoliya";
 
   fputs(str, fp);
 
   fclose (fp);
   return 0;
}