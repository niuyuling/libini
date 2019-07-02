#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libini.h"

#define BUFFER_SIZE 1024

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

int getinikeystring(char *title, char *key, char *filename, char *buf)
{
    FILE *fp;
    int flag = 0;
    char sTitle[BUFFER_SIZE], *wTmp;
    char sLine[BUFFER_SIZE];
    sprintf(sTitle, "[%s]", title);

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
            if (0 == strncmp(key, sLine, strlen(key))
                &&
                !(strncasecmp
                  (strtok(sLine, "="), key, strlen(strtok(sLine, "="))))) {
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
                      (strtok(sLine_backup, "="), key,
                       strlen(strtok(sLine_backup, "="))))) {
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
