#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libini.h"

#define BUFFER_SIZE 1024

// 去除str前的"和后的";
char *delchar(char *str, char *temp)
{
    int len = strlen(str);
    char *p1 = str;
    if ((0 == strncmp("\"", str, 1)) && (str[len - 1] == ';')
        && (str[len - 2] == '"')) {
        p1[len - 2] = '\0';
        return strcpy(temp, p1 + 1);
    } else {
        return str;
    }
    return str;
}

// 去除字符空格
char *del_space(char *str, char *buf)
{
    unsigned int uLen = strlen(str);

    if (0 == uLen) {
        return '\0';
    }

    memset(buf, 0, uLen + 1);

    unsigned int i = 0, j = 0;
    for (i = 0; i < uLen + 1; i++) {
        if (str[i] != ' ') {
            buf[j++] = str[i];
        }
    }
    buf[j] = '\0';

    return buf;
}

// 创建临时内存
int libini_memory(char **pp)
{
    if (pp != NULL) {
        char *tmp = (char *)malloc(BUFFER_SIZE);
        if (tmp != NULL) {
            *pp = tmp; // pp的地址指向tmp
            return 1;
        }
    }
    return -1;
}

// 释放临时内存
void libini_free(char *p)
{
    if (p != NULL) {
        free(p);
    }
}

int getinikeystring(char *title, char *key, char *filename, char *buf)
{
    bzero(buf, 0);
    FILE *fp;
    int flag = 0;
    char sTitle[BUFFER_SIZE], *wTmp;
    char sLine[BUFFER_SIZE];
    sprintf(sTitle, "[%s]", title);
    char buf1[BUFFER_SIZE];

    if (NULL == (fp = fopen(filename, "r"))) {
        perror("fopen");
        return -1;
    }
    while (NULL != fgets(sLine, BUFFER_SIZE, fp)) {
        if (0 == strncmp("//", sLine, 2))
            continue;
        if (sLine[0] == '#' || 0 == strncmp("#", sLine, 1))
            continue;
        if (sLine[0] == ';' || 0 == strncmp(";", sLine, 1))
            continue;
        wTmp = strchr(sLine, '=');
        if ((NULL != wTmp) && (1 == flag)) {
            sLine[strlen(sLine) - 1] = '\0';

            //if (0 == strncmp(key, sLine, strlen(key)) && !(strncasecmp(strtok(sLine, "="), key, strlen(strtok(sLine, "="))))) {
            if (0 == strncmp(key, sLine, strlen(key)) &&
                !(strncasecmp
                  (del_space(strtok(sLine, "="), buf1), key,
                   strlen(del_space(strtok(sLine, "="), buf1))))) {   // 判断key长度的等号左边字符是否相等, 判断key长度的等号左边字符(去除空格)是否相等
                fclose(fp);
                while (*(wTmp + 1) == ' ') {
                    wTmp++;
                }
                delchar(strcpy(buf, wTmp + 1), buf);
                return 0;
            }
        } else {
            if (0 == strncmp(sTitle, sLine, strlen(sTitle))) {
                flag = 1;
            }
        }
    }
    fclose(fp);
    return -1;
}

int putinikeystring(char *title, char *key, char *val, char *filename)
{
    char buf[BUFFER_SIZE];
    FILE *fpr;
    FILE *fpw;
    int flag = 0;
    char sLine[BUFFER_SIZE], sTitle[BUFFER_SIZE], *wTmp;
    char sLine_backup[BUFFER_SIZE];
    sprintf(sTitle, "[%s]", title);
    if (NULL == (fpr = fopen(filename, "r")))
        return -1;
    sprintf(sLine, "%s.tmp", filename);
    if (NULL == (fpw = fopen(sLine, "w")))
        return -1;
    while (NULL != fgets(sLine, BUFFER_SIZE, fpr)) {
        if (2 != flag) {
            wTmp = strchr(sLine, '=');
            if ((NULL != wTmp) && (1 == flag)) {
                strcpy(sLine_backup, sLine);
                if (0 == strncmp(key, sLine, strlen(key))
                    &&
                    !(strncasecmp
                      (del_space(strtok(sLine_backup, "="), buf), key,
                       strlen(del_space(strtok(sLine_backup, "="), buf))))) {
                    flag = 2;
                    sprintf(wTmp + 1, "%s\n", val);
                }
            } else {
                if (0 == strncmp(sTitle, sLine, strlen(sTitle))) {
                    flag = 1;
                }
            }
        }
        fputs(sLine, fpw);
    }
    fclose(fpr);
    fclose(fpw);
    sprintf(sLine, "%s.tmp", filename);
    return rename(sLine, filename);
}

int getinikeyint(char *title, char *key, char *filename)
{
    char buf[BUFFER_SIZE];
    getinikeystring(title, key, filename, buf);
    return atoi(buf);
}

long int getinikeylong(char *title, char *key, char *filename)
{
    char buf[BUFFER_SIZE];
    getinikeystring(title, key, filename, buf);
    return atol(buf);
}

float getinikeyfloat(char *title, char *key, char *filename)
{
    char buf[BUFFER_SIZE];
    getinikeystring(title, key, filename, buf);
    return atof(buf);
}
