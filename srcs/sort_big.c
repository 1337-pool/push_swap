/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_big.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaber <mjaber@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:47:16 by mjaber            #+#    #+#             */
/*   Updated: 2025/12/16 18:49:24 by mjaber           ###   ########.fr       */
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

static void	push_chunks(t_stack **a, t_stack **b, int range)
{
	int	i;

	i = 0;
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
}

void	sort_chunks(t_stack **a, t_stack **b)
{
	int	range;
	int	size;

	size = ft_lstsize(*a);
	if (size > 100)
		range = 35;
	else
		range = 15;
	push_chunks(a, b, range);
	while (size > 0)
		move_max_to_a(a, b, --size);
}
