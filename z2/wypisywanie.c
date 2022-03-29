/* Pola Madej, Krakow 22.03.2022
* Wypisywanie ID procesow potomnych */

#include <stdio.h>
#include <unistd.h> //biblioteka potrzebna do uzycia funkcji systemowych

int main() {
    {
        printf("ID procesu potomnego: \n");
        printf("UID = %i\tGID = %i\tID = %i\tPPID = %i\tPGID = %i\n\n", getuid(), getgid(), getpid(), getppid(), getpgrp()); //funckja wypisujaca ID procesow
    }
    return 0;
}