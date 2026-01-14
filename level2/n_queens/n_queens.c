#include <stdio.h>
#include <stdlib.h>

int safe(int *board, int col, int row)
{
	int i, diff;

	for (i = 0; i < col; i++)
	{
		if (board[i] == row)
			return 0;
		diff = board[i] - row;
		if (diff < 0)
			diff = -diff;
		if (diff == col - i)
			return 0;
	}
	return 1;
}

void solve(int *board, int col, int n)
{
	int row, i;

	if (col == n)
	{
		for (i = 0; i < n; i++)
		{
			fprintf(stdout, "%d", board[i]);
			if (i + 1 < n)
				fprintf(stdout," ");
		}
		fprintf(stdout, "\n");
		return;
	}
	for (row = 0; row < n; row++)
	{
		if (safe(board, col, row))
		{
			board[col] = row;
			solve(board, col + 1, n);
		}
	}
}

int main(int ac, char **av)
{
	int n, *board;

	if (ac != 2)
		return 1;
	n = atoi(av[1]);
	if (n <= 0)
		return 1;
	board = malloc(sizeof(int) * n);
	if (!board)
		return 1;
	solve(board, 0, n);
	free(board);
	return 0;
}