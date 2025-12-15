/* ************************************************************************** */
/*                                                                            */
/*   sort_utils.c                                                             */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

int	is_sorted(t_stack *stack)
{
	while (stack && stack->next)
	{
		if (stack->value > stack->next->value)
			return (0);
		stack = stack->next;
	}
	return (1);
}

/*
** Simple rank assignment O(n^2).
** For each node, count how many nodes are smaller than it.
** This count is its index (0 to N-1).
*/
void	assign_indices(t_stack *a)
{
	t_stack	*ptr;
	t_stack	*highest;
	int		count;

	ptr = a;
	while (ptr)
	{
		count = 0;
		highest = a;
		while (highest)
		{
			if (highest->value < ptr->value)
				count++;
			highest = highest->next;
		}
		ptr->index = count;
		ptr = ptr->next;
	}
}

/* Hardcoded sort for 3 args (mandatory requirement for efficiency) */
void	simple_sort(t_stack **a)
{
	int	max;

	if (is_sorted(*a))
		return ;
	max = (*a)->index;
	if ((*a)->next->index > max)
		max = (*a)->next->index;
	if ((*a)->next->next->index > max)
		max = (*a)->next->next->index;
	if ((*a)->index == max)
		ra(a, 1);
	else if ((*a)->next->index == max)
		rra(a, 1);
	if ((*a)->index > (*a)->next->index)
		sa(a, 1);
}