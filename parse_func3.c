#include "monty.h"

/**
 * pop - delete the top most layer of the stack
 * @stack: stack
 * @line_number: line_number
 *
 * Return: nothing
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp = NULL;

	if (is_empty(*stack))
	{
		fprintf(stderr, "L%d: can't pop an empty stack\n", line_number);
		exit(EXIT_FAILURE);
	}
	if ((*stack)->prev == NULL)
	{
		(*stack)->next = NULL;
		free(*stack), *stack = NULL;
	}
	else
	{
		temp = *stack;
		/*shouldn't stack -> next == NULL?*/
		*stack = (*stack)->prev;
		temp->prev = NULL;
		temp->next = NULL;
		free(temp), temp = NULL;
	}
}

/**
 * swap - swap the top two elements of the slack
 * @stack: stack
 * @line_number: line_number
 *
 * Return: nothing
 */
void swap(stack_t **stack, unsigned int line_number)
{
	int temp;

	if (*stack == NULL || (*stack)->prev == NULL)
	{
		fprintf(stderr, "L%d: can't swap, stack too short\n", line_number);
		exit(EXIT_FAILURE);
	}
	temp = (*stack)->n;
	(*stack)->n = (*stack)->prev->n;
	(*stack)->prev->n = temp;
}

void rotl(stack_t **stack, unsigned int line_number)
{
    stack_t *start = get_start();

    (void)line_number;
    if (*stack == NULL || (*stack)->prev == NULL)
        return;
    start->prev = *stack;
    (*stack)->next = start;

    *stack = (*stack)->prev;
    (*stack)->next = NULL;
    start->prev->prev = NULL;
}

