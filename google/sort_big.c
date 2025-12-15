/* ************************************************************************** */
/*                                                                            */
/*   sort_big.c                                                               */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

static int	find_max_pos(t_stack *stack, int max_index)
{
	int	pos;

	pos = 0;
	while (stack)
	{
		if (stack->index == max_index)
			return (pos);
		pos++;
		stack = stack->next;
	}
	return (-1);
}

static void	move_max_to_a(t_stack **a, t_stack **b, int max_idx)
{
	int	pos;
	int	size;

	size = ft_lstsize(*b);
	pos = find_max_pos(*b, max_idx);
	if (pos <= size / 2)
	{
		while ((*b)->index != max_idx)
			rb(b, 1);
	}
	else
	{
		while ((*b)->index != max_idx)
			rrb(b, 1);
	}
	pa(a, b, 1);
}

/* 
** The Core Chunk Logic
** 1. Push A to B in chunks (based on index).
** 2. If index < counter, pb and rotate b (put at bottom).
** 3. If index in range, just pb.
** 4. Else rotate a.
*/
void	sort_chunks(t_stack **a, t_stack **b)
{
	int	i;
	int	range;
	int	size;

	i = 0;
	size = ft_lstsize(*a);
	range = 0;
	if (size > 100)
		range = 30; // Optimized for 500
	else
		range = 15; // Optimized for 100
	while (*a)
	{
		if ((*a)->index <= i)
		{
			pb(a, b, 1);
			rb(b, 1);
			i++;
		}
		else if ((*a)->index <= i + range)
		{
			pb(a, b, 1);
			i++;
		}
		else
			ra(a, 1);
	}
	while (size > 0)
		move_max_to_a(a, b, --size);
}