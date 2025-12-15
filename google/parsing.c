/* ************************************************************************** */
/*                                                                            */
/*   parsing.c                                                                */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	check_dup(t_stack *a, int n)
{
	while (a)
	{
		if (a->value == n)
			return (1);
		a = a->next;
	}
	return (0);
}

static void	add_to_stack(t_stack **a, char *str_val)
{
	long	n;
	t_stack	*new_node;

	n = ft_atoi(str_val);
	if (n > INT_MAX || n < INT_MIN)
		error_exit(a, NULL);
	if (check_dup(*a, (int)n))
		error_exit(a, NULL);
	new_node = ft_lstnew((int)n);
	if (!new_node)
		error_exit(a, NULL);
	ft_lstadd_back(a, new_node);
}

static void	free_split(char **args)
{
	int	i;

	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

void	parse_args(int argc, char **argv, t_stack **a)
{
	int		i;
	int		j;
	char	**args;

	i = 1;
	while (i < argc)
	{
		args = ft_split(argv[i], ' ');
		if (!args || !args[0])
		{
			if (args)
				free_split(args);
			error_exit(a, NULL);
		}
		j = 0;
		while (args[j])
		{
			add_to_stack(a, args[j]);
			j++;
		}
		free_split(args);
		i++;
	}
}