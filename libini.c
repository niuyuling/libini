#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "libini.h"

int getinikeystring(char *title, char *key, char *filename, char *buf)
{
    FILE *fp;
    int flag = 0;
    char sTitle[64], *wTmp;
    char sLine[1024];
    sprintf(sTitle, "[%s]", title);

    if (NULL == (fp = fopen(filename, "r"))) {
        perror("fopen");
        return -1;
    }
    while (NULL != fgets(sLine, 1024, fp)) {
        if (0 == strncmp("//", sLine, 2))
            continue;
        if ('#' == sLine[0])
            continue;
        if (';' == sLine[0])
            continue;
        wTmp = strchr(sLine, '=');
        if ((NULL != wTmp) && (1 == flag)) {
            sLine[strlen(sLine) - 1] = '\0';
            if (0 == strncmp(key, sLine, strlen(key)) && !(strncasecmp(strtok(sLine, "="), key, strlen(strtok(sLine, "="))))) {
                //printf("%s\n", sLine);
                fclose(fp);
                while (*(wTmp + 1) == ' ') {
                    wTmp++;
                }
                strcpy(buf, wTmp + 1);
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
    char sLine[1024], sTitle[32], *wTmp;
    sprintf(sTitle, "[%s]", title);
    if (NULL == (fpr = fopen(filename, "r")))
        return -1;
    sprintf(sLine, "%s.tmp", filename);
    if (NULL == (fpw = fopen(sLine, "w")))
        return -1;
    while (NULL != fgets(sLine, 1024, fpr)) {
        if (2 != flag) {
            wTmp = strchr(sLine, '=');
            if ((NULL != wTmp) && (1 == flag)) {
                if (0 == strncmp(key, sLine, strlen(key))) {
                    flag = 2;
                    sprintf(wTmp + 1, " %s\n", val);
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
    char buf[256];
    getinikeystring(title, key, filename, buf);
    return atoi(buf);
}

long int getinikeylong(char *title, char *key, char *filename)
{
    char buf[256];
    getinikeystring(title, key, filename, buf);
    return atol(buf);
}

float getinikeyfloat(char *title, char *key, char *filename)
{
    char buf[256];
    getinikeystring(title, key, filename, buf);
    return atof(buf);
}

