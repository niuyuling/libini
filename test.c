#include "libini.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    char buf[50];
    memset(buf, 0, 50);
    getinikeystring("CAT", "age", "config.ini", buf); // 字符串
    printf("%s\n", buf);
    
    memset(buf, 0, 50);
    getinikeystring("CAT", "name", "config.ini", buf); // 字符串
    printf("%s\n", buf);
    memset(buf, 0, 50);

    printf("%d\n", getinikeyint("CAT", "a", "config.ini")); // 整型
    memset(buf, 0, 50);
    printf("%ld\n", getinikeylong("CAT", "b", "config.ini")); // 长整型
    memset(buf, 0, 50);
    printf("%f\n", getinikeyfloat("CAT", "c", "config.ini")); // 浮点型（默认小数点后6位）
    memset(buf, 0, 50);

    putinikeystring("TAC", "e", " abcdef!@#$%^&*()_+", "config.ini"); // 写入
    getinikeystring("TAC", "e", "config.ini", buf);
    printf("%s\n", buf);
    memset(buf, 0, 50);

    getinikeystring("TAC", "f", "config.ini", buf);
    printf("%s\n", buf);
    memset(buf, 0, 50);
    
    printf("%d\n", getinikeystring("CAT", "age", "config.ini", buf));

    return 1;
}
