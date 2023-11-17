#include "monty.h"

/**
 * mod - computes the rest of the division of the second top element of
 * the stack by the top element of the stack.
 * and operate pop, unless top == zero
 * @stack: stack
 * @line_number: line_number
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

/**
 * pstr - prints the string starting at the top of the stack, followed
 * by a new line, while the interger being treated as an ascii value
 * @stack: stack
 * @line_number: line_number
 * Return: nothing
 */
void pstr(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = *stack;

	(void)line_number;
	if (temp == NULL)
	{
		putchar('\n');
		return;
	}

	while (temp && (temp->n < 128 && temp->n > 0))
	{
		fprintf(stdout, "%c", temp->n);
		temp = temp->prev;
	}
	putchar('\n');
}

/**
 * rotl - prints the string starting at the top of the stack, followed
 * by a new line, while the interger being treated as an ascii value
 * @stack: stack
 * @line_number: line_number
 * Return: nothing
 */
void rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL, *first = NULL;

	(void)line_number;
	if (*stack == NULL || (*stack)->prev == NULL)
	{
		return;
	}
	first = *stack;
	*stack = (*stack)->prev;
	(*stack)->next = NULL;
	first->prev = NULL;
	first->next = NULL;
	temp = *stack;
	while (temp->prev != NULL)
		temp = temp->prev;
	temp->prev = first;
	first->next = temp;
}

/**
 * rotr - prints the string starting at the top of the stack, followed
 * by a new line, while the interger being treated as an ascii value
 * @stack: stack
 * @line_number: line_number
 * Return: nothing
 */
void rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL, *first = *stack, *last = NULL;
	(void)line_number;
	if (*stack == NULL || (*stack)->prev == NULL)
	{
		return;
	}
	temp = *stack;
	while (temp->prev->prev != NULL)
		temp = temp->prev;
	last = temp->prev;
	last->next = NULL;
	temp->prev = NULL;
	last->prev = first;
	first->next = last;
	*stack = last;
}
