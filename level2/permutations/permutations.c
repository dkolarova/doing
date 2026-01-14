#include <unistd.h>
#include <stdio.h>

void putstr(char *s)
{
	while (*s)
		write(1, s++, 1);
	write(1, "\n", 1);
}

int ft_strlen(char *s)
{
	int i = 0;

	while (s[i])
		i++;
	return i;
}

void swap(char *a, char *b)
{
	char tmp = *a;
	*a = *b;
	*b = tmp;
}

void sort(char *s)
{
	int i, j;

	for (i = 0; s[i]; i++)
		for (j = i + 1; s[j]; j++)
			if (s[i] > s[j])
				swap(&s[i], &s[j]);
}

void reverse(char *s, int start)
{
	int i = start;
	int j = ft_strlen(s) - 1;

	while (i < j)
		swap(&s[i++], &s[j--]);
}

int next_permutation(char *s)
{
	int i = ft_strlen(s) - 2;
	int j;

	while (i >= 0 && s[i] >= s[i + 1])
		i--;
	if (i < 0)
		return 0;
	j = ft_strlen(s) - 1;
	while (s[j] <= s[i])
		j--;
	swap(&s[i], &s[j]);
	reverse(s, i + 1);
	return 1;
}

int main(int argc, char **argv)
{
	char *s;

	if (argc != 2)
		return 1;
	s = argv[1];
	sort(s);
	putstr(s);
	while (next_permutation(s))
		putstr(s);
}