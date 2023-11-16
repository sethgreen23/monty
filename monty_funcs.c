#include "monty.h"

/**
 * read_file - read the file lines
 * @filename: filename
 * @stack: stack
 *
 * Return: nothing
 */
void read_file(char *filename, stack_t **stack)
{
	size_t len = 0;
	ssize_t lread = 0;
	char *opcode;
	int line_num = 1;
	inst_fun func;

	/*Open the file*/
	global_vars.file = fopen(filename, "r");
	if (global_vars.file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}
	/*read the lines*/

	global_vars.line = NULL;
	while ((lread = getline(&global_vars.line, &len, global_vars.file)) != -1)
	{
		opcode = parse_line(line_num);
		if (opcode == NULL)
		{
			line_num++;
			continue;
		}
		/*get the function related to the opcode*/
		func = get_opcode_func(opcode);
		if (func == NULL)
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_num, opcode);
			exit(EXIT_FAILURE);
		}
		func(stack, line_num);
		line_num++;
	}
	free(global_vars.line);
	fclose(global_vars.file);
}

/**
 * parse_line - parse the line
 * @linenum: linenum
 *
 * Return: opcode or NULL
 */
char *parse_line(int linenum)
{
	char *opcode = NULL;
	char *argument = NULL;

	/*start by tokenize the string to get the opcode*/
	opcode = strtok(global_vars.line, " \n");
	if (opcode == NULL)
		return (NULL);
	if (strcmp(opcode, "push") == 0)
	{
		argument = strtok(NULL, " \n");
		if (argument != NULL && is_numerical(argument))
		{
			global_vars.arg = atoi(argument);
		}
		else
		{
			fprintf(stderr, "L%d: usage: push integer\n", linenum);
			exit(EXIT_FAILURE);
		}
	}
	return (opcode);
}

/**
 * is_numerical - is a number
 * @str: string to check
 *
 * Return: 1 if number 0 if not
 */
int is_numerical(char *str)
{
	int i = 0;

	if (str == NULL)
		return (0);
	while (str[i] != '\0')
	{
		if (str[0] == '-')
		{
			i++;
			continue;
		}
		if (str[i] < 48 || str[i] > 57)
			return (0);
		i++;
	}
	return (1);
}
/**
 * get_opcode_func - get associete function to the opcode
 * @opcode: string
 *
 * Return: appropriete function or NULL
 */
inst_fun get_opcode_func(char *opcode)
{
	int i = 0;

	instruction_t instructions[] = {
		{"push", push},
		{"pall", pall},
		{"pint", pint},
		{"pop", pop},
		{"swap", swap},
		{"add", add},
		{"nop", nop},
		{NULL, NULL}};
	while (instructions[i].f != NULL)
	{
		if (strcmp(instructions[i].opcode, opcode) == 0)
		{
			return (instructions[i].f);
		}
		i++;
	}
	return (NULL);
}
/**
 * is_empty - check if the stack is empty
 * @stack: stack
 *
 * Return: 1 if empty, 0 if not
 */
int is_empty(stack_t *stack)
{
	return (stack == NULL);
}
