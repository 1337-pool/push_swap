#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <stdlib.h>
# include <unistd.h>
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

/* Stack Operations */
void	sa(t_stack **a, int print);
void	sb(t_stack **b, int print);
void	ss(t_stack **a, t_stack **b, int print);
void	pa(t_stack **a, t_stack **b, int print);
void	pb(t_stack **b, t_stack **a, int print);
void	ra(t_stack **a, int print);
void	rb(t_stack **b, int print);
void	rr(t_stack **a, t_stack **b, int print);
void	rra(t_stack **a, int print);
void	rrb(t_stack **b, int print);
void	rrr(t_stack **a, t_stack **b, int print);

/* Stack Utils */
t_stack	*stack_new(int value);
void	stack_add_back(t_stack **stack, t_stack *new);
int		stack_size(t_stack *stack);
void	free_stack(t_stack **stack);
t_stack	*stack_bottom(t_stack *stack);
t_stack	*stack_before_bottom(t_stack *stack);

/* Parsing */
t_stack	*parse_args(int argc, char **argv);
int		is_sorted(t_stack *stack);
void	error_exit(t_stack **a, t_stack **b);

/* Algorithm */
void	sort_stack(t_stack **a, t_stack **b);
void	sort_three(t_stack **a);
void	sort_small(t_stack **a, t_stack **b);
void	sort_large(t_stack **a, t_stack **b);

/* Position & Cost */
void	assign_index(t_stack *a, int size);
void	assign_position(t_stack **stack);
void	get_target_position(t_stack **a, t_stack **b);
void	calculate_cost(t_stack **a, t_stack **b);
void	execute_cheapest(t_stack **a, t_stack **b);

/* Utils */
int		find_highest_index(t_stack *stack);
void	push_all_but_three(t_stack **a, t_stack **b);

#endif