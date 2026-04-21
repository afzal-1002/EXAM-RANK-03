#include <unistd.h>
#include <stdlib.h>

int	ft_abs(int n)
{
    if (n < 0)
        return (-n);
    return (n);
}

void	print_solution(int pos[], int n)
{
    int		i;
    char	c;

    i = 0;
    while (i < n)
    {
        c = pos[i] + '0';
        write(1, &c, 1);
        if (i + 1 < n)
            write(1, " ", 1);
        i++;
    }
    write(1, "\n", 1);
}

int	is_safe(int pos[], int col, int row)
{
    int	c;

    c = 0;
    while (c < col)
    {
        if (pos[c] == row)
            return (0);
        if (ft_abs(pos[c] - row) == ft_abs(c - col))
            return (0);
        c++;
    }
    return (1);
}

void solve(int pos[], int col, int size)
{
    int row;

    if (col == size)
    {
        print_solution(pos, size);
        return;
    }
    row = 0;
    while (row < size)
    {
        if (is_safe(pos, col, row))
        {
            pos[col] = row;
            solve(pos, col + 1, size);
        }
        row++;
    }
}

int	main(int ac, char **av)
{
    int	*pos;
    int	n;

    if (ac != 2)
        return (1);
    n = atoi(av[1]);
    if (n <= 0)
        return (0);
    pos = (int *)malloc(sizeof(int) * n);
    if (!pos)
        return (1);
    solve(pos, 0, n);
    free(pos);
    return (0);
}