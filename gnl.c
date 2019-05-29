#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>


# define BUFF_SIZE 67

/*These ARE FUNCTIONS USED FOR the function that I want to create and DEBUGGING, the code starts from line 133*/


void	ft_putstr(char const *s)
{
	if (s)
		write(1, s, strlen(s));
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

char *ft_strnew(size_t size)
{
	char *s;
	size_t i;

	i = 0;
	if (!(s = (char *)malloc(sizeof(char) * (1 + size))))
		return (NULL);
	bzero((char *)s, size + 1);
	return (s);
}

void	ft_putnbr(int n)
{
	char	c;
	int		i;

	i = 0;
	if (n == -2147483648)
	{
		write(1, "-2147483648", 11);
		return ;
	}
	if (n < 0)
	{
		i = -n;
		write(1, "-", 1);
		ft_putnbr(i);
		return ;
	}
	if (n < 10)
	{
		c = (n % 10) + '0';
		write(1, &c, 1);
		return ;
	}
	c = (n % 10) + '0';
	ft_putnbr(n / 10);
	write(1, &c, 1);
}

void ft_memdel(void **ap)
{
	if (ap == NULL)
		return ;
	free(*ap);
	*ap = NULL;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*dest;
	unsigned long	i;
	unsigned long	j;

	i = 0;
	j = 0;
	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(dest = (char *)malloc(sizeof(char) * (strlen(s1)
			+ strlen(s2) + 1))))
		return (NULL);
	while (*s1 != '\0')
	{
		dest[i] = *s1++;
		i++;
	}
	while (*s2 != '\0')
	{
		dest[i] = *s2++;
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char			*ft_strdupcharset(char *s, char c)
{
	size_t		i;
	size_t		j;
	char		*tab;

	i = 0;
	j = 0;
	if (s == NULL)
		return (NULL);
	while (s[i] != c && s[i] != '\0')
		i++;
	if (!(tab = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	while (j < i)
	{
		tab[j] = s[j];
		j++;
	}
	tab[j] = '\0';
	return (tab);
}

static int      ft_index(const char *s, char n)
{
	int	i;

	i = 0;
	while (s[i] != n && s[i])
		i++;
	return (i);
}


/*IT STARTS FROM HERE*/


static  char    *ft_createline(char *static_buf, char *buf)
{
    char *tmp;

    if (!(tmp = ft_strjoin(static_buf, buf)))
        return (NULL);
    ft_putstr(tmp);
    //ft_putchar('\n');
    ft_putstr("tmp within createline\n");
    ft_memdel((void **)&static_buf);
    return (tmp);
}


static  int     ft_returnval(char *static_buf, int nread)
{
    char *tmp;

    tmp = NULL;
    if ((int) ft_index(static_buf, '\n') == (int) strlen(static_buf))
    {
        ft_memdel((void **)&static_buf);
        if (nread == 0)
            return (0);
    }
    else  
    {
        if(!(tmp = strdup(&static_buf[ft_index(static_buf, '\n') + 1])))
            return (-1);
        ft_putstr(tmp);
        ft_putstr("tmp within returnval\n");
        ft_memdel((void **)&static_buf);
        static_buf = strdup(tmp);
        ft_putstr(static_buf);
        ft_putstr("static buf within returnval\n");
        ft_memdel((void **)&tmp);
    }
    return (1);
}

int             get_next_line(int const fd, char **line)
{
    char                buf[BUFF_SIZE + 1];
    int                 nread;
    static  char        *static_buf;
    static int  i = 0;
    static int j = 0;
    //char                *tmp;
	if (line == NULL || BUFF_SIZE <= 0 || fd < 0)
		return (-1);
    if (static_buf == NULL)
        static_buf = ft_strnew(0);
     ft_putstr(static_buf);
     ft_putstr("static buf after ft_strnew\n");
     j++;
    while ((strchr(static_buf, '\n') == NULL)
            && ((nread = read(fd, &buf, BUFF_SIZE)) > 0))
    {
        buf[nread] = '\0';
        write(1,"yo\n",3);
        static_buf = ft_createline(static_buf, buf);
    }
    ft_putstr(static_buf);
    ft_putchar('\n');
    i++;
    ft_putnbr(i);
    ft_putstr("static buf\n");
    // ici il y a un probleme à la fin
    *line = ft_strdupcharset(static_buf, '\n');
    if (ft_returnval(static_buf, nread) == 1)
    {
        ft_putstr(static_buf);
        ft_putstr("here static_buf doesn't clear itself after the first \\n once it leaves ft_returnval\n");
        return (1);
    }
    ft_putstr(static_buf);
    ft_putstr("static buf after ft_returnval\n");
    
    //return (1);
    return (0);
}


int     main(int argc, char **argv)
{
    int        fd;
    char    *line;
    int i = 0;
    if (argc != 2)
        return (0);
    fd = open(argv[1], O_RDONLY);
    while (get_next_line(fd, &line) > 0)
    {
        ft_putstr(line);
        ft_putchar('\n');
        ft_putstr("printed line\n");
        free(line);
        i++;
    }
    close(fd);
    return (0);
}
