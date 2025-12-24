# Push_swap with BOGOSS ALGO

*This project has been created as part of the 42 curriculum by mjaber.*

## Description

Push_swap is an algorithmic challenge focused on data sorting optimization. The project involves sorting a stack of integers using a limited set of operations, with the goal of achieving the minimum number of moves possible.

The program receives a list of random integers and must output the shortest sequence of instructions to sort them in ascending order using two stacks (a and b) and a predefined set of operations. This project explores fundamental concepts of algorithm complexity, optimization strategies, and efficient sorting techniques.

The challenge lies not just in sorting the numbers, but in finding the most efficient sorting method that adapts to different input sizes and arrangements.

## Instructions

### Compilation

To compile the mandatory part:
```bash
make
```

To compile the bonus part (checker program):
```bash
make bonus
```

To clean object files:
```bash
make clean
```

To remove all generated files:
```bash
make fclean
```

To recompile:
```bash
make re
```

### Usage

**Push_swap program:**
```bash
./push_swap [list of integers]
```

Examples:
```bash
./push_swap 2 1 3 6 5 8
./push_swap "3 2 1"
./push_swap 42
```

**Checker program (bonus):**
```bash
./push_swap [arguments] | ./checker [arguments]
```

Example:
```bash
ARG="4 67 3 87 23"; ./push_swap $ARG | ./checker $ARG
```

The checker will output:
- `OK` if the stack is sorted correctly
- `KO` if the stack is not sorted or an error occurred
- `Error` if invalid arguments are provided

### Available Operations

- `sa`: swap first 2 elements of stack a
- `sb`: swap first 2 elements of stack b
- `ss`: sa and sb simultaneously
- `pa`: push top element from b to a
- `pb`: push top element from a to b
- `ra`: rotate stack a (shift up all elements)
- `rb`: rotate stack b (shift up all elements)
- `rr`: ra and rb simultaneously
- `rra`: reverse rotate stack a (shift down all elements)
- `rrb`: reverse rotate stack b (shift down all elements)
- `rrr`: rra and rrb simultaneously

### Error Handling

The program displays "Error\n" on standard error for:
- Non-integer arguments
- Numbers exceeding integer limits (INT_MIN to INT_MAX)
- Duplicate values
- Invalid input format

### Performance Benchmarks

The sorting algorithm achieves the following performance targets:

**For 100% validation:**
- 100 random numbers: < 700 operations
- 500 random numbers: ≤ 5500 operations

**For 80% validation (minimum):**
- Various combinations of operation counts for different input sizes

## Algorithm Strategy

The implementation uses a **chunk-based radix-inspired sorting approach**:

1. **Small inputs (2-3 elements)**: Hardcoded optimal solutions
2. **Medium inputs (5 elements)**: Specialized sorting with stack b
3. **Large inputs (>5 elements)**: Chunk-based algorithm
   - Elements are indexed (ranked) from 0 to N-1
   - Numbers are pushed to stack b in chunks based on index ranges
   - Larger chunks for bigger inputs (range=35 for >100 elements, range=15 otherwise)
   - Elements are then pushed back to stack a in descending order
   - Uses optimal rotation direction based on element position

This approach provides O(n²) worst-case performance with excellent practical results for the required benchmarks.

## Resources

### Classic References
- **Big-O Notation and Algorithm Complexity**: Understanding time and space complexity
- **Sorting Algorithms**: Quick Sort, Merge Sort, Radix Sort principles
- **Stack Data Structures**: LIFO operations and applications
- **Algorithm Optimization**: Trade-offs between simplicity and efficiency

### Recommended Reading
- [Sorting Algorithm Visualizations](https://visualgo.net/en/sorting)
- [Stack Data Structure (GeeksforGeeks)](https://www.geeksforgeeks.org/stack-data-structure/)
- [Big-O Cheat Sheet](https://www.bigocheatsheet.com/)
- 42's Push_swap subject PDF (version 10.0)

### AI Usage

AI tools were used in the following capacity for this project:

**Tasks where AI was utilized:**
- **Code review and debugging**: Identifying edge cases in parsing and error handling
- **Algorithm research**: Understanding different sorting strategies and their trade-offs
- **Documentation**: Structuring the README and clarifying technical explanations
- **Testing strategy**: Generating test cases for various input sizes

**Project components developed independently:**
- Core sorting algorithm implementation (chunk-based approach)
- Stack operations and move functions
- Parsing logic and input validation
- Bonus checker program with get_next_line integration

All AI-generated suggestions were thoroughly reviewed, tested, and modified to ensure full understanding and compliance with project requirements. The final algorithm design and optimization decisions were made independently based on benchmark testing and performance analysis.

## Project Structure

```
push_swap/
├── Makefile
├── README.md
├── srcs/
│   ├── main.c              # Entry point for push_swap
│   ├── push_swap.h         # Header file
│   ├── parsing.c           # Argument parsing and validation
│   ├── utils.c             # Utility functions (atoi, list operations)
│   ├── split.c             # String splitting for space-separated args
│   ├── moves_1.c           # Stack operations (sa, sb, ss, pa, pb)
│   ├── moves_2.c           # Stack operations (ra, rb, rra, rrb)
│   ├── sort_utils.c        # Sorting utilities (is_sorted, assign_indices, simple_sort)
│   ├── sort_middle.c       # Sorting for 5 elements
│   └── sort_big.c          # Chunk-based sorting for large inputs
└── bonus/
    ├── checker_bonus.c     # Checker program main
    ├── checker_bonus.h     # Bonus header file
    ├── get_next_line_bonus.c  # GNL for reading instructions
    ├── parsing_bonus.c     # Bonus parsing functions
    ├── utils_bonus.c       # Bonus utility functions
    ├── utils2_bonus.c      # Additional utilities
    ├── split_bonus.c       # Bonus split function
    ├── moves1_bonus.c      # Bonus stack operations (sa-pb)
    ├── moves2_bonus.c      # Bonus stack operations (ra-rrb)
    ├── moves3_bonus.c      # Bonus stack operations (rrr)
    └── sort_utils_bonus.c  # Bonus sorting utilities
```

## Testing

To test the program with random numbers:
```bash
ARG=$(seq 1 100 | shuf | tr '\n' ' '); ./push_swap $ARG | wc -l
ARG=$(seq 1 100 | shuf | tr '\n' ' '); ./push_swap $ARG | ./checker $ARG
```

For performance testing:
```bash
# Test with 100 numbers (should be < 700 operations)
for i in {1..10}; do ARG=$(seq 1 100 | shuf | tr '\n' ' '); ./push_swap $ARG | wc -l; done

# Test with 500 numbers (should be ≤ 5500 operations)
for i in {1..5}; do ARG=$(seq 1 500 | shuf | tr '\n' ' '); ./push_swap $ARG | wc -l; done
```

---

**Note**: This project strictly adheres to the 42 Norm coding standards and includes comprehensive error handling for all edge cases.
