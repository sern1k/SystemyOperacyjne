/* Pola Madej 4.04.2022 Kraków
Pierwszy tworzy jeden proces potomny i uruchamia w nim program, 
który ustawia ignorowanie sygnału, staje się liderem swojej grupy procesów, 
a następnie tworzy kilka procesów potomnych, które uruchamiają program z podpunktu (a) */

#define _XOPEN_SOURCE 500
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int childPid = 0;
    int childGroup = 0;
    if (argc != 5) {
        printf("Podales niewlasciwa liczbe argumentow.\n");
        exit(EXIT_FAILURE);
    }
    
    switch (childPid = fork()) {
       case -1:
            perror("fork error");
            exit(EXIT_FAILURE);
            break;
       case  0:
            if (execvp(argv[3], argv) == -1) {  //uruchamia 3c2.out
                perror("execl error");
                exit(EXIT_FAILURE);
            }
            break;
       default:
            sleep(1);
            childGroup = getpgid(childPid);
            if (kill(-1 * childGroup, 0) == -1) {   //czy proces istnieje
                perror("Proces nie istnieje");
                exit(EXIT_FAILURE);
            }
            if (kill(-1 * childGroup, atoi(argv[1])) == -1) {
                exit(EXIT_FAILURE);
            }
    }
    sleep(1);
    if (strcmp(argv[2], "ignore") == 0) {
        printf("Zamykam proces, ktory nie zamknal sie przez to, ze mial ignorowac sygnal\n");
        kill(-1 * childGroup, SIGKILL);
    }
    return 0;
}