#!/bin/bash

# Go to the build folder and re-run CMake
cd build

# Generate project files
cmake ..

# Back to the root folder
cd ../

echo "Reloading finished!"
read -p "Press any key to continue..."