#include "shell.h"

/**
 * long_to_string - converts a number to a string.
 * @number: number to be converten in an string.
 * @string: buffer to save the number as string.
 * @base: base to convert number
 *
 * Return: Nothing.
 */
void long_to_string(long number, char *string, int base)
{
	int i = 0, Negative = 0;
	long chris = number;
	char letters[] = {"0123456789abcdef"};

	if (chris == 0)
		string[i++] = '0';

	if (string[0] == '-')
		Negative = 1;

	while (chris)
	{
		if (chris < 0)
			string[i++] = letters[-(chris % base)];
		else
			string[i++] = letters[chris % base];
		chris /= base;
	}
	if (Negative)
		string[i++] = '-';

	string[i] = '\0';
	custom_str_reverse(string);
}


/**
 * _atoi - convert a string to an integer.
 *
 * @s: pointer to str origen.
 * Return: int of string or 0.
 */
int _atoi(char *s)
{
	int signal = 1;
	unsigned int number = 0;

	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			signal *= -1;
		if (*s == '+')
			signal *= +1;
		s++;
	}

	/*2 - extract the number */
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{

		number = (number * 10) + (*s - '0');
		s++;
	}
	return (number * signal);
}

/**
 * count_characters - count the coincidences of character in string.
 *
 * @string: pointer to str origen.
 * @character: string with  chars to be counted
 * Return: int of string or 0.
 */
int count_characters(char *string, char *character)
{
	int i = 0, count = 0;

	for (; string[i]; i++)
	{
		if (string[i] == character[0])
			count++;
	}
	return (count);
}

