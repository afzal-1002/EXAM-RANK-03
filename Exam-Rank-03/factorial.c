#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void print_num(int num)
{
    if (num == 0)
        return;

    print_num(num - 1);
    printf("%d ", num);
}

int factorial(int num)
{
    if (num == 0) 
        return 1;
    
    return num * factorial(num-1); 

}

int main(int argc, char **argv)
{
    int num = atoi(argv[1]);
     num = factorial(num);

    printf("%d\n", num);

    print_num(num);


    return (0);

}