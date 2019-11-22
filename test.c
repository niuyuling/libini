#include "libini.h"
#include <stdio.h>
#include <string.h>

int main(void)
{
    char *tmp = NULL;
    libini_memory(&tmp);    // 创建内存
    
    getinikeystring("CAT", "age", "config.ini", tmp); // 字符串
    printf("%s\n", tmp);
    
    getinikeystring("CAT", "name", "config.ini", tmp); // 字符串
    printf("%s\n", tmp);

    printf("%d\n", getinikeyint("CAT", "a", "config.ini")); // 整型
    printf("%ld\n", getinikeylong("CAT", "b", "config.ini")); // 长整型
    printf("%f\n", getinikeyfloat("CAT", "c", "config.ini")); // 浮点型（默认小数点后6位）

    putinikeystring("TAC", "e", " abcdef!@#$%^&*()_+", "config.ini"); // 写入
    getinikeystring("TAC", "e", "config.ini", tmp);
    printf("%s\n", tmp);

    getinikeystring("TAC", "f", "config.ini", tmp);
    printf("%s\n", tmp);
    
    libini_free(tmp);
    return 1;
}
