/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaber <mjaber@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/20 17:00:00 by mjaber            #+#    #+#             */
/*   Updated: 2025/12/21 00:00:00 by mjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

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

static void	free_split(char **args)
{
	int	i;

	if (!args)
		return ;
	i = 0;
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}

static int	validate_and_add(t_stack **a, char *str_val)
{
	long	n;
	t_stack	*new_node;

	n = ft_atoi(str_val);
	if (n > INT_MAX || n < INT_MIN)
		return (0);
	if (check_dup(*a, (int)n))
		return (0);
	new_node = ft_lstnew((int)n);
	if (!new_node)
		return (0);
	ft_lstadd_back(a, new_node);
	return (1);
}

static void	process_argument(char *arg, t_stack **a)
{
	char	**args;
	int		j;

	args = ft_split(arg, ' ');
	if (!args || !args[0])
	{
		free_split(args);
		error_exit(a, NULL, NULL);
	}
	j = 0;
	while (args[j])
	{
		if (!validate_and_add(a, args[j]))
		{
			free_split(args);
			error_exit(a, NULL, NULL);
		}
		j++;
	}
	free_split(args);
}

void	parse_args(int argc, char **argv, t_stack **a)
{
	int		i;

	i = 1;
	while (i < argc)
	{
		process_argument(argv[i], a);
		i++;
	}
}
