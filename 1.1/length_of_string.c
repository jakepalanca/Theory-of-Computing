#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Recursive function to calculate the length of a string, illustrating
// principles from the theory of computation.
int recursiveLength(char *str) {
  // --- BASE CASE: The Empty String (ε) ---
  // In the theory of computation, the length of the empty string (ε) is defined as 0.
  // This is our fundamental base case, a fact we can look up without further computation.
  if (strlen(str) == 0) { // Check if the string is empty.
    // Example: If str is "" (empty), then its length is 0.
    return 0;
  }

  // --- RECURSIVE STEP: Reducing the String by One Character ---
  // We define the length of a non-empty string recursively by relating it to the
  // length of a shorter string.
  //
  // If we have a string w = ax, where 'a' is a single character (a symbol from our alphabet Σ)
  // and 'x' is the remaining part of the string, then the length of w can be expressed as:
  // |w| = |ax| = 1 + |x|
  //
  // In other words, the length of w is 1 (for the character 'a') plus the length of the
  // rest of the string ('x').

  // 1. Recursive call with a smaller string:
  //    - str + 1: This creates a pointer to the substring of str starting from the
  //              second character. We are effectively removing the first character.
  //              Example: If str is "abc", then str + 1 points to "bc".
  //    - We recursively call recursiveLength with this shorter string.
  //    - This breaks down the problem into a smaller, similar subproblem.
  int restLength = recursiveLength(str + 1);

  // 2. Calculate the length of the current string:
  //    - The length of the current string is 1 (for the first character that we removed)
  //      plus the length of the rest of the string (which we got from the recursive call).
  int length = 1 + restLength;

  // Example:
  // If str is "abc":
  //   - 1st recursive call: recursiveLength("bc")
  //   - 2nd recursive call: recursiveLength("c")
  //   - 3rd recursive call: recursiveLength("")  <- Base case! Returns 0
  //   - Now, unwinding the recursion:
  //     - 3rd call returns 0
  //     - 2nd call returns 1 + 0 = 1
  //     - 1st call returns 1 + 1 = 2
  //     - Original call returns 1 + 2 = 3

  // 3. Return the calculated length.
  return length;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <string>\n", argv[0]);
    return 1;
  }

  char *string = argv[1];

  // Call our recursive length function.
  int len = recursiveLength(string);

  printf("Length of string '%s': %d\n", string, len);

  return 0;
}