/***********************************************************************
* Code listing from "Advanced Linux Programming," by CodeSourcery LLC  *
* Copyright (C) 2001 by New Riders Publishing                          *
* See COPYRIGHT for license information.                               *
***********************************************************************/

#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

int main (int argc, char* argv[])
{
  char* file = argv[1];
  int fd,milkStorage;
  FILE *quantity = fopen(file,"r");
  char c[1000];
  struct flock lock;

  /* Program exits if file pointer returns NULL. */
  if ((quantity=fopen(file,"r"))==NULL){
       printf("Error! opening file");
       exit(1);
  }

  /*Return the info inside the file in a integer*/
  fscanf(quantity,"%[^\n]",c);
  fclose(quantity);
  milkStorage = atoi(c);

  /* Open a file descriptor to the file.  */
  printf ("Checking availability of milkStorage in:  %s\n", file);
  fd = open (file, O_WRONLY);
  printf ("Please wait...\n");

  /* Initialize the flock structure.  */
  memset (&lock, 0, sizeof(lock));
  lock.l_type = F_WRLCK;

  /* Place a write lock on the file.  */
  fcntl (fd, F_SETLKW, &lock);

  /*Updates, in a file, the available milkStorage*/
  if(milkStorage > 0 ){
    printf("%s\n", "Yes, we have milkStorage!");
    milkStorage = milkStorage -1;
    quantity = fopen(file, "w");
    fprintf(quantity, "%d",milkStorage);
    fclose(quantity);
    printf ("Press enter to pay.");
    getchar ();
    printf ("Thanks for buying with us!\n");

  }else{
    printf("%s\n", "I'm sorry, we don't have milkStorage anymore, press enter to exit.");
    getchar ();
    printf ("Thanks for your visit!\n");
  }
  /*Release the lock.*/
  lock.l_type = F_UNLCK;
  fcntl (fd, F_SETLKW, &lock);
  close (fd);
  return 0;

}
