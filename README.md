# Cellular Automata Project

This C++ project implements a cellular automata simulation with both deterministic and random mutation features.

## Project Structure

```
cellular_automata/
├── src/              # Source files
│   ├── cellular_automata.cpp
│   └── play_automata.cpp
├── input/            # Input files
│   └── test_file.txt
└── output/           # Generated PBM files
    └── *.pbm
```

## Features

- Implementation of elementary cellular automata rules
- Random mutation support with configurable probability
- PBM file output format for visualization
- File-based input for initial states and rules

## Building

```bash
# Compile the main program
g++ src/cellular_automata.cpp -o bin/cellular_automata

# Compile the play automata program
g++ src/play_automata.cpp -o bin/play_automata
```

## Usage

1. Create an input file with:
   - First line: Initial state (sequence of 0s and 1s)
   - Second line: Rule definition (8 bits)

2. Run the program:
   ```bash
   ./bin/cellular_automata
   ```

3. When prompted:
   - Enter the input file path
   - Enter the number of generations
   - Enter the mutation probability

4. The program will generate a PBM file with the cellular automata evolution.

## License

[MIT License](LICENSE)
