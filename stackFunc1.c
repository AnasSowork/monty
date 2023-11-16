#include "monty.h"

/**
 * addToStack - Adds a new node to the top of the linked list (stack).
 * @newNode: A pointer to the new node to be added.
 * @lineNumber: The line number (unused attribute).
 */
void addToStack(stack_t **newNode,
__attribute__((unused))unsigned int lineNumber)
{
	stack_t *tmp;

	if (newNode == NULL || *newNode == NULL)
		exit(EXIT_FAILURE);
	if (head == NULL)
	{
		head = *newNode;
		return;
	}
	tmp = head;
	head = *newNode;
	head->next = tmp;
	tmp->prev = head;
}

/**
 * printStack - Prints all elements of the stack.
 * @stack: A pointer to the top of the stack.
 * @lineNumber: The line number (unused attribute).
 */
void printStack(stack_t **stack, unsigned int lineNumber)
{
	stack_t *tmp;

	(void)lineNumber;
	if (stack == NULL)
		exit(EXIT_FAILURE);
	tmp = *stack;
	while (tmp != NULL)
	{
		printf("%d\n", tmp->n);
		tmp = tmp->next;
	}
}

/**
 * popTop - Removes the top element from the stack.
 * @stack: A pointer to the top of the stack.
 * @lineNumber: The line number where the operation occurs.
 */
void popTop(stack_t **stack, unsigned int lineNumber)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL)
		handleMoreErrors(7, lineNumber);

	tmp = *stack;
	*stack = tmp->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;
	free(tmp);
}

/**
 * printTop - Prints the value of the top element in the stack.
 * @stack: A pointer to the top of the stack.
 * @lineNumber: The line number where the operation occurs.
 */
void printTop(stack_t **stack, unsigned int lineNumber)
{
	if (stack == NULL || *stack == NULL)
		handleMoreErrors(6, lineNumber);
	printf("%d\n", (*stack)->n);
}
