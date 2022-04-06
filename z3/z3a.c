/* Pola Madej 4.04.2022 Kraków
Ustawia obsługę sygnału na 3 sposoby zgodnie z opcją podaną jako argument wywołania programu, a następnie czeka na sygnał */

#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>

void ObslugaCustom(int sig) {
    extern const char * const sys_siglist[];
    printf("\nWlasna obsluga sygnalu:\n");
    printf("Sygnal %s, %d\n", sys_siglist[sig], sig);
}

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printf("Podales niewlasciwa liczbe argumentow.\nPrawidlowe wywolanie funkcji to: make runA SYGNAL=? OPCJA=?\ngdzie SYGNAL to liczba a OPCJA to default, ignore lub custom\n");
        exit(EXIT_FAILURE);
    }
    printf("PID procesu: %d\n", getpid());
    
    if (strcmp(argv[2], "default") == 0) {
        if (signal(atoi(argv[1]), SIG_DFL) == SIG_ERR) {    //atoi - konwertuje wartosc zapisana w lancuchu znakow do postaci int
            printf("Funkcja signal napotkala problem\n");
            exit(EXIT_FAILURE);
        }
    } else if (strcmp(argv[2], "ignore") == 0) {
        if (signal(atoi(argv[1]), SIG_IGN) == SIG_ERR) {
            printf("Funkcja signal napotkala problem\n");
            exit(EXIT_FAILURE);
        }
    } else if (strcmp(argv[2], "custom") == 0) {
        if (signal(atoi(argv[1]), ObslugaCustom) == SIG_ERR) {
            printf("Funkcja signal napotkala problem\n");
            exit(EXIT_FAILURE);
        }
    } else {
        printf("Zla opcja.");
        exit(EXIT_FAILURE);
    }
    pause();

    return 0;
}