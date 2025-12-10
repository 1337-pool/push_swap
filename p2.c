/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: your_login <your_login@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/01 00:00:00 by your_login        #+#    #+#             */
/*   Updated: 2024/01/01 00:00:00 by your_login       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <unistd.h>

typedef struct s_stack {
    int *array;
    int size;
    int capacity;
} t_stack;

// ============ UTILITY FUNCTIONS ============

void ft_putstr_fd(char *str, int fd) {
    while (*str)
        write(fd, str++, 1);
}

void print_error(void) {
    ft_putstr_fd("Error\n", 2);
}

int ft_strcmp(char *s1, char *s2) {
    int i = 0;
    
    while (s1[i] && s2[i] && s1[i] == s2[i])
        i++;
    return (unsigned char)s1[i] - (unsigned char)s2[i];
}

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

// ============ STACK OPERATIONS (SILENT) ============

void do_sa(t_stack *a) {
    if (a->size < 2) return;
    int temp = a->array[0];
    a->array[0] = a->array[1];
    a->array[1] = temp;
}

void do_sb(t_stack *b) {
    if (b->size < 2) return;
    int temp = b->array[0];
    b->array[0] = b->array[1];
    b->array[1] = temp;
}

void do_ss(t_stack *a, t_stack *b) {
    if (a->size >= 2) {
        int temp = a->array[0];
        a->array[0] = a->array[1];
        a->array[1] = temp;
    }
    if (b->size >= 2) {
        int temp = b->array[0];
        b->array[0] = b->array[1];
        b->array[1] = temp;
    }
}

void do_pa(t_stack *a, t_stack *b) {
    if (b->size == 0) return;
    
    int i;
    for (i = a->size; i > 0; i--)
        a->array[i] = a->array[i - 1];
    
    a->array[0] = b->array[0];
    a->size++;
    
    for (i = 0; i < b->size - 1; i++)
        b->array[i] = b->array[i + 1];
    b->size--;
}

void do_pb(t_stack *a, t_stack *b) {
    if (a->size == 0) return;
    
    int i;
    for (i = b->size; i > 0; i--)
        b->array[i] = b->array[i - 1];
    
    b->array[0] = a->array[0];
    b->size++;
    
    for (i = 0; i < a->size - 1; i++)
        a->array[i] = a->array[i + 1];
    a->size--;
}

void do_ra(t_stack *a) {
    if (a->size < 2) return;
    int temp = a->array[0];
    int i;
    for (i = 0; i < a->size - 1; i++)
        a->array[i] = a->array[i + 1];
    a->array[a->size - 1] = temp;
}

void do_rb(t_stack *b) {
    if (b->size < 2) return;
    int temp = b->array[0];
    int i;
    for (i = 0; i < b->size - 1; i++)
        b->array[i] = b->array[i + 1];
    b->array[b->size - 1] = temp;
}

void do_rr(t_stack *a, t_stack *b) {
    if (a->size >= 2) {
        int temp = a->array[0];
        int i;
        for (i = 0; i < a->size - 1; i++)
            a->array[i] = a->array[i + 1];
        a->array[a->size - 1] = temp;
    }
    if (b->size >= 2) {
        int temp = b->array[0];
        int i;
        for (i = 0; i < b->size - 1; i++)
            b->array[i] = b->array[i + 1];
        b->array[b->size - 1] = temp;
    }
}

void do_rra(t_stack *a) {
    if (a->size < 2) return;
    int temp = a->array[a->size - 1];
    int i;
    for (i = a->size - 1; i > 0; i--)
        a->array[i] = a->array[i - 1];
    a->array[0] = temp;
}

void do_rrb(t_stack *b) {
    if (b->size < 2) return;
    int temp = b->array[b->size - 1];
    int i;
    for (i = b->size - 1; i > 0; i--)
        b->array[i] = b->array[i - 1];
    b->array[0] = temp;
}

void do_rrr(t_stack *a, t_stack *b) {
    if (a->size >= 2) {
        int temp = a->array[a->size - 1];
        int i;
        for (i = a->size - 1; i > 0; i--)
            a->array[i] = a->array[i - 1];
        a->array[0] = temp;
    }
    if (b->size >= 2) {
        int temp = b->array[b->size - 1];
        int i;
        for (i = b->size - 1; i > 0; i--)
            b->array[i] = b->array[i - 1];
        b->array[0] = temp;
    }
}

// ============ INSTRUCTION EXECUTION ============

int execute_instruction(char *instruction, t_stack *a, t_stack *b) {
    if (ft_strcmp(instruction, "sa\n") == 0)
        do_sa(a);
    else if (ft_strcmp(instruction, "sb\n") == 0)
        do_sb(b);
    else if (ft_strcmp(instruction, "ss\n") == 0)
        do_ss(a, b);
    else if (ft_strcmp(instruction, "pa\n") == 0)
        do_pa(a, b);
    else if (ft_strcmp(instruction, "pb\n") == 0)
        do_pb(a, b);
    else if (ft_strcmp(instruction, "ra\n") == 0)
        do_ra(a);
    else if (ft_strcmp(instruction, "rb\n") == 0)
        do_rb(b);
    else if (ft_strcmp(instruction, "rr\n") == 0)
        do_rr(a, b);
    else if (ft_strcmp(instruction, "rra\n") == 0)
        do_rra(a);
    else if (ft_strcmp(instruction, "rrb\n") == 0)
        do_rrb(b);
    else if (ft_strcmp(instruction, "rrr\n") == 0)
        do_rrr(a, b);
    else
        return 0;
    return 1;
}

// ============ READ INSTRUCTIONS ============

char *read_line(void) {
    char *line = malloc(sizeof(char) * 5);
    int i = 0;
    int ret;
    
    if (!line)
        return NULL;
    
    while (1) {
        ret = read(0, &line[i], 1);
        if (ret <= 0 || line[i] == '\n') {
            line[i + 1] = '\0';
            break;
        }
        i++;
        if (i >= 4) {
            line[i] = '\0';
            return line;
        }
    }
    
    if (ret < 0 || (ret == 0 && i == 0)) {
        free(line);
        return NULL;
    }
    
    return line;
}

// ============ MAIN ============

int main(int argc, char **argv) {
    t_stack *a;
    t_stack *b;
    char *instruction;
    
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
    
    if (!parse_args(argc, argv, a) || has_duplicates(a)) {
        free_stack(a);
        free_stack(b);
        print_error();
        return 1;
    }
    
    while (1) {
        instruction = read_line();
        if (!instruction)
            break;
        
        if (!execute_instruction(instruction, a, b)) {
            free(instruction);
            free_stack(a);
            free_stack(b);
            print_error();
            return 1;
        }
        
        free(instruction);
    }
    
    if (is_sorted(a) && b->size == 0)
        ft_putstr_fd("OK\n", 1);
    else
        ft_putstr_fd("KO\n", 1);
    
    free_stack(a);
    free_stack(b);
    
    return 0;
}