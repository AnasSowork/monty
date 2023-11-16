#include "monty.h"

/**
 * nop - Does nothing.
 * @stack: A pointer to the top of the stack.
 * @lineNumber: The line number (unused attribute).
 */
void nop(stack_t **stack, unsigned int lineNumber)
{
	(void)stack;
	(void)lineNumber;
}

/**
 * swapNodes - Swaps the top two elements of the stack.
 * @stack: A pointer to the top of the stack.
 * @lineNumber: The line number where the operation occurs.
 */
void swapNodes(stack_t **stack, unsigned int lineNumber)
{
	stack_t *tmp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		handleMoreErrors(8, lineNumber, "swap");

	tmp = (*stack)->next;
	(*stack)->next = tmp->next;
	if (tmp->next != NULL)
		tmp->next->prev = *stack;
	tmp->next = *stack;
	(*stack)->prev = tmp;
	tmp->prev = NULL;
	*stack = tmp;
}

/**
 * addNodes - Adds the top two elements of the stack.
 * @stack: A pointer to the top of the stack.
 * @lineNumber: The line number where the operation occurs.
 */
void addNodes(stack_t **stack, unsigned int lineNumber)
{
	int sum;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		handleMoreErrors(8, lineNumber, "add");

	(*stack) = (*stack)->next;
	sum = (*stack)->n + (*stack)->prev->n;
	(*stack)->n = sum;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}

/**
 * subNodes - Subtracts the top element from the second element in the stack.
 * @stack: A pointer to the top of the stack.
 * @lineNumber: The line number where the operation occurs.
 */
void subNodes(stack_t **stack, unsigned int lineNumber)
{
	int difference;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		handleMoreErrors(8, lineNumber, "sub");

	(*stack) = (*stack)->next;
	difference = (*stack)->n - (*stack)->prev->n;
	(*stack)->n = difference;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}

/**
 * divNodes - Divides the second element by the top element in the stack.
 * @stack: A pointer to the top of the stack.
 * @lineNumber: The line number where the operation occurs.
 */
void divNodes(stack_t **stack, unsigned int lineNumber)
{
	int quotient;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		handleMoreErrors(8, lineNumber, "div");

	if ((*stack)->n == 0)
		handleMoreErrors(9, lineNumber);

	(*stack) = (*stack)->next;
	quotient = (*stack)->n / (*stack)->prev->n;
	(*stack)->n = quotient;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}
