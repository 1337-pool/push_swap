#!/bin/bash

# Colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
PUSH_SWAP="./push_swap"
CHECKER="./checker"

echo -e "${BLUE}========================================${NC}"
echo -e "${BLUE}   Push_swap 500 Numbers Test Suite${NC}"
echo -e "${BLUE}========================================${NC}\n"

# Check if programs exist
if [ ! -f "$PUSH_SWAP" ]; then
    echo -e "${RED}Error: push_swap not found. Compile first with 'make'${NC}"
    exit 1
fi

if [ ! -f "$CHECKER" ]; then
    echo -e "${YELLOW}Warning: checker not found. Skipping validation tests.${NC}"
    echo -e "${YELLOW}Compile with 'make bonus' to enable checker.${NC}\n"
    CHECKER=""
fi

# Test 1: Single test with 500 numbers
echo -e "${BLUE}Test 1: Single run with 500 random numbers${NC}"
echo "Generating 500 random numbers..."
ARG=$(seq 1 500 | shuf | tr '\n' ' ')
RESULT=$($PUSH_SWAP $ARG | wc -l | tr -d ' ')

echo -e "Operations used: ${YELLOW}$RESULT${NC}"

if [ $RESULT -lt 5500 ]; then
    echo -e "${GREEN}✓ PASS${NC} - Under 5500 operations (100% grade)\n"
elif [ $RESULT -lt 8500 ]; then
    echo -e "${YELLOW}⚠ PASS${NC} - Under 8500 operations (80%+ grade)\n"
else
    echo -e "${RED}✗ FAIL${NC} - Over 8500 operations\n"
fi

# Test with checker if available
if [ -n "$CHECKER" ]; then
    echo "Validating with checker..."
    CHECK_RESULT=$($PUSH_SWAP $ARG | $CHECKER $ARG)
    if [ "$CHECK_RESULT" == "OK" ]; then
        echo -e "${GREEN}✓ Stack correctly sorted${NC}\n"
    else
        echo -e "${RED}✗ Stack NOT sorted correctly${NC}\n"
    fi
fi

# Test 2: Multiple runs (10 tests)
echo -e "${BLUE}Test 2: Average over 10 runs with 500 numbers${NC}"
echo "Running 10 tests..."

TOTAL=0
MIN=999999
MAX=0
PASSED=0

for i in {1..10}; do
    ARG=$(seq 1 500 | shuf | tr '\n' ' ')
    RESULT=$($PUSH_SWAP $ARG | wc -l | tr -d ' ')
    
    echo -ne "Test $i/10: $RESULT operations"
    
    # Check with checker if available
    if [ -n "$CHECKER" ]; then
        CHECK_RESULT=$($PUSH_SWAP $ARG | $CHECKER $ARG)
        if [ "$CHECK_RESULT" == "OK" ]; then
            echo -e " ${GREEN}✓${NC}"
        else
            echo -e " ${RED}✗${NC}"
        fi
    else
        echo ""
    fi
    
    TOTAL=$((TOTAL + RESULT))
    
    if [ $RESULT -lt $MIN ]; then
        MIN=$RESULT
    fi
    
    if [ $RESULT -gt $MAX ]; then
        MAX=$RESULT
    fi
    
    if [ $RESULT -lt 5500 ]; then
        PASSED=$((PASSED + 1))
    fi
done

AVERAGE=$((TOTAL / 10))

echo ""
echo -e "${BLUE}Statistics:${NC}"
echo -e "  Average: ${YELLOW}$AVERAGE${NC} operations"
echo -e "  Minimum: ${GREEN}$MIN${NC} operations"
echo -e "  Maximum: ${RED}$MAX${NC} operations"
echo -e "  Passed (< 5500): ${GREEN}$PASSED/10${NC}"

if [ $AVERAGE -lt 5500 ]; then
    echo -e "\n${GREEN}✓ EXCELLENT${NC} - Average under 5500 (100% grade)"
elif [ $AVERAGE -lt 8500 ]; then
    echo -e "\n${YELLOW}⚠ GOOD${NC} - Average under 8500 (80%+ grade)"
else
    echo -e "\n${RED}✗ NEEDS IMPROVEMENT${NC} - Average over 8500"
fi

# Test 3: Edge cases with 500 numbers
echo -e "\n${BLUE}Test 3: Edge cases${NC}"

# Already sorted
echo -n "Already sorted (1-500): "
ARG=$(seq 1 500 | tr '\n' ' ')
RESULT=$($PUSH_SWAP $ARG | wc -l | tr -d ' ')
if [ $RESULT -eq 0 ]; then
    echo -e "${GREEN}✓ PASS${NC} (0 operations)"
else
    echo -e "${RED}✗ FAIL${NC} ($RESULT operations, expected 0)"
fi

# Reverse sorted
echo -n "Reverse sorted (500-1): "
ARG=$(seq 500 -1 1 | tr '\n' ' ')
RESULT=$($PUSH_SWAP $ARG | wc -l | tr -d ' ')
if [ $RESULT -lt 5500 ]; then
    echo -e "${GREEN}✓ PASS${NC} ($RESULT operations)"
else
    echo -e "${RED}✗ FAIL${NC} ($RESULT operations)"
fi

if [ -n "$CHECKER" ]; then
    CHECK_RESULT=$($PUSH_SWAP $ARG | $CHECKER $ARG)
    if [ "$CHECK_RESULT" == "OK" ]; then
        echo -e "  ${GREEN}✓ Correctly sorted${NC}"
    else
        echo -e "  ${RED}✗ NOT sorted${NC}"
    fi
fi

# Test 4: Also test 100 numbers
echo -e "\n${BLUE}Test 4: Bonus - Testing with 100 numbers${NC}"
echo "Running 5 tests with 100 numbers..."

TOTAL_100=0
for i in {1..5}; do
    ARG=$(seq 1 100 | shuf | tr '\n' ' ')
    RESULT=$($PUSH_SWAP $ARG | wc -l | tr -d ' ')
    echo -ne "Test $i/5: $RESULT operations"
    
    if [ -n "$CHECKER" ]; then
        CHECK_RESULT=$($PUSH_SWAP $ARG | $CHECKER $ARG)
        if [ "$CHECK_RESULT" == "OK" ]; then
            echo -e " ${GREEN}✓${NC}"
        else
            echo -e " ${RED}✗${NC}"
        fi
    else
        echo ""
    fi
    
    TOTAL_100=$((TOTAL_100 + RESULT))
done

AVERAGE_100=$((TOTAL_100 / 5))
echo -e "Average for 100 numbers: ${YELLOW}$AVERAGE_100${NC}"

if [ $AVERAGE_100 -lt 700 ]; then
    echo -e "${GREEN}✓ EXCELLENT${NC} - Under 700 operations (100% grade)"
elif [ $AVERAGE_100 -lt 1100 ]; then
    echo -e "${YELLOW}⚠ GOOD${NC} - Under 1100 operations (80%+ grade)"
else
    echo -e "${RED}✗ NEEDS IMPROVEMENT${NC} - Over 1100 operations"
fi

# Summary
echo -e "\n${BLUE}========================================${NC}"
echo -e "${BLUE}              SUMMARY${NC}"
echo -e "${BLUE}========================================${NC}"
echo -e "500 numbers average: ${YELLOW}$AVERAGE${NC} (target: < 5500)"
echo -e "100 numbers average: ${YELLOW}$AVERAGE_100${NC} (target: < 700)"

if [ $AVERAGE -lt 5500 ] && [ $AVERAGE_100 -lt 700 ]; then
    echo -e "\n${GREEN}🎉 ALL BENCHMARKS PASSED! Ready for 100% grade!${NC}"
elif [ $AVERAGE -lt 8500 ]; then
    echo -e "\n${YELLOW}⚠ Benchmarks passed for 80%+ grade${NC}"
else
    echo -e "\n${RED}❌ Benchmarks not met. Optimization needed.${NC}"
fi

echo ""