#!/bin/bash

# Quick test script for push_swap

# Test 500 numbers - 5 runs
echo "Testing 500 numbers (5 runs)..."
echo "================================"

total=0
for i in {1..5}; do
    ARG=$(seq 1 500 | shuf | tr '\n' ' ')
    ops=$(./push_swap $ARG | wc -l)
    echo "Run $i: $ops operations"
    echo "the total is $ops"
    total=$((total + ops))
    
    # Verify with checker if available
    if [ -f "./checker" ]; then
        result=$(./push_swap $ARG | ./checker $ARG)
        if [ "$result" != "OK" ]; then
            echo "  ERROR: Sort failed!"
        fi
    fi
done

avg=$((total / 5))
echo ""
echo "Average: $avg operations"
echo ""

if [ $avg -lt 5500 ]; then
    echo "✓ PASS - Under 5500 (100%)"
elif [ $avg -lt 8500 ]; then
    echo "⚠ PASS - Under 8500 (80%)"
else
    echo "✗ FAIL - Over 8500"
fi

# Test 100 numbers - 5 runs
echo ""
echo "Testing 100 numbers (5 runs)..."
echo "================================"

total=0
for i in {1..5}; do
    ARG=$(seq 1 100 | shuf | tr '\n' ' ')
    ops=$(./push_swap $ARG | wc -l)
    echo "Run $i: $ops operations"
    total=$((total + ops))
    
    # Verify with checker if available
    if [ -f "./checker" ]; then
        result=$(./push_swap $ARG | ./checker $ARG)
        if [ "$result" != "OK" ]; then
            echo "  ERROR: Sort failed!"
        fi
    fi
done

avg=$((total / 5))
echo ""
echo "Average: $avg operations"
echo ""

if [ $avg -lt 700 ]; then
    echo "✓ PASS - Under 700 (100%)"
elif [ $avg -lt 1100 ]; then
    echo "⚠ PASS - Under 1100 (80%)"
else
    echo "✗ FAIL - Over 1100"
fi
