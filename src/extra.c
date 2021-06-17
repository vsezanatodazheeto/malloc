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

void	write_char(char ch)
{
	write(1, &ch, 1);
}

char	hex_digit(int v)
{
    if (v >= 0 && v < 10)
        return ('0' + v);
    else
        return ('a' + v - 10);
}

void	print_address_hex(void *p0)
{
    int i;
    uintptr_t p = (uintptr_t)p0;

    write_char('0');
	write_char('x');
    for (i = (sizeof(p) << 3); i >= 0; i -=  4)
        write_char(hex_digit((p >> i) & 0xf));
}