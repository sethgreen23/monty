#include "monty.h"

/**
 * mod - computes the rest of the division of the second top element of
 * the stack by the top element of the stack.
 * and operate pop, unless top == zero
 * @stack: stack
 * @line_number: line_number
 *
 * Return: nothing
 */
void mod(stack_t **stack, unsigned int line_number)
{
	int result = 0;

	if (*stack == NULL || (*stack)->prev == NULL)
	{
		fprintf(stderr, "L%d: can't mod, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->n == 0)
	{
		fprintf(stderr, "L%d: division by zero\n", line_number);
		exit(EXIT_FAILURE);
	}
	result = (*stack)->prev->n % (*stack)->n;
	(*stack)->prev->n = result;
	pop(stack, line_number);
}

/**
 * pchar - print the top most value as a char if not out of range
 * @stack: stack
 * @line_number: line_number
 *
 * Return: nothing
 */
void pchar(stack_t **stack, unsigned int line_number)
{
	if (*stack == NULL)
	{
		fprintf(stderr, "L%d: can't pchar, stack empty\n", line_number);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->n < 0 || (*stack)->n > 127)
	{
		fprintf(stderr, "L%d: can't pchar, value out of range\n", line_number);
		exit(EXIT_FAILURE);
	}

	printf("%c\n", (*stack)->n);
}

