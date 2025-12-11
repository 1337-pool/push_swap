#include "push_swap.h"

int	main(int argc, char **argv)
{
	t_stack	*a;
	t_stack	*b;

	if (argc < 2)
		return (0);
	a = parse_args(argc, argv);
	if (!a)
		error_exit(NULL, NULL);
	if (is_sorted(a))
	{
		free_stack(&a);
		return (0);
	}
	b = NULL;
	sort_stack(&a, &b);
	free_stack(&a);
	free_stack(&b);
	return (0);
}