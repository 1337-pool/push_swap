#include "push_swap.h"

static int	ft_atoi_safe(const char *str, int *error)
{
	long	result;
	int		sign;

	result = 0;
	sign = 1;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str == '-')
			sign = -1;
		str++;
	}
	if (!*str || (*str < '0' || *str > '9'))
		*error = 1;
	while (*str >= '0' && *str <= '9')
	{
		result = result * 10 + (*str - '0');
		if ((sign == 1 && result > INT_MAX) || 
			(sign == -1 && result > (long)INT_MAX + 1))
			*error = 1;
		str++;
	}
	if (*str != '\0')
		*error = 1;
	return ((int)(result * sign));
}

static int	check_duplicates(t_stack *stack)
{
	t_stack	*tmp;
	t_stack	*check;

	tmp = stack;
	while (tmp)
	{
		check = tmp->next;
		while (check)
		{
			if (tmp->value == check->value)
				return (1);
			check = check->next;
		}
		tmp = tmp->next;
	}
	return (0);
}

t_stack	*parse_args(int argc, char **argv)
{
	t_stack	*a;
	int		i;
	int		num;
	int		error;

	a = NULL;
	i = 1;
	while (i < argc)
	{
		error = 0;
		num = ft_atoi_safe(argv[i], &error);
		if (error)
		{
			free_stack(&a);
			return (NULL);
		}
		stack_add_back(&a, stack_new(num));
		i++;
	}
	if (check_duplicates(a))
	{
		free_stack(&a);
		return (NULL);
	}
	return (a);
}

int	is_sorted(t_stack *stack)
{
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

void	error_exit(t_stack **a, t_stack **b)
{
	if (a)
		free_stack(a);
	if (b)
		free_stack(b);
	write(2, "Error\n", 6);
	exit(1);
}