#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Recursive function to reverse a string, demonstrating principles from the
// theory of computation.
char *recursiveReverse(char *str) {
  // --- BASE CASE: The Empty String (ε) ---
  // In the theory of computation, the reverse of the empty string (ε) is itself (ε).
  // This forms our fundamental base case.
  if (strlen(str) == 0) { // Check if the string is empty.
    // Example: If str is "" (empty), its reverse is also "".
    char *reversed = (char *)malloc(1); // Allocate memory for the empty string (null terminator only).
     if (reversed == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1); // Or handle the error appropriately
    }
    reversed[0] = '\0'; // Set the null terminator.
    return reversed;
  }

  // --- RECURSIVE STEP: Building the Reverse Character by Character ---
  // We define the reverse of a non-empty string recursively by relating it to the
  // reverse of a shorter string.
  //
  // If we have a string w = ax, where 'a' is a single character (a symbol from our
  // alphabet Σ) and 'x' is the remaining part of the string, then the reverse of w
  // (denoted as w^R) can be expressed as:
  // w^R = (ax)^R = x^R a
  //
  // In other words, the reverse of w is the reverse of the rest of the string ('x')
  // followed by the first character ('a').

  // 1. Recursive call with a smaller string:
  //    - str + 1: This creates a pointer to the substring of str starting from the
  //              second character, effectively removing the first character.
  //              Example: If str is "abc", then str + 1 points to "bc".
  //    - We recursively call recursiveReverse with this shorter string.
  //    - This breaks down the problem into a smaller, similar subproblem.
  char *reversedRest = recursiveReverse(str + 1);

  // 2. Allocate memory for the reversed string:
  //    - We need space for all characters of the original string plus the null terminator.
  char *reversed = (char *)malloc(strlen(str) + 1);
  if (reversed == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1); // Or handle the error appropriately
    }

  // 3. Build the reversed string:
  //    - Copy the result of the recursive call (reversedRest) to the beginning of
  //      the reversed string.
  //      Example: If str is "abc" and reversedRest is "cb", then reversed becomes "cb".
  strcpy(reversed, reversedRest);
  //    - Append the first character of the original string (str[0]) to the end of
  //      the reversed string.
  //      Example: If str[0] is 'a', then reversed becomes "cba".
  reversed[strlen(str) - 1] = str[0];
  //    - Add the null terminator to mark the end of the string.
  reversed[strlen(str)] = '\0';

  // 4. Free the dynamically allocated memory for the temporary string 'reversedRest'.
  //    - The recursive call to recursiveReverse allocated memory for 'reversedRest'.
  //    - We are responsible for freeing this memory to prevent memory leaks.
  free(reversedRest);

  // 5. Return the reversed string.
  return reversed;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <string>\n", argv[0]);
    return 1;
  }

  char *string = argv[1];

  // Call our recursive reverse function.
  char *reversedString = recursiveReverse(string);

  printf("Reversed string: %s\n", reversedString);

  // Free the dynamically allocated memory for the reversed string.
  free(reversedString);

  return 0;
}