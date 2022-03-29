/* Pola Madej, Krakow 29.03.2022
 * W procesie macierzystym utworzyc proces potomny i sprawic, aby stal sie liderem nowej grupy,
 * nastepnie uruchomic w nim kilka procesow potomnych wykonujacych program do obslugi sygnalow */

//#define _POSIX_C_SOURCE 200112L
//#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <unistd.h> //do obslugi np getpid()
#include <stdlib.h> //do obslugi np exit(EXIT_FAILURE)
#include <signal.h> //do obslugi sygnalow
#include <sys/wait.h

int main(int argc, char *argv[]) {

    if (argc != 4) {                //obsluga bledu w przypadku zlej liczby argumentow
        printf("Blad - zla ilosc argumentow\n");
        exit(EXIT_FAILURE);
    }

    setpgid(0,0);
    printf("PID procesu dziecka: %d/n", getpgrp());

    for(int i = 0; i < 3; i++) {
        switch (fork()) {
            case -1:
                perror("fork error");
                exit(EXIT_FAILURE);

            case 0:
                if (execl(argv[3], argv[3], argv[1], argv[2], NULL) == -1) {
                    perror("execl error");
                    exit(EXIT_FAILURE);
                }
                perror("execl error");
                exit(EXIT_FAILURE);
                break;

            default:
                break;
        };
    }

    if (signal(atoi(argv[1]), SIG_IGN) == SIG_ERR) {
        perror("Problem funkcji z SIGINT");
        exit(EXIT_FAILURE);
    }

    int stat = 0;
    int procesPID;

    for(int i = 0; i < 3; i++) {
        if ((procesPID = wait(&stat)) == -1) {
            perror("wait error");
            exit(EXIT_FAILURE);
        }
        printf("Status zakonczenia procesu %d: %d\n", procesPID, stat);
    }
}
