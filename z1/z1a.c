#include <stdio.h>
#include <unistd.h> //biblioteka potrzebna do uzycia funkcji systemowych

void wypisywanie()
{
    printf("UID = %i\nGID = %i\nPID = %i\nPPID = %i\nPGID = %i\n\n", getuid(), getgid(), getpid(), getppid(), getpgrp()); //funckja wypisujaca ID procesow
}

int main()
{
    wypisywanie();
    return 0;
}
