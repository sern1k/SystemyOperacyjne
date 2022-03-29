#include <stdio.h>
#include <unistd.h> //biblioteka potrzebna do uzycia funkcji systemowych
#include <stdlib.h> //biblioteka potrzebna do uzycia funkcji exit

void wypisywanie()
{
    printf("UID = %i\tGID = %i\tID = %i\tPPID = %i\tPGID = %i\n\n", getuid(), getgid(), getpid(), getppid(), getpgrp()); //funckja wypisujaca ID procesow
}

int main() {
    printf("ID procesu macierzystego:\n");
    wypisywanie();

    int i; //pomocnicza zmienna
    for (i = 0; i < 3; i++)
    {
        switch (fork())
        {
            case -1:
                perror("fork error");
                exit(1);
            case 0:
                printf("ID procesu potomnego:\n");
                wypisywanie();
                sleep(1);
                break;
            default:
                break;
        };
    }
    sleep(4);
    return 0;
}
