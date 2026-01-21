#include "get_next_line.h"

char *apend_char(char *s, int len, char c)
{
	char *new = malloc(len + 2);
	if (!new)
		return free(s), NULL;
	
	int i = 0;
	while (i < len)
	{
		new[i] = s[i];
		i++;
	}
	new[len] = c;
	new[len + 1] = '\0';
	free(s);
	return new;
}

char *get_next_line(int fd)
{
	static char buf[BUFFER_SIZE];
	static int i = 0, r = 0;
	char *line = NULL;
	int len = 0;

	while(1)
	{
		if (i >= r)
		{
			r = read(fd, buf, BUFFER_SIZE);
			i = 0;
			if (r <= 0)
				return line;
		}
		line = apend_char(line, len++, buf[i++]);
		if (!line || line[len - 1] == '\n')
			return line;
	}
}

#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line;

	while((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
	}
}