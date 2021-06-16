#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <unistd.h>

// int	ft_numlen(size_t value, int base)
// {
// 	int	i;
// 	int	neg;

// 	if (base < 2 || base > 16 || base % 2)
// 		return (0);
// 	i = 0;
// 	neg = 0;
// 	if (value == 0)
// 		return (1);
// 	if (value < 0)
// 		neg = 1;
// 	while (value)
// 	{
// 		value /= base;
// 		i++;
// 	}
// 	return (i + neg);
// }

// char	*ft_utoa_base(intptr_t val, int base)
// {
// 	int				neg;
// 	int				len;
// 	unsigned int	unv;
// 	char			*tmp;

// 	if (base < 2 || base > 16 || base % 2 != 0)
// 		return (NULL);
// 	unv = 0;
// 	neg = (val < 0 && base == 10) ? 1 : 0;
// 	unv = (val < 0) ? val * -1 : val;
// 	len = neg + ft_numlen(unv, base);
// 	if (!(tmp = (char *)malloc(sizeof(char) * (len + 1))))
// 		return (NULL);
// 	tmp[len] = '\0';
// 	while (--len >= 0)
// 	{
// 		tmp[len] = (unv % base < 10) ? unv % base + '0' : unv % base + 'a' - 10;
// 		write(1, &tmp[len], 1);
// 		unv /= base;
// 	}
// 	if (neg)
// 		tmp[0] = '-';
// 	return (tmp);
// }


/* you must provide this function somewhere */
extern void write_char(char);

void write_char(char ch)
{
	write(1, &ch, 1);

}

char hex_digit(int v) {
    if (v >= 0 && v < 10)
        return '0' + v;
    else
        return 'a' + v - 10; // <-- Here
}

void print_address_hex(void* p0) {
    int i;
    uintptr_t p = (uintptr_t)p0;

    write_char('0');
	write_char('x');
    for(i = (sizeof(p) << 3) - 4; i>=0; i -= 4) {
        write_char(hex_digit((p >> i) & 0xf));
    }
}

int main()
{
	void *p = malloc(100);
	print_address_hex(p);
	printf("\n%p\n", p);
}