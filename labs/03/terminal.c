#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

int main(void){
        char line[50];
        char *cmd[10];
        char *token;

        while (1){
                int counter = 0;
                printf("terminal $ ");
                scanf(" %50[^\n]", line);
                if(strcmp(line, "exit") == 0){
                        exit(-1);
                }
                token = strtok (line," ");
                while (token != NULL){
                        cmd[counter] = token;
                        token = strtok (NULL, " ");
                        counter++;
                }
                cmd[counter] = '\0';
                pid_t pid;
                pid = fork();
                if (pid < 0){
                        exit (-1);
                }
                else if (pid == 0){
                        execvp(cmd[0], cmd);
                }
                else{
                        wait(NULL);
                }
        }
}
