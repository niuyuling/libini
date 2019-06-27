#include "libini.h"
#include <stdio.h>

int main(void) {

    char buf[50];
    getinikeystring("CAT", "age", "config.ini", buf);
    printf("%s\n", buf);

    getinikeystring("CAT", "name", "config.ini", buf);
    printf("%s\n", buf);

    printf("%d\n", getinikeyint("CAT", "a", "config.ini"));
    printf("%ld\n", getinikeylong("CAT", "b", "config.ini"));
    printf("%f\n", getinikeyfloat("CAT", "c", "config.ini"));
    return 1;
}