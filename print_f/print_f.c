
#include <stdio.h>
#include <stdarg.h>
#include <unistd.h>

void ft_putchar(char c);
void ft_putstr(const char *s);
void ft_putnbr(int n);
void ft_puthex(unsigned int n);
void ft_putptr(void *ptr);



int ft_printf(const char *format, ... )
{
    va_list args;
    char *ptr;
    char c;
    int d, i;
    char *s;

    va_start(args, format);
    ptr = (char *)format;
    while (*ptr) {
        if (*ptr == '%') {
            ptr++;
            if (*ptr == 'c') {
                c = va_arg(args, int);
                ft_putchar(c);
            } else if (*ptr == 's') {
                s = va_arg(args, char *);
                ft_putstr(s);
            } else if (*ptr == 'd') {
                d = va_arg(args, int);
                ft_putnbr(d);
            } else if (*ptr == 'i') {
                i = va_arg(args, int);
                ft_putnbr(i);
            } else if (*ptr == 'x') {
                d = va_arg(args, int);
                ft_puthex(d);
            } else if (*ptr == 'p') {
                void *ptr = va_arg(args, void *);
                ft_putptr(ptr);
            }   else {
                ft_putstr("Unsupported format specifier");
            }
        } else {
            ft_putchar(*ptr);
        }
        ptr++;
    }   

    va_end(args);
}

void ft_putchar(char c) {
    write(1, &c, 1);
}

void ft_putstr(const char *s) {
    while (*s) {
        write(1, s, 1);
        s++;
    }
}   

void ft_putnbr(int n) {
    char *base = "0123456789";
    if (n < 0) {
        ft_putchar('-');
        n = -n;
    }
    if (n >= 10) {
        ft_putnbr(n / 10);
    }
    ft_putchar(base[n % 10]);
}

void ft_puthex(unsigned int n) {
    char *base = "0123456789abcdef";
    if (n >= 16) {
        ft_puthex(n / 16);
    }
    ft_putchar(base[n % 16]);
}   

void ft_putptr(void *ptr) {
    unsigned long n = (unsigned long)ptr;
    ft_putstr("0x");
    ft_puthex(n);
}


int main(int argc, char **argv) {
    ft_printf("Hello world!\n My name is %s and I am %d years old.\n", "Alice", 30);
    return 0;
}