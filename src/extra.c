#include "../include/malloc.h"

void	error_malloc(void *ptr, char *msg, size_t msg_size)
{
	if (ptr && msg)
	{
		write(2, E_ERR, sizeof(E_ERR) - 1);
		print_address_hex(2, ptr);
		write(2, msg, msg_size);
	}
	else if (!ptr && msg)
	{
		write(2, E_ERR, sizeof(E_ERR) - 1);
		write(2, msg, msg_size);
	}
}

void	*ft_memset(void *s, int c, size_t len)
{
	char	*tmp;
	size_t	i;

	i = 0;
	tmp = (char *)s;
	while (i < len)
	{
		tmp[i] = c;
		i++;
	}
	return (s);
}

void	*ft_memcpy(void *dest, const void *source, size_t size)
{
	char	*dest_copy;
	char	*source_copy;

	if (!size || dest == source)
		return (NULL);
	dest_copy = (char *)dest;
	source_copy = (char *)source;
	while (size)
	{
		*dest_copy = *source_copy;
		dest_copy++;
		source_copy++;
		size--;
	}
	return (dest);
}

static char	hex_digit(int v)
{
	if (v >= 0 && v < 10)
		return ('0' + v);
	else
		return ('a' + v - 10);
}

void	print_num(int fd, long n)
{
	unsigned long	un;
	char			c;

	if (fd < 0)
		return ;
	if (n < 0)
	{
		write(fd, "-", 1);
		un = -n;
	}
	else
		un = n;
	if (un > 9)
		print_num(fd, un / 10);
	c = un % 10 + '0';
	write(fd, &c, 1);
}

void	print_address_hex(int fd, void *p0)
{
	uintptr_t	p = (uintptr_t)p0;
	int			i, flag = 0;
	char		ch;

	if (fd < 0)
		return ;
	write(fd, "0x", 2);
	for (i = (sizeof(p) << 3) - 4; i >= 0; i -= 4)
	{
		if ('0' < (ch = hex_digit((p >> i) & 0xf)))
			flag = 1;
		if (flag)
			write(fd, &ch, 1);
	}
	if (!flag)
		write(fd, &ch, 1);
}
