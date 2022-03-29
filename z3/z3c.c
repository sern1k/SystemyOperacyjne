/* Pola Madej, Krakow 29.03.2022
 * W procesie macierzystym utworzyc proces potomny i sprawic, aby stal sie liderem nowej grupy,
 * nastepnie uruchomic w nim kilka procesow potomnych wykonujacych program do obslugi sygnalow */

//#define _POSIX_C_SOURCE 200112L
//#define _XOPEN_SOURCE 500
#include <stdio.h>
#include <unistd.h> //do obslugi np getpid()
#include <stdlib.h> //do obslugi np exit(EXIT_FAILURE)
#include <signal.h> //do obslugi sygnalow

int main(int argc, char *argv[]) {
    if (argc != 5) {                //obsluga bledu w przypadku zlej liczby argumentow
        printf("Blad - zla ilosc argumentow\n");
        exit(EXIT_FAILURE);
    }

    printf("PID procesu: %d/n", getpid());

    int childrenPID = 0;
    int childrenPGID = 0;

    switch (childrenPID = fork()) {
        case -1:
            perror("fork error");
            exit(EXIT_FAILURE);

        case 0:
            if (execl(argv[3], argv[3], argv[1], argv[4], NULL) == -1) {
                perror("execl error");
                exit(EXIT_FAILURE);
            }
            break;

        default:
            sleep(1);
            childrenPGID = getpgid(childrenPID);

            if (kill((-1)*childrenPGID, 0) == -1) {
                perror("Dziecko tego procesu nie istnieje\n");
                exit(EXIT_FAILURE);
            }
            if (kill((-1)*childrenPGID, atoi(argv[1]))) {
                perror("kill error");
                exit(EXIT_FAILURE);
            }
    }

    sleep(1);

    if (strcmp(argv[2], "ignore") == 0) {
        printf("Pozostaly procesy zombie\n");
        printf("Wysylam SIGKILL do procesow zombie\n");
        kill((-1)*childrenPGID, SIGKILL);
    }
}
