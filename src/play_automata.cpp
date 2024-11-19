#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "cellular_automata.cpp"

// Function to print the current state
void print_state(const std::vector<bool>& state) {
    for(bool cell : state) {
        std::cout << (cell ? "■" : "□");
    }
    std::cout << std::endl;
}

int main() {
    // Initialize random seed
    srand(time(0));

    // Define Rule 30 (00011110 in binary)
    bool rule30[8] = {0, 1, 1, 0, 1, 0, 0, 0};
    
    // Create initial state (93 cells with middle cell = 1)
    std::vector<bool> initial_state(160, false);
    initial_state[80] = true;  // Set middle cell to true
    
    // Create random automaton with Rule 30 and probability 0 (makes it behave like normal CA)
    random_cellular_automata automaton(rule30, initial_state, 0.1);
    
    // Run and print 100 generations
    std::vector<bool> current_state = initial_state;
    
    // Print initial state
    std::cout << "Generation 0:" << std::endl;
    print_state(current_state);
    
    // Run 100 generations
    for(int gen = 1; gen <= 1000; gen++) {
        current_state = automaton.next();
        std::cout << "Generation " << gen << ":" << std::endl;
        print_state(current_state);
    }
    
    return 0;
}
