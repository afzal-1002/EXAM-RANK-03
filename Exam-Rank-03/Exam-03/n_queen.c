#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>

int ft_abs(int n)
{
    if(n < 0)
        return(-n);
    return(n);    
}

void put_number(int n)
{
    char c;

    if (n >= 10)
        put_number(n / 10);

    c = (n % 10) + '0';
    write(1, &c, 1);
}

void print_queen(int pos[], int size)
{
    int i = 0;
    char chr;

    while (i < size)
    {
        put_number(pos[i]);
        write(1, &chr, 1);
        if (i + 1 < size)
            write(1, " ", 1);
        i++;
    }
     write(1, "\n", 1);
}


int is_safe(int pos[], int col, int row)
{

   int q = 0;
   
   while (q < col)
   {
        if (pos[q] == row)
                return (0);
            
         if (ft_abs(pos[q] - row) == ft_abs(q-col))
            return (0);
                       
        q++;
   }

   return(1);
   

}


void solve(int pos[], int col, int size)
{
    if (col == size)
    {
        print_queen(pos, size);
        return;
    }

    int row = 0;
    while (row < size)
    {
        if(is_safe(pos, col, row))
        {
            pos[col] = row;
            solve(pos, col +1, size);

        }
        row++;
    }
}




int main(int argc, char **argv)
{

    int	*pos;

    int size = atoi(argv[1]);
    if (size <= 0)
        return (0);
    pos = (int *)malloc(sizeof(int) * size);
    if (!pos)
        return (1);
    solve(pos, 0, size);
    return (0);
}