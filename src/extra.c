#include "malloc.h"

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

static void	print_address_hex(void *p0)
{
	uintptr_t	p;
	int			i, flag;
	char		ch;

	p = (uintptr_t)p0;
	flag = 0;
	write(2, "0", 1);
	write(2, "x", 1);
	for (i = (sizeof(p) << 3) - 4; i >= 0; i -= 4)
	{
		if ('0' < (ch = hex_digit((p >> i) & 0xf)))
			flag = 1;
		if (flag)
			write(2, &ch, 1);
	}
	if (!flag)
		write(2, &ch, 1);
}

void	error_malloc(void *ptr, char *msg, size_t msg_size)
{
	if (ptr && msg)
	{
		write(2, E_ERR_AT, sizeof(E_ERR_AT) - 1);
		print_address_hex(ptr);
		write(2, msg, msg_size);
	}
	else if (!ptr && msg)
	{
		write(2, E_ERR, sizeof(E_ERR) - 1);
		print_address_hex(ptr);
		write(2, msg, msg_size);
	}
}
