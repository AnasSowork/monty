#include "monty.h"

/**
 * handleErrors - Handles various error cases and prints
 * corresponding messages.
 * @errorCode: The error code indicating the type of error.
 *             1 - Incorrect usage.
 *             2 - Unable to open file.
 *             3 - Unknown instruction.
 *             4 - Memory allocation failure.
 *             5 - Incorrect push usage.
 */
void handleErrors(int errorCode, ...)
{
	va_list args;
	char *op;
	int lineNum;

	va_start(args, errorCode);
	switch (errorCode)
	{
		case 1:
			fprintf(stderr, "USAGE: monty file\n");
			break;
		case 2:
			fprintf(stderr, "Error: Can't open file %s\n", va_arg(args, char *));
			break;
		case 3:
			lineNum = va_arg(args, int);
			op = va_arg(args, char *);
			fprintf(stderr, "L%d: unknown instruction %s\n", lineNum, op);
			break;
		case 4:
			fprintf(stderr, "Error: malloc failed\n");
			break;
		case 5:
			fprintf(stderr, "L%d: usage: push integer\n", va_arg(args, int));
			break;
		default:
			break;
	}
	freeNodes();
	exit(EXIT_FAILURE);
}

/**
 * handleMoreErrors - Handles additional error cases and prints
 * corresponding messages.
 * @errorCode: The error code indicating the type of error.
 *             6 - Unable to pint, stack empty.
 *             7 - Unable to pop, empty stack.
 *             8 - Unable to perform an operation, stack too short.
 *             9 - Division by zero.
 */
void handleMoreErrors(int errorCode, ...)
{
	va_list args;
	char *op;
	int lineNum;

	va_start(args, errorCode);
	switch (errorCode)
	{
		case 6:
			fprintf(stderr, "L%d: can't pint, stack empty\n", va_arg(args, int));
			break;
		case 7:
			fprintf(stderr, "L%d: can't pop an empty stack\n", va_arg(args, int));
			break;
		case 8:
			lineNum = va_arg(args, unsigned int);
			op = va_arg(args, char *);
			fprintf(stderr, "L%d: can't %s, stack too short\n", lineNum, op);
			break;
		case 9:
			fprintf(stderr, "L%d: division by zero\n", va_arg(args, unsigned int));
			break;
		default:
			break;
	}
	freeNodes();
	exit(EXIT_FAILURE);
}

/**
 * handleStringErrors - Handles string-related error cases and prints
 * corresponding messages.
 * @errorCode: The error code indicating the type of error.
 *             10 - Unable to pchar, value out of range.
 *             11 - Unable to pchar, stack empty.
 */
void handleStringErrors(int errorCode, ...)
{
	va_list args;
	int lineNum;

	va_start(args, errorCode);
	lineNum = va_arg(args, int);
	switch (errorCode)
	{
		case 10:
			fprintf(stderr, "L%d: can't pchar, value out of range\n", lineNum);
			break;
		case 11:
			fprintf(stderr, "L%d: can't pchar, stack empty\n", lineNum);
			break;
		default:
			break;
	}
	freeNodes();
	exit(EXIT_FAILURE);
}
