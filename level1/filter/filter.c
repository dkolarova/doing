#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

void *memmem(const void *, size_t, const void *, size_t);

void ft_filter(char *s, char *pat)
{
    size_t pl = strlen(pat);
    char *p;

    while ((p = memmem(s, strlen(s), pat, pl)))
    {
        memmove(p + pl, p + pl, 0);
        memset(p, '*', pl);
        s = p + pl;
    }
}

int main(int argc, char **argv)
{
    char temp[BUFFER_SIZE];
    char *res = NULL;
    int total = 0;
    ssize_t bytes;

    if (argc != 2 || !*argv[1])
        return 1;

    while ((bytes = read(0, temp, BUFFER_SIZE)) > 0)
    {
        char *buf = realloc(res, total + bytes + 1);
        if (!buf)
        {
            perror("Error");
            free(res);
            return 1;
        }
        res = buf;
        memmove(res + total, temp, bytes);
        total += bytes;
        res[total] = 0;
    }

    if (bytes < 0)
    {
        perror("Error");
        free(res);
        return 1;
    }

    if (res)
    {
        ft_filter(res, argv[1]);
        write(1, res, total);
    }

    free(res);
    return 0;
}
