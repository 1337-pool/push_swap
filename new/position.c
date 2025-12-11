#include "push_swap.h"

void	assign_index(t_stack *a, int size)
{
	t_stack	*tmp;
	t_stack	*highest;
	int		value;

	while (--size > 0)
	{
		tmp = a;
		value = INT_MIN;
		highest = NULL;
		while (tmp)
		{
			if (tmp->value == INT_MIN && tmp->index == -1)
				tmp->index = 0;
			if (tmp->value > value && tmp->index == -1)
			{
				value = tmp->value;
				highest = tmp;
			}
			tmp = tmp->next;
		}
		if (highest)
			highest->index = size;
	}
}

void	assign_position(t_stack **stack)
{
	t_stack	*tmp;
	int		pos;

	tmp = *stack;
	pos = 0;
	while (tmp)
	{
		tmp->pos = pos;
		tmp = tmp->next;
		pos++;
	}
}

static int	find_target(t_stack *a, int index_b, int target_idx, int target_pos)
{
	t_stack	*tmp;

	tmp = a;
	while (tmp)
	{
		if (tmp->index > index_b && tmp->index < target_idx)
		{
			target_idx = tmp->index;
			target_pos = tmp->pos;
		}
		tmp = tmp->next;
	}
	if (target_idx != INT_MAX)
		return (target_pos);
	tmp = a;
	while (tmp)
	{
		if (tmp->index < target_idx)
		{
			target_idx = tmp->index;
			target_pos = tmp->pos;
		}
		tmp = tmp->next;
	}
	return (target_pos);
}

void	get_target_position(t_stack **a, t_stack **b)
{
	t_stack	*tmp;
	int		target_pos;

	tmp = *b;
	assign_position(a);
	assign_position(b);
	target_pos = 0;
	while (tmp)
	{
		target_pos = find_target(*a, tmp->index, INT_MAX, target_pos);
		tmp->target_pos = target_pos;
		tmp = tmp->next;
	}
}