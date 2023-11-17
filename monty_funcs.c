#include "monty.h"

static int arg;

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
	char *opcode = NULL, *line = NULL;
	int line_num = 1;
	inst_fun func;
	FILE *file;

	/*Open the file*/
	file = fopen(filename, "r");
	if (file == NULL)
	{
		fprintf(stderr, "Error: Can't open file %s\n", filename);
		exit(EXIT_FAILURE);
	}
	/*read the lines*/

	line = NULL;
	while ((lread = getline(&line, &len, file)) != -1)
	{
		printf("%s\n", line);
		opcode = parse_line(line_num, line);
		printf("%s\n", opcode);

		if (opcode == NULL || opcode[0] == '#')
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
	free(line);
	fclose(file);
}

/**
 * parse_line - parse the line
 * @linenum: linenum
 * @line: line
 *
 * Return: opcode or NULL
 */
char *parse_line(int linenum, char *line)
{
	char *opcode = NULL;
	char *argument = NULL;

	/*start by tokenize the string to get the opcode*/
	printf("%s\n", line);
	opcode = strtok(line, " \n");
	if (opcode == NULL)
		return (NULL);

	if (strcmp(opcode, "push") == 0)
	{
		argument = strtok(NULL, " \n");
		if (argument != NULL && is_numerical(argument))
		{
			arg = atoi(argument);
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
		{"div", divide},
		{"sub", sub},
		{"mul", mul},
		{"mod", mod},
		{"pchar", pchar},
		{"pstr", pstr},
		{"rotl", rotl},
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
 * get_arg - return the arg variable
 * Return: arg value
 */
int get_arg(void)
{
	return (arg);
}
