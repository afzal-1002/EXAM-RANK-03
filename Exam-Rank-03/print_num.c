#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

void put_char(int n)
{
    char num = n + '0';
    write(1, &num, 1);
    write(1, "\n", 1);

}

void print_num(int num)
{
    if (num <= 0 )
        return;
    put_char(num);
    print_num(num -1);
    
}


int main(int argc, char **argv)
{
    int num = atoi(argv[1]);
    print_num(num);
    return (1);
}