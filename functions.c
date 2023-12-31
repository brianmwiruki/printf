
#include "main.h"

/******* -pRINT CHARACT *******/
/**
 * print_char - print a character
 * @precision: Precision specification
 * @size: Size specifier
 * @buffer: Buffer array to handle print
 * @flags:  Calculates active flags
 * @types: List a of arguments
 * @width: Width
 * Return: No. of characters printed
 */

int print_char(va_list types, char buffer[], int width,
	int flags,int precision, int size)
{
	char Z = va_arg(types, int);

	return (handle_write_char(Z, buffer, flags, width, precision, size));
}

/******* PRIN A STR *******/
/**
 * print_string - print a str
 * @flags:  Calculates active flags
 * @width: get width.
 * @precision: Precision specification
 * @size: Size specifier
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * Return: No. of characters printed
 */

int print_string(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int length = 0, i;
	char *str = va_arg(types, char *);

	UNUSED(flags);
    UNUSED(buffer);
    UNUSED(precision);
	UNUSED(size);
	UNUSED(width);
	
	if (str == NULL)
	{
		str = "(null)";

		if (precision >= 6)
			str = "      ";
	}

	while (str[length] != '\0')
		length++;

	if (precision >= 0 && precision < length)
		length = precision;

	if (width > length)
	{
		if (flags & F_MINUS)
		{
			write(1, &str[0], length);
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			return (width);
		}
		else
		{
			for (i = width - length; i > 0; i--)
				write(1, " ", 1);
			write(1, &str[0], length);
			return (width);
		}
	}

	return (write(1, str, length));
}

/******* PRINT % *******/
/**
 * print_percent - Prints a percent sign
 * @precision: Precision specification
 * @size: Size specifier
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
* @width: get width.
 * @flags:  Calculates active flags
 * Return: No. of chars printed
 */

int print_percent(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
    UNUSED(precision);
	UNUSED(size);
	UNUSED(types);
	UNUSED(buffer);
	UNUSED(flags);
	UNUSED(width);
	
	return (write(1, "%%", 1));
}

/******* PRINT INT *******/
/**
 * print_int - Prints an int
 * @precision: Precision specification
 * @size: Size specifier
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @width: get width.
  * @flags:  Calculates active flags
 * Return: Number of chars printed
 */

int print_int(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	int i = BUFF_SIZE - 2;
	int is_negative = 0;
	long int n = va_arg(types, long int);
	unsigned long int num;

	n = convert_size_number(n, size);

	if (n == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';
	num = (unsigned long int)n;

	if (n < 0)
	{
		num = (unsigned long int)((-1) * n);
		is_negative = 1;
	}

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}
	i++;

	return (write_number(is_negative, i, buffer, flags, width, precision, size));
}

/********** PRINT BINARY *************/
/**
 * print_binary - Prints an unsigned number
* @precision: Precision specification
 * @size: Size specifier
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @width: get width.
 * @flags:  Calculates active flags

 * Return: No. of chars printed.
 */

int print_binary(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	unsigned int x, y, i, sum;
	unsigned int a[32];
	int count;

    UNUSED(precision);
	UNUSED(size);
	UNUSED(buffer);
	UNUSED(width);
	UNUSED(flags);

	x = va_arg(types, unsigned int);
	y = 2147483648; 
	a[0] = x / y;
	for (i = 1; i < 32; i++)
	{
		y /= 2;
		a[i] = (x / y) % 2;
	}
	for (i = 0, sum = 0, count = 0; i < 32; i++)
	{
		sum += a[i];
		if (sum || i == 31)
		{
			char z = '0' + a[i];

			write(1, &z, 1);
			count++;
		}
	}
	return (count);
}
