#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

void *memmem(const void *, size_t, const void *, size_t);

char *read_all(int *len)
{
	char buf[BUFFER_SIZE];
	char *res = NULL;
	ssize_t n;

	*len = 0;
	while ((n = read(0, buf, BUFFER_SIZE)) > 0)
	{
		char *tmp = realloc(res, *len + n + 1);
		if (!tmp)
			return free(res), NULL;
		res = tmp;
		memmove(res + *len, buf, n);
		*len += n;
		res[*len] = 0;
	}
	return (n < 0) ? free(res), NULL : res;
}

void filter(char *s, char *pat)
{
	size_t l = strlen(pat);
	char *p;

	while ((p = memmem(s, strlen(s), pat, l)))
		memset(p, '*', l), s = p + l;
}

int main(int ac, char **av)
{
	char *s;
	int len;

	if (ac != 2 || !*av[1])
		return 1;
	if (!(s = read_all(&len)))
		return perror("Error"), 1;
	filter(s, av[1]);
	write(1, s, len);
	free(s);
}
