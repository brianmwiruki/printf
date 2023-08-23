#include "main.h"

/****** PRINT POINTER ********/
/**
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * _print_pointer - Print the value of a pointer variable
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
* @types: List a of arguments
 * Return: Num of chars printed.
 */

int print_pointer(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char extra_char = 0, padd = ' ';
	int ind = BUFF_SIZE - 2, length = 2, padd_start = 1; /* length=2, for '0x' */
	unsigned long num_addrs;
	char map_to[] = "0123456789abcdef";
	void *addrs = va_arg(types, void *);

	UNUSED(size);
    UNUSED(width);

	if (addrs == NULL)
		return (write(1, "(nil)", 5));

	buffer[BUFF_SIZE - 1] = '\0';
	UNUSED(precision);

	num_addrs = (unsigned long)addrs;

	while (num_addrs > 0)
	{
		buffer[ind--] = map_to[num_addrs % 16];
		num_addrs /= 16;
		length++;
	}

	if ((flags & F_ZERO) && !(flags & F_MINUS))
		padd = '0';
	if (flags & F_PLUS)
		extra_char = '+', length++;
	else if (flags & F_SPACE)
		extra_char = ' ', length++;

	ind++;

	return (write_pointer(buffer, ind, length,
		width, flags, padd, extra_char, padd_start));
}

/****** PRINT NON PRINTABLE ********/
/**
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * -print_non_printable - Print ascii codes in hexa of non printable chars
 * @types: Lista of arguments
 * @flags:  Calculates active flags
 * @buffer: Buffer array to handle print
 * Return: Number of chars printed
 */

int print_non_printable(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = 0, offset = 0;
	char *str = va_arg(types, char *);

	UNUSED(precision);
    UNUSED(flags);
    UNUSED(size);
	UNUSED(width);
	
	if (str == NULL)
		return (write(1, "(null)", 6));

	while (str[i] != '\0')
	{
		if (is_printable(str[i]))
			buffer[i + offset] = str[i];
		else
			offset += append_hexa_code(str[i], buffer, i + offset);

		i++;
	}

	buffer[i + offset] = '\0';

	return (write(1, buffer, i + offset));
}

/********* PRINT REVERSE ***********/
/**
 * print_reverse - Print reverse string.
 * Return: Number of chars printed
* @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 */


int print_reverse(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char *str;
	int i, count = 0;

	UNUSED(flags);
	UNUSED(width);
    UNUSED(size);
    UNUSED(buffer);

	str = va_arg(types, char *);

	if (str == NULL)
	{
		UNUSED(precision);

		str = ")Null(";
	}
	for (i = 0; str[i]; i++)
		;

	for (i = i - 1; i >= 0; i--)
	{
		char z = str[i];

		write(1, &z, 1);
		count++;
	}
	return (count);
}
/****** PRINT A STRING IN ROT13 ************/
/**
 * @width: get width
 * @precision: Precision specification
 * @size: Size specifier
 * -print_rot13string - Print a string in rot13.
 * @types: Lista of arguments
* @flags:  Calculates active flags
 * @buffer: Buffer array to handle print
 * Return: Numbers of chars printed
 */

int print_rot13string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	char x;
	char *str;
	unsigned int i, j;
	int count = 0;
	char in[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
	char out[] = "NOPQRSTUVWXYZABCDEFGHIJKLMnopqrstuvwxyzabcdefghijklm";

	str = va_arg(types, char *);
    UNUSED(width);
	UNUSED(precision);
	UNUSED(buffer);
    UNUSED(size);
	UNUSED(flags);

	if (str == NULL)
		str = "(AHYY)";
	for (i = 0; str[i]; i++)
	{
		for (j = 0; in[j]; j++)
		{
			if (in[j] == str[i])
			{
				x = out[j];
				write(1, &x, 1);
				count++;
				break;
			}
		}
		if (!in[j])
		{
			x = str[i];
			write(1, &x, 1);
			count++;
		}
	}
	return (count);
}
