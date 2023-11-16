#include "monty.h"
stack_t *head = NULL;

/**
 * main - Entry point for the Monty interpreter.
 * @argc: The number of command-line arguments.
 * @argv: An array of strings containing the command-line arguments.
 * Return: 0 on success, EXIT_FAILURE on failure.
 */
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		fprintf(stderr, "USAGE: monty file\n");
		exit(EXIT_FAILURE);
	}
	openFile(argv[1]);
	freeNodes();
	return (0);
}

/**
 * createNode - Creates a new node with the given integer value.
 * @n: The integer value to be stored in the new node.
 * Return: A pointer to the newly created node.
 */
stack_t *createNode(int n)
{
	stack_t *node = malloc(sizeof(stack_t));

	if (node == NULL)
		handleErrors(4);

	node->next = NULL;
	node->prev = NULL;
	node->n = n;
	return (node);
}

/**
 * freeNodes - Frees all the nodes in the linked list.
 */
void freeNodes(void)
{
	stack_t *tmp;

	if (head == NULL)
		return;

	while (head != NULL)
	{
		tmp = head;
		head = head->next;
		free(tmp);
	}
}

/**
 * addToQueue - Adds a new node to the end of the linked list (queue).
 * @new_node: A pointer to the new node to be added.
 * @ln: The line number (unused attribute).
 */
void addToQueue(stack_t **new_node, __attribute__((unused))unsigned int ln)
{
	stack_t *tmp;

	if (new_node == NULL || *new_node == NULL)
		exit(EXIT_FAILURE);
	if (head == NULL)
	{
		head = *new_node;
		return;
	}
	tmp = head;
	while (tmp->next != NULL)
		tmp = tmp->next;

	tmp->next = *new_node;
	(*new_node)->prev = tmp;

}
