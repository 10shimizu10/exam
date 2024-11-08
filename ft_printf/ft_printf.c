#include <stdarg.h>
#include <unistd.h>

int putstr(char* s, int count)
{
    int i = 0;

    if(!s)
        s = "(null)";
    while(s[i])
    {
        write(1, &s[i], 1);
        i++;
        count++;
    }
    return count;
}

int putnum(long n, int count)
{
    char *b = "0123456789";
    if(n < 0)
    {   
        write(1, "-", 1);
        count++;
        n = -n;
    }
    if(n >= 10)
        count = putnum(n/10, count);
    write(1, &b[n%10], 1);
    count++;
    return count;
}

int puthex(unsigned int n, int count)
{
    char* b = "0123456789abcdef";
    if(n >= 16)
        count = puthex(n/16, count);
    write(1, &b[n%16], 1);
    count++;
    return count;
}


int ft_printf(const char * f, ... )
{
    va_list args;
    int count = 0;
    int i = 0;
    va_start(args, f);

    while(f[i])
    {
        if(f[i] == '%' && f[i+1])
        {
            i++;
            if(f[i] == 's')
                count = putstr(va_arg(args, char*), count);
            else if(f[i] == 'd')
                count = putnum(va_arg(args, long), count);
            else if(f[i] == 'x')
                count = puthex(va_arg(args, unsigned int), count);
            else
                {
                    write(1, &f[i], 1);
                    count++;
                }
        }
        else
        {
            write(1, &f[i], 1);
            count++;
        }
        i++;
    }
    va_end(args);
    return count;
}

// int main()
// {
//     char* s = "abcdedf";
//     ft_printf("%d", ft_printf("%s", s));
// }