/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaber <mjaber@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/21 13:02:55 by mjaber            #+#    #+#             */
/*   Updated: 2025/12/21 13:02:56 by mjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "checker_bonus.h"

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
