/* Pola Madej 4.04.2022 Kraków
W procesie potomnym uruchamia program z podpunktu (a), po czy z procesu macierzystego wysyła do niego sygnał; 
w procesie macierzystym przed wywołaniem funkcji kill() wstawić funkcję sleep() z krótkim czasem uśpienia */

#define _XOPEN_SOURCE 500
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include <string.h>

int main(int argc, char *argv[]) {
    if (argc != 4) {
        printf("Podales niewlasciwa liczbe argumentow.\n");
        exit(EXIT_FAILURE);
    }
    
    int childPid = 0;
    switch (childPid = fork()) {
       case -1:
            perror("fork error");
            exit(EXIT_FAILURE);
            break;
       case  0:
            childPid = getpid();
            if (execlp(argv[3], argv[3], argv[1], argv[2], NULL) == -1) {   //uruchamia 3a
                perror("execl error");
                exit(EXIT_FAILURE);
            }
            break;
       default:
            sleep(1);   //czeka na uruchomienie 3a
            if (kill(childPid, 0) == -1) {     //czy proces istnieje
                perror("Proces nie istnieje");
                exit(EXIT_FAILURE);
            }
            if (kill(childPid, atoi(argv[1])) == -1) {
                exit(EXIT_FAILURE);
            }
    }
    if (strcmp(argv[2], "ignore") == 0) {
        printf("Zamykam proces, ktory ignorowal sygnal.\n");
        kill(childPid, SIGKILL);
    }
    return 0;
}