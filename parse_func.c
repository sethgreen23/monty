#include "monty.h"

static stack_t *start;

/**
 * push - push element to the stack
 * @stack: stack
 * @line_number: line_number
 *
 * Return: nothing
 */
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *layer = malloc(sizeof(stack_t));

	(void)line_number;
	if (layer == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		exit(EXIT_FAILURE);
	}
	layer->n = get_arg();
	layer->next = NULL;
	layer->prev = *stack;
	if (!is_empty(*stack))
	{
		(*stack)->next = layer;
	}
	else
	{
		set_start(layer);
	}
	*stack = layer;
}

/**
 * pall - print the elements of the stack
 * @stack: stack
 * @line_number: line_number
 *
 * Return: nothing
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;

	(void)line_number;
	while (temp != NULL)
	{
		fprintf(stdout, "%d\n", temp->n);
		temp = temp->prev;
	}
}

/**
 * pint - print the top most stack node
 * @stack: stack
 * @line_number: line_number
 *
 * Return: nothing
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pint, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	fprintf(stdout, "%d\n", (*stack)->n);
}

/**
 * set_start - set the start variable
 * @start: the value of start
 * Return: void
*/
void set_start(stack_t *start_value)
{
	start = start_value;
}

/**
 * get_start - return the start variable
 * Return: the value of it
*/
stack_t *get_start()
{
	return (start);
}