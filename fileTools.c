#include "monty.h"

/**
 * openFile - Opens and reads a Monty bytecode file.
 * @fileName: The name of the Monty bytecode file.
 */
void openFile(char *fileName)
{
	FILE *fileDescriptor = fopen(fileName, "r");

	if (fileName == NULL || fileDescriptor == NULL)
		handleErrors(2, fileName);

	readFile(fileDescriptor);
	fclose(fileDescriptor);
}

/**
 * readFile - Reads the contents of a Monty bytecode file line by line.
 * @fileDescriptor: The file descriptor of the opened Monty bytecode file.
 */
void readFile(FILE *fileDescriptor)
{
	int lineNumber = 0, format = 0;
	char *buffer = NULL;
	size_t length = 0;
	size_t line_length;

	while (_getline(&buffer, &length, fileDescriptor) != -1)
	{
		lineNumber++;

		line_length = strlen(buffer);

		if (line_length > 0 && buffer[line_length - 1] == '\n')
		{
			buffer[line_length - 1] = '\0';
		}

		format = parseLine(buffer, lineNumber, format);
	}

	free(buffer);
}


/**
 * parseLine - Parses a line from the Monty bytecode file.
 * @buffer: The buffer containing the line from the file.
 * @lineNumber: The current line number being parsed.
 * @format: The format indicator for stack or queue mode.
 * Return: The updated format indicator.
 */
int parseLine(char *buffer, int lineNumber, int format)
{
	char *opcode, *value;
	const char *delim = "\n ";

	if (buffer == NULL)
		handleErrors(4);

	opcode = strtok(buffer, delim);
	if (opcode == NULL)
		return (format);
	value = strtok(NULL, delim);

	if (strcmp(opcode, "stack") == 0)
		return (0);
	if (strcmp(opcode, "queue") == 0)
		return (1);

	findFunc(opcode, value, lineNumber, format);
	return (format);
}

/**
 * findFunc - Finds the corresponding function for a given opcode.
 * @opcode: The opcode to be matched.
 * @value: The value associated with the opcode.
 * @lineNumber: The current line number being processed.
 * @format: The format indicator for stack or queue mode.
 */
void findFunc(char *opcode, char *value, int lineNumber, int format)
{
	int i;
	int flag;

	instruction_t funcList[] = {
		{"push", addToStack},
		{"pall", printStack},
		{"pint", printTop},
		{"pop", popTop},
		{"nop", nop},
		{"swap", swapNodes},
		{"add", addNodes},
		{"sub", subNodes},
		{"div", divNodes},
		{"mul", mulNodes},
		{"mod", modNodes},
		{"pchar", printChar},
		{"pstr", printStr},
		{"rotl", rotl},
		{"rotr", rotr},
		{NULL, NULL}
	};

	if (opcode[0] == '#')
		return;

	for (flag = 1, i = 0; funcList[i].opcode != NULL; i++)
	{
		if (strcmp(opcode, funcList[i].opcode) == 0)
		{
			callFun(funcList[i].f, opcode, value, lineNumber, format);
			flag = 0;
		}
	}
	if (flag == 1)
		handleErrors(3, lineNumber, opcode);
}

/**
 * callFun - Calls the appropriate function based on the opcode .
 * @func: The function pointer to the corresponding opcode function.
 * @op: The opcode.
 * @val: The value associated with the opcode.
 * @lineNumber: The current line number being processed .
 * @format: The format indicator for stack or queue mode.
 */
void callFun(op_func func, char *op, char *val, int lineNumber, int format)
{
	stack_t *node;
	int flag;
	int i;

	flag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val != NULL && val[0] == '-')
		{
			val = val + 1;
			flag = -1;
		}
		if (val == NULL)
			handleErrors(5, lineNumber);
		for (i = 0; val[i] != '\0'; i++)
		{
			if (!isdigit(val[i]))
				handleErrors(5, lineNumber);
		}
		node = createNode(atoi(val) * flag);
		if (format == 0)
			func(&node, lineNumber);
		if (format == 1)
			addToQueue(&node, lineNumber);
	} else
		func(&head, lineNumber);
}
