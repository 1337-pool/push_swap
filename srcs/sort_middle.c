#include "push_swap.h"

static int	get_stack_size(t_stack *stack)
{
	int	len;

	len = 0;
	while (stack)
	{
		stack = stack->next;
		len++;
	}
	return (len);
}

static int	find_min_pos(t_stack *stack)
{
	int		pos;
	int		min_pos;
	int		min_val;

	pos = 1;
	min_pos = 1;
	min_val = stack->value;
	while (stack)
	{
		if (stack->value < min_val)
		{
			min_val = stack->value;
			min_pos = pos;
		}
		stack = stack->next;
		pos++;
	}
	return (min_pos);
}

void	sort_middle(t_stack **a, t_stack **b)
{
	int	pos;
	int	size;

	while (get_stack_size(*a) > 3)
	{
		pos = find_min_pos(*a);
		size = get_stack_size(*a);
		if (pos <= size / 2 + 1)
		{
			while (pos-- > 1)
				ra(a, 1);
		}
		else
		{
			while (pos++ <= size)
				rra(a, 1);
		}
		pb(a, b, 1);
	}
	simple_sort(a);
	pa(a, b, 1);
	pa(a, b, 1);
}
