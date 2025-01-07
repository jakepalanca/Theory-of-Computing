#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Recursive function to concatenate two strings, demonstrating principles from
// the theory of computation.
char *recursiveConcat(char *str1, char *str2) {
  // --- BASE CASE: The Empty String (ε) ---
  // In the theory of computation, the empty string (often represented as ε)
  // is the identity element for concatenation. This means that for any string s:
  // εs = sε = s
  //
  // Our base case handles this fundamental rule.
  if (strlen(str1) == 0) { // Check if str1 is the empty string.
    // Example: If str1 is "" (empty) and str2 is "hello", then we are essentially
    // performing "" + "hello" which, according to the theory, should just be "hello".

    // Allocate memory to store the result (a copy of str2).
    // We need space for each character in str2 plus the null terminator '\0'.
    char *result = (char *)malloc(strlen(str2) + 1);
    if (result == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1); // Or handle the error appropriately
    }

    // Copy str2 into the newly allocated memory.
    strcpy(result, str2);

    // Return the copy of str2. This satisfies the rule εs = s.
    return result;
  }

  // --- RECURSIVE STEP: Building Concatenation Character by Character ---
  // The recursive step embodies the idea that we can build up string concatenation
  // by sequentially adding characters.
  //
  // If we have a string s = ax, where 'a' is a single character and 'x' is the
  // remaining part of the string, then concatenating s with another string t can
  // be defined as:
  // st = a(xt)
  //
  // In other words, we take the first character of s ('a') and concatenate it
  // with the result of concatenating the rest of s ('x') with t.

  // 1. Allocate memory for the final concatenated string.
  //    We need space for all characters of str1, all characters of str2, and the null terminator.
  char *result = (char *)malloc(strlen(str1) + strlen(str2) + 1);
  if (result == NULL) {
        fprintf(stderr, "Memory allocation failed!\n");
        exit(1); // Or handle the error appropriately
  }

  // 2. Copy the first character of str1 to the beginning of the result.
  //    Example: If str1 is "abc" and str2 is "def", then result[0] becomes 'a'.
  result[0] = str1[0];
  result[1] = '\0'; // Null-terminate result for now (we've only added one character).

  // 3. Recursively concatenate the rest of str1 with str2.
  //    - str1 + 1:  This creates a pointer to the substring of str1 starting from
  //                the second character.
  //                Example: If str1 is "abc", then str1 + 1 points to "bc".
  //    - We recursively call recursiveConcat with the remainder of str1 and str2.
  //    - This breaks down the problem into a smaller, similar subproblem.
  //    - The result of this recursive call is a new string (dynamically allocated),
  //      which is stored in the temporary pointer 'temp'.
  char *temp = recursiveConcat(str1 + 1, str2);
  // Example:
  // If str1 is "abc" and str2 is "def":
  //   - 1st recursive call: recursiveConcat("bc", "def")
  //   - 2nd recursive call: recursiveConcat("c", "def")
  //   - 3rd recursive call: recursiveConcat("", "def")  <- Base case! Returns a copy of "def"

  // 4. Concatenate the first character (already in result) with the result of the recursive call (temp).
  //    - We use strcat to append the string pointed to by 'temp' to the end of 'result'.
  //    - Example: If result is "a" and temp is "bcdef", then after strcat, result becomes "abcdef".
  strcat(result, temp);

  // 5. Free the dynamically allocated memory for the temporary string 'temp'.
  //    - The recursive call to recursiveConcat allocated memory for 'temp'.
  //    - We are responsible for freeing this memory to prevent memory leaks.
  free(temp);

  // 6. Return the final concatenated string.
  return result;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <string1> <string2>\n", argv[0]);
    return 1;
  }

  char *string1 = argv[1];
  char *string2 = argv[2];

  // Call our recursive concatenation function.
  char *concatenatedString = recursiveConcat(string1, string2);

  printf("Concatenated string: %s\n", concatenatedString);

  // Free the dynamically allocated memory for the final result.
  free(concatenatedString);

  return 0;
}