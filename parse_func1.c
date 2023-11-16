#include "monty.h"

/**
 * add - Add first layer data to the sencond top one, and
 * remove the top
 * @stack: stack
 * @line_number: line_number
 *
 * Return: nothing
 */
void add(stack_t **stack, unsigned int line_number)
{
	int temp;

	if ((*stack)->prev == NULL)
	{
		fprintf(stderr, "L%d: can't add, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp = (*stack)->n + (*stack)->prev->n;
	(*stack)->prev->n = temp;
	pop(stack, line_number);
}

/**
 * nop - print the elements of the stack
 * @stack: stack
 * @line_number: line_number
 *
 * Return: nothing
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}

/**
 * sub - subtract the top from the soocnd to layer
 * and operate pop
 * @stack: stack
 * @line_number: line_number
 *
 * Return: nothing
 */
void sub(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL || (*stack)->prev == NULL)
	{
		fprintf(stderr, "L%d: can't sub, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	(*stack)->prev->n = (*stack)->prev->n - (*stack)->n;
	pop(stack, line_number);
}
