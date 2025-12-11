#include "push_swap.h"

int	find_highest_index(t_stack *stack)
{
	int	highest;

	highest = stack->index;
	while (stack)
	{
		if (stack->index > highest)
			highest = stack->index;
		stack = stack->next;
	}
	return (highest);
}

static void	push_to_b_chunked(t_stack **a, t_stack **b, int size)
{
	int	chunk_size;
	int	pushed;
	int	chunk_max;

	if (size <= 100)
		chunk_size = 15;
	else
		chunk_size = 30;
	pushed = 0;
	chunk_max = chunk_size;
	while (*a && stack_size(*a) > 3)
	{
		if ((*a)->index <= pushed)
		{
			pb(b, a, 1);
			pushed++;
		}
		else if ((*a)->index <= chunk_max)
		{
			pb(b, a, 1);
			rb(b, 1);
			pushed++;
		}
		else
			ra(a, 1);
		if (pushed == chunk_max && chunk_max < size)
			chunk_max += chunk_size;
	}
}

static void	shift_stack(t_stack **a)
{
	int	size;
	int	lowest_pos;
	int	i;

	size = stack_size(*a);
	lowest_pos = 0;
	i = 0;
	while ((*a)->index != 0)
	{
		if (i == 0)
		{
			while ((*a) && (*a)->index != 0)
			{
				lowest_pos++;
				*a = (*a)->next;
			}
			i = 1;
		}
	}
	if (lowest_pos <= size / 2)
		while ((*a)->index != 0)
			ra(a, 1);
	else
		while ((*a)->index != 0)
			rra(a, 1);
}

void	sort_large(t_stack **a, t_stack **b)
{
	int	size;

	size = stack_size(*a);
	assign_index(*a, size);
	push_to_b_chunked(a, b, size);
	if (!is_sorted(*a))
		sort_three(a);
	while (*b)
	{
		get_target_position(a, b);
		calculate_cost(a, b);
		execute_cheapest(a, b);
	}
	if (!is_sorted(*a))
		shift_stack(a);
}