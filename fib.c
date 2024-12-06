#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

// Define the widest possible integer type
typedef uint64_t fib_type;

// Array to store computed Fibonacci values for memoization
fib_type *memo = NULL;
int memo_size = 0;

// Core recursive Fibonacci function (no memoization)
fib_type fib_r_core(fib_type n) {
    if (n == 1) return 0;
    if (n == 2) return 1;
    return fib_r_core(n - 1) + fib_r_core(n - 2);
}

// Core iterative Fibonacci function (no memoization)
fib_type fib_i_core(fib_type n) {
    if (n == 1) return 0;
    if (n == 2) return 1;
    fib_type prev1 = 0, prev2 = 1, current = 0;
    for (fib_type i = 3; i <= n; i++) {
        current = prev1 + prev2;
        prev1 = prev2;
        prev2 = current;
    }
    return current;
}

// Wrapper recursive Fibonacci function (with memoization)
fib_type fib_r(fib_type n) {
    if (n == 1) return 0; // Base case
    if (n == 2) return 1; // Base case
    if (memo[n] != -1) return memo[n];
    memo[n] = fib_r(n - 1) + fib_r(n - 2);
    return memo[n];
}

// Wrapper iterative Fibonacci function (with memoization)
fib_type fib_i(fib_type n) {
    if (n == 1) return 0; // Base case
    if (n == 2) return 1; // Base case
    if (memo[n] != -1) return memo[n];
    memo[n] = fib_i_core(n);
    return memo[n];
}

// Initialize memoization array
void initialize_memo(fib_type n) {
    memo_size = n + 1;
    memo = (fib_type *)malloc(sizeof(fib_type) * memo_size);
    if (!memo) {
        printf("Error: Memory allocation failed.\n");
        exit(1);
    }
    for (int i = 0; i < memo_size; i++) {
        memo[i] = -1; // Initialize all values to -1
    }
}

// Main program
int main(int argc, char *argv[]) {
    // Validate input arguments
    if (argc != 3) {
        printf("Usage: ./fib <integer> <method (r/i)>\n");
        return 1;
    }

    // Parse command-line arguments
    fib_type n = atoi(argv[1]);
    char method = argv[2][0];

    if (method != 'r' && method != 'i') {
        printf("Invalid method. Use 'r' for recursive or 'i' for iterative.\n");
        return 1;
    }

    // Initialize memoization array
    initialize_memo(n);

    // Compute Fibonacci number
    fib_type result;
    if (method == 'r') {
        result = fib_r(n);
    } else {
        result = fib_i(n);
    }

    // Output the result
    printf("%lu\n", result);

    // Free memoization array
    free(memo);
    return 0;
}
