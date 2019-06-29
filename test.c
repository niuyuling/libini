#include "libini.h"
#include <stdio.h>

int main(void) {

    char buf[50];
    getinikeystring("CAT", "age", "config.ini", buf);           // 字符串
    printf("%s\n", buf);
    getinikeystring("CAT", "name", "config.ini", buf);          // 字符串
    printf("%s\n", buf);


    printf("%d\n", getinikeyint("CAT", "a", "config.ini"));     // 整型
    printf("%ld\n", getinikeylong("CAT", "b", "config.ini"));   // 长整型
    printf("%f\n", getinikeyfloat("CAT", "c", "config.ini"));   // 浮点型（默认小数点后6位）


    putinikeystring("TAC", "e", "!@#$%^&*()_+", "config.ini");  // 写入
    getinikeystring("TAC", "e", "config.ini", buf);
    printf("%s\n", buf);
    
    return 1;
}