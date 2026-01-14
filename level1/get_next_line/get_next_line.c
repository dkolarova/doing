#include "get_next_line.h"

char *append_char(char *s, int len, char c)
{
	char *new = malloc(len + 2);
	int i = 0;

	if (!new)
		return free(s), NULL;
	while (i < len)
	{
		new[i] = s[i];
		i++;
	}
	new[len] = c;
	new[len + 1] = 0;
	free(s);
	return new;
}

char *get_next_line(int fd)
{
	static char buf[BUFFER_SIZE];
	static int pos = 0, readed = 0;
	char *line = NULL;
	int len = 0;

	while (1)
	{
		if (pos >= readed)
		{
			readed = read(fd, buf, BUFFER_SIZE);
			if (readed <= 0)
				return line;
			pos = 0;
		}
		line = append_char(line, len++, buf[pos++]);
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

	if (fd < 0)
	{
		perror("Error");
		return (1);
	}
	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}


