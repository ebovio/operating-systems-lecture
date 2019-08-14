#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <stdio.h>
#include <semaphore.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

#define SHMSZ 27
char SEM_NAME[]= "sem";

int main(){
  int id_shm;
  int quantity;
  key_t k;
  char *shm,*s;
  sem_t *mutex;

  k = 1000;

  mutex = sem_open(SEM_NAME,0,0644,4);
  if(mutex == SEM_FAILED){
      perror("Unable to execute");
      sem_close(mutex);
      exit(-1);
    }

  id_shm = shmget(k,SHMSZ,0666);
  if(id_shm<0){
      perror("Failure in shmget");
      exit(-1);
    }

  shm = shmat(id_shm,NULL,0);

    s = shm;
    printf("Checking availability of milk...\n");
    sem_wait(mutex);
    if(*s > 0 ){
    printf("%s\n", "Yes, we have milk!");
    printf("How many liters you want: ");
    scanf("%d", &quantity);
    *shm=*s-quantity;
    printf ("Thanks for buying with us!\n");
    }else{
    printf("%s\n", "I'm sorry, we don't have milk anymore.");
    }
    sem_post(mutex);

  sem_close(mutex);
  shmctl(id_shm, IPC_RMID, 0);
  exit(0);
}
