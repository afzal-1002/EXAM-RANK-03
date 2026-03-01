/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_correct.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvlasov <vlasov.andrii@gmail.com>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/27 17:34:32 by anvlasov          #+#    #+#             */
/*   Updated: 2026/01/28 15:07:35 by anvlasov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#define BUFF_SIZE 1000

int get_char(int fd)
{
    unsigned char   c;
    static char     buffer[BUFF_SIZE];
    static int      buff_len = 0;
    static int      current_pos = 0;

    if (current_pos >= buff_len)
    {
        buff_len = read(fd, buffer, BUFF_SIZE);
        current_pos = 0;
        if (buff_len <= 0)
            return (EOF);
    }
    c = buffer[current_pos];
    current_pos++;
    return (c);
}
// line- where to copy
// ind - how many chars to copy
// mega_buff - from where to copy
char    *malloc_n_copy(char *line, int ind, char *mega_buff)
{
    int i;

    line = malloc(ind + 1);
    if (!line)
        return (NULL);
    i = 0;
    while (i < ind)
    {
        line[i] = mega_buff[i];
        i++;
    }
    line[ind] = 0;
    return (line);
}

char    *get_nl(int fd)
{
    static char mega_buff[10024];
    char        *line;
    char        c;
    int         ind;

    ind = 0;
    c = get_char(fd);
    while (c != EOF)
    {
        mega_buff[ind] = (char)c;
        ind++;
        if (c == '\n')
            break ;
        c = get_char(fd);
    }
    line = malloc_n_copy(line, ind, mega_buff);
    return (line);
}

int main(void)
{
    int fd;
    fd = open("./gnl.c", O_RDONLY);
    int c;
    char *line;
    /* c = get_char(fd);
    while (c != EOF)
    {
        printf("%c", c);
        c = get_char(fd);
    } */
    int i = 0;
    while (i < 500)
    {
        line = get_nl(fd);
        printf("%s", line);
        free (line);
        i++;
    }
    return (0);