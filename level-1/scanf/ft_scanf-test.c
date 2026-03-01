#include <stdarg.h>
#include <stdio.h>
#include <ctype.h>

int match_space(FILE *f)
{
    int c;
	while ((c = fgetc(f)) != EOF)
	{
		if (!isspace(c))
		{
			ungetc(c, f);
			return 0;
		}
	}
	if (ferror(f))
	{
		return -1;
	}
    return (0);
}

int match_char(FILE *f, char c)
{
    int to_compare = fgetc(f);
	if (to_compare == EOF)
	{
		if (ferror(f))
		{
			return -1;
		}
		return 0;
	}
	if (to_compare == c)
	{
		return 1;
	}
	else
	{
		ungetc(c, f);
		return (0);
	}
}

int scan_char(FILE *f, va_list ap)
{
    int c = fgetc(f);
	if (c == EOF)
	{
		if (ferror(f))
		{
			return -1;
		}
		return 0;
	}
	char *ptr = va_arg(ap, char *);
	*ptr = (char)c;
    return (1);
}

int scan_int(FILE *f, va_list ap)
{
    int c = fgetc(f);
	if (c == EOF)
	{
		if (ferror(f))
		{
			return -1;
		}
		return 0;
	}

	int sign = 1;
	if (c == '-' || c == '+')
	{
		if (c == '-')
		{
			sign = -1;
		}
	}
	else
	{
		ungetc(c, f);
	}

	int value = 0;
	int digits_read = 0;
	while ((c = fgetc(f)) != EOF)
	{
		if (isdigit(c))
		{
			value = value * 10 + (c - '0');
			digits_read++;
		}
		else
		{
			ungetc(c, f);
			break;
		}
	}

	if (ferror(f))
	{
		return -1;
	}

	if (digits_read == 0)
	{
		return -1;
	}

	int *ptr = va_arg(ap, int *);
	*ptr = value * sign;

    return (1);
}

int scan_string(FILE *f, va_list ap)
{
	int c = fgetc(f);
	if (c == EOF)
	{
		if (ferror(f))
		{
			return -1;
		}
		return 0;
	}
	ungetc(c, f);

	char *s = va_arg(ap, char *);
	int char_read = 0;
	while ((c = fgetc(f)) != EOF)
	{
		if (isspace(c))
		{
			ungetc(c, f);
			break ;
		}
		*s = (char)c;
		s++;
		char_read++;
	}

	if (ferror(f))
	{
		return -1;
	}

	if (!char_read)
	{
		return -0;
	}

	*s = '\0';
    return (1);
}


int	match_conv(FILE *f, const char **format, va_list ap)
{
	switch (**format)
	{
		case 'c':
			return scan_char(f, ap);
		case 'd':
			match_space(f);
			return scan_int(f, ap);
		case 's':
			match_space(f);
			return scan_string(f, ap);
		case EOF:
			return -1;
		default:
			return -1;
	}
}

int ft_vfscanf(FILE *f, const char *format, va_list ap)
{
	int nconv = 0;

	int c = fgetc(f);
	if (c == EOF)
		return EOF;
	ungetc(c, f);

	while (*format)
	{
		if (*format == '%')
		{
			format++;
			if (match_conv(f, &format, ap) != 1)
				break;
			else
				nconv++;
		}
		else if (isspace(*format))
		{
			if (match_space(f) == -1)
				break;
		}
		else if (match_char(f, *format) != 1)
			break;
		format++;
	}
	
	if (ferror(f))
		return EOF;
	return nconv;
}


int ft_scanf(const char *format, ...)
{
	va_list ap;
	va_start(ap, format);
	int ret = ft_vfscanf(stdin, format, ap);
	va_end(ap);
	return ret;
}

int main()
{
	int number;
	char c;
	char str[500];

	ft_scanf("%d %c %s", &number, &c, &str);
	//scanf("%d %c %s", &number, &c, str);
	printf("The number you entered: %d\n", number);
	printf("The c you entered: %c\n", c);
	printf("The str you entered: %s\n", str);

}