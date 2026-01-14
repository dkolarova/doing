#include "get_next_line.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t i = 0;
	while (i < n)
	{
		((char *)dest)[i] = ((char *)src)[i];
		i++;
	}
	return (dest);
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	static int	buffer_pos = 0;
	static int	buffer_read = 0;
	char		*line = NULL;
	int			len = 0;

	while (1)
	{
		if (buffer_pos >= buffer_read)
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			if (buffer_read <= 0)
				return (line);
			buffer_pos = 0;
		}
		char c = buffer[buffer_pos++];
		char *new_line = malloc(len + 2);
		if (!new_line)
		{
			free(line);
			return (NULL);
		}
		if (line)
		{
			ft_memcpy(new_line, line, len);
			free (line);
		}
		new_line[len] = c;
		new_line[len + 1] = '\0';
		line = new_line;
		len++;
		if (c == '\0')
			return (line);
	}
}

#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *line;

	while ((line = get_next_line(fd)) != NULL)
	{
		printf("%s", line);
		free(line);
	}
}