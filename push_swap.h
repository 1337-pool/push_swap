/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjaber <mjaber@student.1337.ma>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:46:59 by mjaber            #+#    #+#             */
/*   Updated: 2025/12/16 18:47:06 by mjaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>

typedef struct s_stack
{
	int				value;
	int				index;
	int				pos;
	int				target_pos;
	int				cost_a;
	int				cost_b;
	struct s_stack	*next;
}	t_stack;

/* Utils */
long		ft_atoi(const char *str);
void		ft_putstr_fd(char *s, int fd);
void		error_exit(t_stack **a, t_stack **b);
void		free_stack(t_stack **stack);
int			ft_lstsize(t_stack *stack);
t_stack		*ft_lstnew(int value);
void		ft_lstadd_back(t_stack **stack, t_stack *new);
t_stack		*ft_lstlast(t_stack *stack);

/* Moves */
void		sa(t_stack **a, int print);
void		sb(t_stack **b, int print);
void		ss(t_stack **a, t_stack **b, int print);
void		pa(t_stack **a, t_stack **b, int print);
void		pb(t_stack **a, t_stack **b, int print);
void		ra(t_stack **a, int print);
void		rb(t_stack **b, int print);
void		rr(t_stack **a, t_stack **b, int print);
void		rra(t_stack **a, int print);
void		rrb(t_stack **b, int print);
void		rrr(t_stack **a, t_stack **b, int print);

/* Sorting */
int			is_sorted(t_stack *stack);
void		simple_sort(t_stack **a);
void		sort_chunks(t_stack **a, t_stack **b);
void		assign_indices(t_stack *a);

/* Parsing */
void		parse_args(int argc, char **argv, t_stack **a);
char		**ft_split(char const *s, char c);

#endif
