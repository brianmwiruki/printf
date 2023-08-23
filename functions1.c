#include "main.h"

/******** PRINT UNSIGNED NUMBER *********/
/**
 * _print_unsigned - Prints an unsigned number
 * @precision: Precision specification
 * @size: Size specifier
 * @types: List a of arguments
 * @buffer: Buffer array to handle print
 * @width: get width
 * @flags:  Calculates active flags
 * Return: No. of chars printed.
 */

int print_unsigned(va_list types, int width, char buffer[],
	int flags, int size, int precision)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 10) + '0';
		num /= 10;
	}

	i++;

	return (write_unsgnd(0, width, i, buffer,, size flags, width, precision));
}

/**** PRINT UNSIGNED NUMBER IN OCTAL  *******/
/**
 * @precision: Precision specification
 * @size: Size specifier
 * -print_octal - Print an unsigned num in octal notation
 * @types: List of arguments
 * @flags:  Calculates active flags
 * @width: get width
* @buffer: Buffer array to handle print
 * Return: Number of chars printed
 */

int print_octal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{

	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = (num % 8) + '0';
		num /= 8;
	}

	if (flags & F_HASH && init_num != 0)
		buffer[i--] = '0';

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}

/**** PRINT UNSIGNED NUMBER IN HEXADECIMAL *******/
/**
 * _print_hexadecimal - print an unsigned number in hexadecimal notation
  * @precision: Precision specification
 * @size: Size specifier
 * @types: Lista of arguments
 * @buffer: Buffer array to handle print
 * @width: get width
* @flags:  Calculates active flags
 * Return: Number of chars printed
 */

int print_hexadecimal(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789abcdef", buffer,
		flags, 'x', width, precision, size));
}

/******* PRINT UNSIGNED NUMBER IN UPPER HEXADECIMAL ********/

int print_hexa_upper(va_list types, char buffer[],
	int flags, int width, int precision, int size)
{
	return (print_hexa(types, "0123456789ABCDEF", buffer,
		flags, 'X', width, precision, size));
}

/*****PRINT HEXX NUM IN UPPER OR LOWER ********/
/**
* @precision: Precision specification
 * @size: Size specifier
 * @size: Size specification
 * print_hexa - Prints a hexadecimal number in lower or upper
 * @types: Lista of argument
 * @flags:  Calculates active flags
 * @flag_ch: Calculates active flags
 * @width: get width
  * @map_to: Array of values to map the number to
 * @buffer: Buffer array to handle print
 * Return: Number of chars printed
 */


int print_hexa(va_list types, char flag_ch, char map_to[], char buffer[],
	int size, int flags, int width, int precision)
{
	int i = BUFF_SIZE - 2;
	unsigned long int num = va_arg(types, unsigned long int);
	unsigned long int init_num = num;

	UNUSED(width);

	num = convert_size_unsgnd(num, size);

	if (num == 0)
		buffer[i--] = '0';

	buffer[BUFF_SIZE - 1] = '\0';

	while (num > 0)
	{
		buffer[i--] = map_to[num % 16];
		num /= 16;
	}

	if (flags & F_HASH && init_num != 0)
	{
		buffer[i--] = flag_ch;
		buffer[i--] = '0';
	}

	i++;

	return (write_unsgnd(0, i, buffer, flags, width, precision, size));
}
