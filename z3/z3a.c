/* Pola Madej, Krakow 29.03.2022
 * Program do obslugi sygnalow z mozliwosciami
 * 1.operacji domyslnej
 * 2. ignorowania
 * 3. przechwycenia i wlasnej obslugi sygnalu */

//#define _POSIX_C_SOURCE 200112L
//#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <unistd.h> //do obslugi np getpid()
#include <stdlib.h> //do obslugi np exit(EXIT_FAILURE)
#include <string.h> //do obslugi strcmp()
#include <signal.h> //do obslugi sygnalow

void obsluga(int sygnal) {
    extern const char * const sys_siglist[];
    printf("\nWlasna obsluga sygnalu:\n");
    printf("Sygnal %s, %d\n", sys_siglist[sygnal], sygnal);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {                //obsluga bledu w przypadku zlej liczby argumentow
        printf("Blad - zla ilosc argumentow\n");
        exit(EXIT_FAILURE);
    }

    printf("PID procesu: %d/n", getpid());

    if (strcmp(argv[2], "ignore") == 0) {    //strcmp - porownuje dwa lancuchy znakow
        if (signal(atoi(argv[1]), SIG_IGN) == SIG_ERR) { //atoi - konwertuje wartosc zapisana w lancuchu znakow do int
            perror("Problem funkcji z SIGINT");
            exit(EXIT_FAILURE);
        }
    } else if (strcmp(argv[2], "default") == 0) {
        if (signal(atoi(argv[1]), SIG_DFL) == SIG_ERR) {
            perror("Problem funkcji z SIGINT");
            exit(EXIT_FAILURE);
        }
    } else if (strcmp(argv[2], "custom") == 0) {
        if (signal(atoi(argv[1]), obsluga) == SIG_ERR) {
            perror("Problem funkcji z SIGINT");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Bledna opcja %s\n", argv[2]);
    }

    pause();
}
