#include <unistd.h>
#include <string.h>

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 42
#endif

void ft_filter(char *s, char *f)
{
	int i = 0, j, len = strlen(f);

	while(s[i])
	{
		j = 0;
		while (f[j] && s[i + j] == f[j])
			j++;
		if (j == len)
			while (j--) write(1, "*", 1), i++;
		else
			write(1, &s[i++], 1);
	}
}

int main(int ac, char **av)
{
	char buf[9999];
	int i = 0, n;

	if (!ac || !av[1][0])
		return 1;
	while ((n = read(0, buf + i, BUFFER_SIZE)) > 0)
		i += n;
	buf[i] = 0;
	ft_filter(buf, av[1]);
}