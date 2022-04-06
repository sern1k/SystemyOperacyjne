/* Pola Madej 4.04.2022 Kraków
Uruchamia program 3a, czeka na zakonczenie procesow i zwraca ich stan zakonczenia.*/

#define _XOPEN_SOURCE 500
#define _POSIX_C_SOURCE 200112L
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/wait.h>

int main(int argc, char *argv[]) {
    if (argc != 5) {
        printf("Podales niewlasciwa liczbe argumentow.\n");
        exit(EXIT_FAILURE);
    }
    int stan = 0;
    setpgid(0, 0);
    for (int i = 0; i < 3; i++) {
        switch (fork()) {
           case -1:
                perror("fork error");
                exit(EXIT_FAILURE);
                break;
           case  0:
                if (execlp(argv[4], argv[4], argv[1], argv[2], NULL) == -1) {      //uruchamiamy 3a.out
                    perror("execl error");
                    exit(EXIT_FAILURE);
                }
                perror("execl error");
                exit(EXIT_FAILURE);
                break;
           default:
                break;
        }
    }
    if (signal(atoi(argv[1]),SIG_IGN) == SIG_ERR) {
        perror("Funkcja signal napotkala problem");
        exit(EXIT_FAILURE);
    }
    int childProc = 0;
    for (int i = 0; i < 3; i++) {
        if ((childProc = wait(&stan)) == -1) {
            perror("wait error");
            exit(EXIT_FAILURE);
        }
        printf("Stan zakonczenia procesu %d: %d\n", childProc, stan);
    }
    return 0;
}