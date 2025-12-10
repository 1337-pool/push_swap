/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_login        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

// Stack structure
typedef struct s_stack {
    int *array;
    int size;
    int capacity;
} t_stack;

// ============ UTILITY FUNCTIONS ============

void ft_putstr(char *str) {
    while (*str)
        write(1, str++, 1);
}

void print_error(void) {
    write(2, "Error\n", 6);
}

// String to integer conversion with error checking
int ft_atoi(char *str, int *error) {
    long result = 0;
    int sign = 1;
    int i = 0;
    int has_digit = 0;
    
    while (str[i] == ' ' || str[i] == '\t' || str[i] == '\n')
        i++;
    
    if (str[i] == '-' || str[i] == '+') {
        if (str[i] == '-')
            sign = -1;
        i++;
    }
    
    while (str[i]) {
        if (str[i] >= '0' && str[i] <= '9') {
            has_digit = 1;
            result = result * 10 + (str[i] - '0');
            if ((sign == 1 && result > 2147483647) || 
                (sign == -1 && result > 2147483648)) {
                *error = 1;
                return 0;
            }
        } else {
            *error = 1;
            return 0;
        }
        i++;
    }
    
    if (!has_digit) {
        *error = 1;
        return 0;
    }
    
    return (int)(result * sign);
}

// ============ STACK MANAGEMENT ============

t_stack *init_stack(int capacity) {
    t_stack *stack = malloc(sizeof(t_stack));
    if (!stack)
        return NULL;
    
    stack->array = malloc(sizeof(int) * capacity);
    if (!stack->array) {
        free(stack);
        return NULL;
    }
    
    stack->size = 0;
    stack->capacity = capacity;
    return stack;
}

void free_stack(t_stack *stack) {
    if (stack) {
        if (stack->array)
            free(stack->array);
        free(stack);
    }
}

int parse_args(int argc, char **argv, t_stack *a) {
    int i, error = 0;
    
    for (i = 1; i < argc; i++) {
        a->array[a->size] = ft_atoi(argv[i], &error);
        if (error)
            return 0;
        a->size++;
    }
    
    return 1;
}

int has_duplicates(t_stack *stack) {
    int i, j;
    
    for (i = 0; i < stack->size; i++) {
        for (j = i + 1; j < stack->size; j++) {
            if (stack->array[i] == stack->array[j])
                return 1;
        }
    }
    return 0;
}

int is_sorted(t_stack *stack) {
    int i;
    
    for (i = 0; i < stack->size - 1; i++) {
        if (stack->array[i] > stack->array[i + 1])
            return 0;
    }
    return 1;
}

// ============ STACK OPERATIONS ============

void sa(t_stack *a) {
    if (a->size < 2) return;
    int temp = a->array[0];
    a->array[0] = a->array[1];
    a->array[1] = temp;
    ft_putstr("sa\n");
}

void sb(t_stack *b) {
    if (b->size < 2) return;
    int temp = b->array[0];
    b->array[0] = b->array[1];
    b->array[1] = temp;
    ft_putstr("sb\n");
}

void ss(t_stack *a, t_stack *b) {
    int swapped = 0;
    if (a->size >= 2) {
        int temp = a->array[0];
        a->array[0] = a->array[1];
        a->array[1] = temp;
        swapped = 1;
    }
    if (b->size >= 2) {
        int temp = b->array[0];
        b->array[0] = b->array[1];
        b->array[1] = temp;
        swapped = 1;
    }
    if (swapped)
        ft_putstr("ss\n");
}

void pa(t_stack *a, t_stack *b) {
    if (b->size == 0) return;
    
    int i;
    for (i = a->size; i > 0; i--)
        a->array[i] = a->array[i - 1];
    
    a->array[0] = b->array[0];
    a->size++;
    
    for (i = 0; i < b->size - 1; i++)
        b->array[i] = b->array[i + 1];
    b->size--;
    
    ft_putstr("pa\n");
}

void pb(t_stack *a, t_stack *b) {
    if (a->size == 0) return;
    
    int i;
    for (i = b->size; i > 0; i--)
        b->array[i] = b->array[i - 1];
    
    b->array[0] = a->array[0];
    b->size++;
    
    for (i = 0; i < a->size - 1; i++)
        a->array[i] = a->array[i + 1];
    a->size--;
    
    ft_putstr("pb\n");
}

void ra(t_stack *a) {
    if (a->size < 2) return;
    int temp = a->array[0];
    int i;
    for (i = 0; i < a->size - 1; i++)
        a->array[i] = a->array[i + 1];
    a->array[a->size - 1] = temp;
    ft_putstr("ra\n");
}

void rb(t_stack *b) {
    if (b->size < 2) return;
    int temp = b->array[0];
    int i;
    for (i = 0; i < b->size - 1; i++)
        b->array[i] = b->array[i + 1];
    b->array[b->size - 1] = temp;
    ft_putstr("rb\n");
}

void rr(t_stack *a, t_stack *b) {
    int rotated = 0;
    if (a->size >= 2) {
        int temp = a->array[0];
        int i;
        for (i = 0; i < a->size - 1; i++)
            a->array[i] = a->array[i + 1];
        a->array[a->size - 1] = temp;
        rotated = 1;
    }
    if (b->size >= 2) {
        int temp = b->array[0];
        int i;
        for (i = 0; i < b->size - 1; i++)
            b->array[i] = b->array[i + 1];
        b->array[b->size - 1] = temp;
        rotated = 1;
    }
    if (rotated)
        ft_putstr("rr\n");
}

void rra(t_stack *a) {
    if (a->size < 2) return;
    int temp = a->array[a->size - 1];
    int i;
    for (i = a->size - 1; i > 0; i--)
        a->array[i] = a->array[i - 1];
    a->array[0] = temp;
    ft_putstr("rra\n");
}

void rrb(t_stack *b) {
    if (b->size < 2) return;
    int temp = b->array[b->size - 1];
    int i;
    for (i = b->size - 1; i > 0; i--)
        b->array[i] = b->array[i - 1];
    b->array[0] = temp;
    ft_putstr("rrb\n");
}

void rrr(t_stack *a, t_stack *b) {
    int rotated = 0;
    if (a->size >= 2) {
        int temp = a->array[a->size - 1];
        int i;
        for (i = a->size - 1; i > 0; i--)
            a->array[i] = a->array[i - 1];
        a->array[0] = temp;
        rotated = 1;
    }
    if (b->size >= 2) {
        int temp = b->array[b->size - 1];
        int i;
        for (i = b->size - 1; i > 0; i--)
            b->array[i] = b->array[i - 1];
        b->array[0] = temp;
        rotated = 1;
    }
    if (rotated)
        ft_putstr("rrr\n");
}

// ============ SORTING HELPERS ============

int find_min(t_stack *stack) {
    int min = stack->array[0];
    int i;
    
    for (i = 1; i < stack->size; i++) {
        if (stack->array[i] < min)
            min = stack->array[i];
    }
    return min;
}

int find_min_index(t_stack *stack) {
    int min = stack->array[0];
    int min_pos = 0;
    int i;
    
    for (i = 1; i < stack->size; i++) {
        if (stack->array[i] < min) {
            min = stack->array[i];
            min_pos = i;
        }
    }
    return min_pos;
}

int find_max_index(t_stack *stack) {
    int max = stack->array[0];
    int max_pos = 0;
    int i;
    
    for (i = 1; i < stack->size; i++) {
        if (stack->array[i] > max) {
            max = stack->array[i];
            max_pos = i;
        }
    }
    return max_pos;
}

// ============ SMALL STACK SORTING ============

void sort_two(t_stack *a) {
    if (a->array[0] > a->array[1])
        sa(a);
}

void sort_three(t_stack *a) {
    int first = a->array[0];
    int second = a->array[1];
    int third = a->array[2];
    
    if (first > second && second < third && first < third)
        sa(a);
    else if (first > second && second > third) {
        sa(a);
        rra(a);
    }
    else if (first > second && second < third && first > third)
        ra(a);
    else if (first < second && second > third && first < third) {
        sa(a);
        ra(a);
    }
    else if (first < second && second > third && first > third)
        rra(a);
}

void sort_small(t_stack *a, t_stack *b) {
    int size = a->size;
    
    if (size == 2) {
        sort_two(a);
        return;
    }
    
    if (size == 3) {
        sort_three(a);
        return;
    }
    
    while (size > 3) {
        int min_pos = find_min_index(a);
        
        if (min_pos <= a->size / 2) {
            while (min_pos-- > 0)
                ra(a);
        } else {
            while (min_pos++ < a->size)
                rra(a);
        }
        
        pb(a, b);
        size--;
    }
    
    sort_three(a);
    
    while (b->size > 0)
        pa(a, b);
}

// ============ CHUNK SORTING ============

int *create_sorted_copy(t_stack *a) {
    int *sorted = malloc(sizeof(int) * a->size);
    int i, j;
    
    for (i = 0; i < a->size; i++)
        sorted[i] = a->array[i];
    
    for (i = 0; i < a->size - 1; i++) {
        for (j = 0; j < a->size - i - 1; j++) {
            if (sorted[j] > sorted[j + 1]) {
                int temp = sorted[j];
                sorted[j] = sorted[j + 1];
                sorted[j + 1] = temp;
            }
        }
    }
    
    return sorted;
}

int get_sorted_index(int *sorted_array, int size, int value) {
    int i;
    
    for (i = 0; i < size; i++) {
        if (sorted_array[i] == value)
            return i;
    }
    return -1;
}

void push_back_sorted(t_stack *a, t_stack *b) {
    while (b->size > 0) {
        int max_pos = find_max_index(b);
        
        if (max_pos <= b->size / 2) {
            while (max_pos-- > 0)
                rb(b);
        } else {
            while (max_pos++ < b->size)
                rrb(b);
        }
        
        pa(a, b);
    }
}

void chunk_sort(t_stack *a, t_stack *b) {
    int total_size = a->size;
    int chunk_size;
    int *sorted_array;
    int pushed = 0;
    int current_chunk = 0;
    
    if (total_size <= 100)
        chunk_size = total_size / 5;
    else
        chunk_size = total_size / 11;
    
    sorted_array = create_sorted_copy(a);
    
    while (pushed < total_size) {
        int chunk_max = (current_chunk + 1) * chunk_size;
        int rotations = 0;
        
        while (a->size > 0 && rotations < total_size) {
            int current_value = a->array[0];
            int sorted_pos = get_sorted_index(sorted_array, total_size, current_value);
            
            if (sorted_pos < chunk_max) {
                pb(a, b);
                pushed++;
                rotations = 0;
                
                if (b->size > 1) {
                    int b_top_index = get_sorted_index(sorted_array, total_size, b->array[0]);
                    if (b_top_index < current_chunk * chunk_size + chunk_size / 2)
                        rb(b);
                }
            } else {
                ra(a);
                rotations++;
            }
            
            if (pushed >= chunk_max) {
                current_chunk++;
                break;
            }
        }
    }
    
    free(sorted_array);
    push_back_sorted(a, b);
}

// ============ MAIN ============

int main(int argc, char **argv) {
    t_stack *a;
    t_stack *b;
    
    if (argc < 2)
        return 0;
    
    a = init_stack(argc - 1);
    b = init_stack(argc - 1);
    
    if (!a || !b) {
        free_stack(a);
        free_stack(b);
        print_error();
        return 1;
    }
    
    if (!parse_args(argc, argv, a)) {
        free_stack(a);
        free_stack(b);
        print_error();
        return 1;
    }
    
    if (has_duplicates(a)) {
        free_stack(a);
        free_stack(b);
        print_error();
        return 1;
    }
    
    if (is_sorted(a)) {
        free_stack(a);
        free_stack(b);
        return 0;
    }
    
    if (a->size <= 5)
        sort_small(a, b);
    else
        chunk_sort(a, b);
    
    free_stack(a);
    free_stack(b);
    
    return 0;
}