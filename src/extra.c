#include "../include/malloc.h"

int					ft_numlen(long long value, int base)
{
	int				i;
	int				neg;

	if (base < 2 || base > 16)
		return (0);
	i = 0;
	neg = 0;
	if (value == 0)
		return (1);
	if (value < 0)
		neg = 1;
	while (value)
	{
		value /= base;
		i++;
	}
	return (i + neg);
}

int					ft_unumlen(size_t value, int base)
{
	int				i;
	int				neg;

	if (base < 2 || base > 16)
		return (0);
	i = 0;
	neg = 0;
	if (value == 0)
		return (1);
	if (value < 0)
		neg = 1;
	while (value)
	{
		value /= base;
		i++;
	}
	return (i + neg);
}

char				*ft_uitoa_base(size_t unval, int base)
{
	int					num_len;
	char				*string;

	if (base < 2 || base > 16)
		return (NULL);
	num_len = ft_unumlen(unval, base);
	if (!(string = (char *)malloc(sizeof(char) * (num_len + 1))))
		return (NULL);
	string[num_len] = '\0';
	while (--num_len >= 0)
	{
		string[num_len] = (unval % base < 10) ? unval % base + '0' : unval % base + 'A' - 10;
		unval /= base;
	}
	return (string);
}

char				*ft_itoa_base(long long val, int base)
{
	unsigned long long	unval;
	int					is_neg;
	int					num_len;
	char				*string;

	if (base < 2 || base > 16)
		return (NULL);
	is_neg = (val < 0 && base == 10) ? 1 : 0;
	unval = (val < 0) ? val * (long long)-1 : val;
	num_len = is_neg + ft_numlen(unval, base);
	if (!(string = (char *)malloc(sizeof(char) * (num_len + 1))))
		return (NULL);
	string[num_len] = '\0';
	while (--num_len >= 0)
	{
		string[num_len] = (unval % base < 10) ? unval % base + '0' : unval % base + 'A' - 10;
		unval /= base;
	}
	if (is_neg)
		string[0] = '-';
	return (string);
}
