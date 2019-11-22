#ifndef LIBINI_H
#define LIBINI_H

int getinikeystring(char *title, char *key, char *filename, char *buf);
int putinikeystring(char *title, char *key, char *val, char *filename);
int getinikeyint(char *title, char *key, char *filename);
long getinikeylong(char *title, char *key, char *filename);
float getinikeyfloat(char *title, char *key, char *filename);
int libini_memory(char **pp);
void libini_free(char *p);

#endif
