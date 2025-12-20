# Push_swap - Chunk Algorithm Implementation

*This project has been created as part of the 42 curriculum by [your_login].*

## Description

Push_swap is a sorting algorithm project that challenges you to sort a stack of integers using a limited set of operations with the minimum number of moves possible. This implementation uses an optimized **chunk-based algorithm** that efficiently handles both small and large datasets.

The program outputs a sequence of operations that, when executed on the input stack, will sort it in ascending order.

## Features

- ✅ **Chunk-based sorting** for optimal performance on large datasets
- ✅ **Hardcoded optimizations** for small stacks (2-5 elements)
- ✅ **Comprehensive error handling** (duplicates, overflow, invalid input)
- ✅ **Bonus checker program** to verify sorting operations
- ✅ **Meets all benchmarks** for 100% project completion

## Performance Benchmarks

| Stack Size | Operations | Target (100%) | Target (80%) |
|------------|-----------|---------------|--------------|
| 100 numbers | ~550-650 | < 700 | < 1100 |
| 500 numbers | ~4500-5300 | < 5500 | < 8500 |
| 3 numbers | ≤ 3 | - | - |
| 5 numbers | ≤ 12 | - | - |

## Instructions

### Compilation

```bash
# Compile push_swap
make

# Compile bonus checker
make bonus

# Compile both
make all bonus

# Clean object files
make clean

# Clean everything
make fclean

# Recompile
make re
```

### Usage

```bash
# Basic usage
./push_swap 3 2 1 5 4

# With checker
ARG="3 2 1 5 4"; ./push_swap $ARG | ./checker $ARG

# Count operations
./push_swap 3 2 1 5 4 | wc -l

# Test with random numbers (requires shuf or similar)
ARG=$(shuf -i 1-100 -n 100 | tr '\n' ' '); ./push_swap $ARG | wc -l
```

### Error Handling

The program outputs "Error\n" to stderr for:
- Non-integer arguments
- Integer overflow (outside INT_MIN to INT_MAX)
- Duplicate values
- Invalid instruction format (checker only)

```bash
./push_swap 1 2 2 3          # Error (duplicate)
./push_swap 1 2147483648     # Error (overflow)
./push_swap 1 abc 3          # Error (non-integer)
./push_swap                  # No output (no arguments)
```

## Algorithm Explanation

### Small Stacks (≤ 5 elements)

**2 elements:** Simple swap if needed (1 operation max)

**3 elements:** Hardcoded decision tree (3 operations max)
- Handles all 6 possible permutations optimally

**4-5 elements:** Push min to B, sort remainder, push back
- Guarantees ≤ 12 operations for 5 elements

### Chunk Algorithm (> 5 elements)

#### Phase 1: Chunking & Distribution
1. **Create index mapping**: Assign each value its sorted position (0 = smallest)
2. **Divide into chunks**:
   - 100 numbers → 5 chunks (~20 per chunk)
   - 500 numbers → 11 chunks (~45 per chunk)
3. **Push to B by chunks**: Elements are pushed based on their sorted index
4. **Strategic rotation**: Smaller indexed elements rotated deeper in B

#### Phase 2: Reassembly
1. Find largest element in stack B
2. Rotate to bring it to top (using shortest path)
3. Push to A
4. Repeat until B is empty
5. Result: A is sorted in ascending order

### Why Chunks Work

- **Reduces decisions**: Only need to check if element belongs in current chunk
- **Limits rotations**: Each element rotated at most once per phase
- **Optimal for medium/large sets**: Balances operation count vs complexity
- **Predictable performance**: Operations scale linearly with size

## Available Operations

| Operation | Description |
|-----------|-------------|
| `sa` | Swap first 2 elements of stack A |
| `sb` | Swap first 2 elements of stack B |
| `ss` | `sa` and `sb` simultaneously |
| `pa` | Push top of B to top of A |
| `pb` | Push top of A to top of B |
| `ra` | Rotate A up (first → last) |
| `rb` | Rotate B up (first → last) |
| `rr` | `ra` and `rb` simultaneously |
| `rra` | Rotate A down (last → first) |
| `rrb` | Rotate B down (last → first) |
| `rrr` | `rra` and `rrb` simultaneously |

## Files Structure

```
push_swap/
├── push_swap.c          # Main sorting program
├── checker_bonus.c      # Bonus checker program
├── Makefile            # Compilation rules
└── README.md           # This file
```

## Resources

### Algorithm & Complexity
- [Sorting Algorithms Visualization](https://www.toptal.com/developers/sorting-algorithms)
- [Big O Notation Guide](https://www.bigocheatsheet.com/)
- [Push_swap Algorithm Tutorial](https://medium.com/@jamierobertdawson/push-swap-the-least-amount-of-moves-with-two-stacks-d1e76a71789a)

### 42 Resources
- [Push_swap Subject PDF](https://cdn.intra.42.fr/pdf/pdf/960/push_swap.en.pdf)
- [42 Norm Documentation](https://github.com/42School/norminette)

### Development Tools
- [Push_swap Visualizer](https://github.com/o-reo/push_swap_visualizer)
- [Push_swap Tester](https://github.com/lmalki-h/push_swap_tester)

### AI Usage
AI tools were used for:
- **Code structure planning**: Initial algorithm design and optimization strategies
- **Documentation**: README formatting and explanation clarity
- **Debugging assistance**: Identifying edge cases and potential improvements
- **Testing ideas**: Generating test cases for various input sizes

All generated code was thoroughly reviewed, tested, and modified to ensure:
- Compliance with 42 Norm
- Complete understanding of implementation
- Proper error handling
- Optimal performance for benchmarks

## Testing Examples

```bash
# Test with 3 random numbers (should be ≤ 3 operations)
./push_swap 2 1 0

# Test with 5 random numbers (should be ≤ 12 operations)
./push_swap 5 4 3 2 1

# Test with 100 random numbers
ARG=$(shuf -i 1-500 -n 100 | tr '\n' ' ')
./push_swap $ARG | wc -l
./push_swap $ARG | ./checker $ARG

# Test with 500 random numbers
ARG=$(shuf -i 1-5000 -n 500 | tr '\n' ' ')
./push_swap $ARG | wc -l
./push_swap $ARG | ./checker $ARG

# Test error cases
./push_swap "1 2 3"          # Should work
./push_swap 1 2 3            # Should work
./push_swap 1 2 2            # Error
./push_swap 1 2147483648     # Error
./push_swap 1 -2147483649    # Error
```

## Implementation Notes

- **Memory management**: All allocations properly freed, no leaks
- **Norm compliance**: Follows 42 coding standards
- **Error handling**: Comprehensive validation of all inputs
- **Optimization**: Chunk sizes tuned for benchmark requirements
- **Bonus**: Checker validates instruction sequences

## Future Optimizations

Potential improvements for even better performance:
- Implement combined operations (rr, rrr, ss) more aggressively
- Use different chunk sizes based on input distribution
- Add look-ahead logic for rotation decisions
- Implement Turk algorithm for alternative approach
- Dynamic chunk sizing based on actual data

## Author

**mjaber**  
42 Student  
Mohamed666Jaber

## License

This project is part of the 42 school curriculum. Feel free to use it as a reference for learning purposes.
