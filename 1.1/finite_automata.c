#include <stdio.h>
#include <string.h>

// --- Definitions for our Finite Automaton (DFA) ---

// 1. Q - Finite nonempty set of states
typedef enum {
  STATE_A,       // Initial state and a non-final state
  STATE_B,       // Non-final state
  STATE_C,       // Non-final state
  STATE_D,       // Final state (accepting state) - Correctly added!
  STATE_REJECT,  // Implicit reject state
} State;

// 2. Σ (SIGMA) - Input alphabet
//    - The set of allowed symbols in the input string: {0, 1}

// 3. δ (DELTA) - Transition function
//    - Q × Σ → Q

// --- DFA Simulation Function ---

// Purpose of this DFA:
// This DFA is designed to recognize (accept) strings over the alphabet {0, 1} that
// contain the substring "010".

// Function to simulate the DFA
State finiteAutomaton(char *input) {
  // The current state of the automaton, initially the start state.
  State currentState = STATE_A;

  // Input symbol being processed
  char symbol;

  // String index
  int i = 0;

  // Process each symbol in the input string
  while ((symbol = input[i++]) != '\0') {
    // Check if the symbol is in the alphabet
    if (symbol != '0' && symbol != '1') {
      fprintf(stderr, "Error: Invalid symbol '%c' in input string. Alphabet is {0, 1}.\n", symbol);
      return STATE_REJECT;
    }

    // δ (DELTA) - Transition function implementation:
    switch (currentState) {
      case STATE_A:
        if (symbol == '0') {
          currentState = STATE_B;
        } else if (symbol == '1') {
          currentState = STATE_A;
        }
        break;

      case STATE_B:
        if (symbol == '0') {
          currentState = STATE_B;
        } else if (symbol == '1') {
          currentState = STATE_C;
        }
        break;

      case STATE_C:
        if (symbol == '0') {
          currentState = STATE_D; // Transition to STATE_D (accepting state) on input '0'
        } else if (symbol == '1') {
          currentState = STATE_A; // changed this to A per diagram
        }
        break;

      case STATE_D: // Accepting state (trap state)
        // Once in STATE_D, we stay in STATE_D regardless of the input
        currentState = STATE_D;
        break;

      default:
        fprintf(stderr, "Error: Invalid state encountered in DFA.\n");
        return STATE_REJECT;
    }
  }

  // After processing the entire input string, return the final state.
  return currentState;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <string>\n", argv[0]);
    return 1;
  }

  char *inputString = argv[1];

  // Simulate the DFA
  State finalState = finiteAutomaton(inputString);

  // Determine if the string is accepted or rejected based on the final state.
  if (finalState == STATE_D) {
    printf("String '%s' is accepted by the DFA (contains \"010\").\n", inputString);
  } else {
    printf("String '%s' is rejected by the DFA (does not contain \"010\").\n", inputString);
  }

  return 0;
}