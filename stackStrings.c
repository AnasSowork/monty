#include "monty.h"

/**
 * printChar - Prints the ASCII value.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @lineNumber: Integer representing the line number of the opcode.
 */
void printChar(stack_t **stack, unsigned int lineNumber)
{
	int ascii;

	if (stack == NULL || *stack == NULL)
		handleStringErrors(11, lineNumber);

	ascii = (*stack)->n;
	if (ascii < 0 || ascii > 127)
		handleStringErrors(10, lineNumber);
	printf("%c\n", ascii);
}

/**
 * printStr - Prints a string.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @lineNumber: Integer representing the line number of the opcode.
 */
void printStr(stack_t **stack,
__attribute__((unused))unsigned int lineNumber)
{
	int ascii;
	stack_t *tmp;

	if (stack == NULL || *stack == NULL)
	{
		printf("\n");
		return;
	}

	tmp = *stack;
	while (tmp != NULL)
	{
		ascii = tmp->n;
		if (ascii <= 0 || ascii > 127)
			break;
		printf("%c", ascii);
		tmp = tmp->next;
	}
	printf("\n");
}

/**
 * rotl - Rotates the first node of the stack to the bottom.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @lineNumber: Integer representing the line number of the opcode.
 */
void rotl(stack_t **stack, __attribute__((unused))unsigned int lineNumber)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		return;

	tmp = *stack;
	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = *stack;
	(*stack)->prev = tmp;
	*stack = (*stack)->next;
	(*stack)->prev->next = NULL;
	(*stack)->prev = NULL;
}

/**
 * rotr - Rotates the last node of the stack to the top.
 * @stack: Pointer to a pointer pointing to the top node of the stack.
 * @lineNumber: Integer representing the line number of the opcode.
 */
void rotr(stack_t **stack, __attribute__((unused))unsigned int lineNumber)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		return;

	tmp = *stack;

	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = *stack;
	tmp->prev->next = NULL;
	tmp->prev = NULL;
	(*stack)->prev = tmp;
	(*stack) = tmp;
}

#include "monty.h"

/**
 * _getline - Read a line from a stream.
 * @lineptr: Buffer for the line.
 * @n: Size of the buffer.
 * @stream: Input stream.
 *
 * Return: Number of characters read, -1 on error or EOF.
 *
 * Reads a line from @stream into @lineptr, up to @n characters.
 * Resizes the buffer if necessary .Stops at newline, EOF, or error.
 */

int _getline(char **lineptr, size_t *n, FILE *stream)
{

	int bytesRead = 0;
	size_t totalBytesRead = 0;
	int ch;
	char *newLineptr;

	if (lineptr == NULL || n == NULL || stream == NULL)
		return (-1);
	if (*lineptr == NULL || *n == 0)
	{
		*n = 128;
		*lineptr = (char *)malloc(*n);
		if (*lineptr == NULL)
			return (-1);
	}

	while ((ch = fgetc(stream)) != EOF)
	{
		if (totalBytesRead >= *n - 1)
		{
			*n *= 2;
			newLineptr = (char *)realloc(*lineptr, *n);
			if (newLineptr == NULL)
				return (-1);
			*lineptr = newLineptr;
		}

		(*lineptr)[totalBytesRead++] = (char)ch;
		bytesRead++;

		if (ch == '\n')
			break;
	}

	if (totalBytesRead == 0 && bytesRead == 0)
		return (-1);

	(*lineptr)[totalBytesRead] = '\0';

	return (totalBytesRead);
}
