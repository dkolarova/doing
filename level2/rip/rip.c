#include <unistd.h>

int min_removed(char *s)
{
	int open = 0, rm = 0;

	while (*s)
	{
		if (*s == ')')
			open++;
		else if (*s == '(')
			open ? open-- : rm++;
		s++;
	}
	return (open + rm);
}

void solve(char *str, int i, int open, int close, int removed, int min, char *buf)
{
	if (!str[i])
	{
		if (open == close && removed == min)
		{
			write(1, buf, i);
			write(1, "\n", 1);
		}
		return ;
	}
	
	buf[i] = str[i];

	if(str[i] == '(')
		solve(str, i + 1, open + 1, close, removed, min, buf);
	else if (str[i] == ')')
	{
		if (open > close)
			solve(str, i + 1, open, close + 1, removed, min, buf);
	}
	else
		solve(str, i + 1, open, close, removed, min, buf);

	if (str[i] == '(' || str[i] == ')')
	{
		buf[i] = ' ';
		solve(str, i + 1, open, close, removed + 1, min, buf);
	}
}

int main(int ac, char **av)
{
	char buf[256];

	if (ac == 2)
		solve(av[1], 0, 0, 0, 0, min_removed(av[1]), buf);
	return 0;
}