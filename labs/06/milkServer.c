#include <sys/types.h>
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
  key_t k;
  char *shm,*s;
  sem_t *mutex;

  k = 1000;

  mutex = sem_open(SEM_NAME,O_CREAT,0644,4);
  if(mutex == SEM_FAILED){
      perror("Unable to create");
      sem_unlink(SEM_NAME);
      exit(-1);
    }

  id_shm = shmget(k,SHMSZ,IPC_CREAT|0666);
  if(id_shm<0){
      perror("Failure in shmget");
      exit(-1);
    }

  shm = shmat(id_shm,NULL,0);

  *shm=30;

  while(*shm != 0){
      sleep(1);
    }
  sem_close(mutex);
  sem_unlink(SEM_NAME);
  shmctl(id_shm, IPC_RMID, 0);
  exit(0);
}
