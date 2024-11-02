#!/bin/bash

# Compile the C++ program
g++ main.cpp -o vending_machine -std=c++11

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the program..."
    # Run the compiled program
    ./vending_machine
else
    echo "Compilation failed. Please check for errors."
fi
