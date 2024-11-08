#include "get_next_line.h"

char* ft_stddup(char* src)
{
    char* dest;
    int i = 0;

    while(src[i])
        i++;
    dest = (char*)malloc(sizeof(char) * (i + 1));
    i = 0;
    while(src[i])
    {
        dest[i] = src[i];
        i++;
    }
    return dest;
}

char* get_next_line(int fd)
{
    static char buffer[BUFFER_SIZE];
    static int buffer_read;
    static int buffer_pos;
    int i = 0;
    char line[70000];

    if(fd < 0 || BUFFER_SIZE <= 0)
        return NULL;
    while(1)
    {
        if(buffer_pos >= buffer_read)
        {
            buffer_read = read(fd, buffer, BUFFER_SIZE);
            buffer_pos = 0;
            if (buffer_read <= 0)
                break;
        }
        if(line[i] == '\n')
            break;
        line[i] = buffer[buffer_pos];
        i++;
        buffer_pos++;
    }
    line[i] = '\0';
    if(i == 0)
        return NULL;
    return ft_stddup(line);
}

// #include <stdio.h>
// int main()
// {
//     printf("%s", get_next_line(0));
// }